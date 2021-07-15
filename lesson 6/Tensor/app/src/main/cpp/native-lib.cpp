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

jbyteArray* getImage(jobject context, JNIEnv* env) {
    jclass contextThemeWrapperClass = env->FindClass("android/view/ContextThemeWrapper");
    jmethodID getAssetsID = env->GetMethodID(contextThemeWrapperClass, "getAssets", "()Landroid/content/res/AssetManager;");
    jobject assets = env->CallObjectMethod(context, getAssetsID);

//!! could you please give me a hint, how I can call open on die jobject assets??
    // call open on assets object and continue the rest of the code
    jclass AssetManager = env->FindClass("android/content/res/AssetManager");
    jmethodID openFile = env->GetMethodID(AssetManager, "open", "([type)Ljava/io/InputStream;"); // ??
    jobject open = env->CallObjectMethod(context, openFile);

    jclass InputStream = env->FindClass("java/io/InputStream");
    jmethodID available = env->GetMethodID(InputStream, "available()", ()I);  // available() returns 0; how does it return the size?
    jint size = env->CallIntMethod(context, available);

    jbyteArray jbuffer[size];
    // how can we get the row and column size of the pictur?

    jmethodID read = env->GetMethodID(InputStream, "read", (jbyteArray)I); // ??
    jint result = env->CallIntMethod(context, read, jbuffer);

    jmethodID close = env->GetMethodID(InputStream, "close", ()); // ??
    env->CallVoidMethod(context, close);

    return jbuffer;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_tensorapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject context, jbyteArray buffer) {

    int server_socket;
    sockaddr_in server;
    char server_reply[1000] = {0};
    getImage(context, env);

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

    char *picTransmit = (char*) env->GetByteArrayElements(buffer, nullptr);
    std::size_t size = env->GetArrayLength(buffer);
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

