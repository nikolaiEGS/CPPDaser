#include <jni.h>
#include <string>
#include <string.h>
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <android/log.h>
#include <errno.h>
#include <locale>


#define LOG_TAG "CLIENT_APP"

jbyteArray getImage(jobject context, JNIEnv* env) {
    jclass contextThemeWrapperClass = env->FindClass("android/view/ContextThemeWrapper");
    jclass assetManagerClass = env->FindClass("android/content/res/AssetManager");
    jclass inputStreamClass = env->FindClass("java/io/InputStream");

    jmethodID getAssetsID = env->GetMethodID(contextThemeWrapperClass, "getAssets", "()Landroid/content/res/AssetManager;");
    jmethodID openID = env->GetMethodID(assetManagerClass, "open", "(Ljava/lang/String;)Ljava/io/InputStream;");
    jmethodID availableID = env->GetMethodID(inputStreamClass, "available", "()I");
    jmethodID readID = env->GetMethodID(inputStreamClass, "read", "([B)I");
    jmethodID closeID = env->GetMethodID(inputStreamClass, "close", "()V");

    jobject assets = env->CallObjectMethod(context, getAssetsID);
    jobject stream = env->CallObjectMethod(assets, openID, env->NewStringUTF("zivert.jpg"));

    jint j_size = env->CallIntMethod(stream, availableID);
    std::size_t size = (std::size_t)j_size;
    jbyteArray buffer = env->NewByteArray(j_size);
    jint r = env->CallIntMethod(stream, readID, buffer);

    env->CallVoidMethod(stream, closeID);

    env->DeleteLocalRef(contextThemeWrapperClass);
    env->DeleteLocalRef(assetManagerClass);
    env->DeleteLocalRef(inputStreamClass);
    env->DeleteLocalRef(assets);
    env->DeleteLocalRef(stream);

    return buffer;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_tensorapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject context) {

    int server_socket;
    sockaddr_in server;
    char server_reply[1000] = {0};


    if (((server_socket = socket(AF_INET , SOCK_STREAM , 0)) < 0)) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in socket") +strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "Socket created");

    server.sin_addr.s_addr = inet_addr("192.168.148.131");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    if (connect(server_socket, (struct sockaddr *)&server , sizeof(server)) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in connect") +strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "connected!");

    jbyteArray buffer = getImage(context, env);
    std::size_t size = env->GetArrayLength(buffer);
    char* picTransmit =  (char*) env->GetByteArrayElements(buffer, nullptr);
    std::string length = std::to_string(size);
    std::size_t sendSize = 0, send_counter = 0;


    send(server_socket, length.c_str(), length.size(), 0);

    while((sendSize = send(server_socket, &picTransmit[send_counter], size - send_counter , 0) > 0)) {
        send_counter += sendSize;
    }

    //Receive a reply from the server
    if (recv(server_socket, server_reply , 1000 , 0) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in recv") + strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, server_reply);

    close(server_socket);

    // code without calling methods through jni does work, except print of server_reply
    return env->NewStringUTF((std::string("Server reply: ") + server_reply).c_str());
}

