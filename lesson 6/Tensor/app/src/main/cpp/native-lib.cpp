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
    jmethodID getAssetsID = env->GetMethodID(contextThemeWrapperClass, "getAssets", "()Landroid/content/res/AssetManager;");
    jobject assets = env->CallObjectMethod(context, getAssetsID);
//!! could you please give me a hint, how I can call open on die jobject assets??
    // call open on assets object and continue the rest of the code
    jclass AssetManager = env->FindClass("android/content/res/AssetManager");
    jmethodID openFile = env->GetMethodID(AssetManager, "open", "([type)Landroid/content/res/AssetManager");
    jobject open = env->CallObjectMethod(context, openFile);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_tensorapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject context, jbyteArray buffer) {

    int s;
    sockaddr_in server;
    char server_reply[32] = {0};
    std::string message = "hello server TEST";

    //getImage(context, env);

    if (((s = socket(AF_INET , SOCK_STREAM , 0)) < 0)) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in socket") +strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "Socket created");

    server.sin_addr.s_addr = inet_addr("192.168.148.130");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    if (connect(s, (struct sockaddr *)&server , sizeof(server)) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in connect") +strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "connected!");

    char *picTransmit = (char*) env->GetByteArrayElements(buffer, nullptr);
    std::size_t size = env->GetArrayLength(buffer);
    std::string length = std::to_string(size);
    std::size_t sendSize = 0, tmp_size = 0;

    send(s, length.c_str(), length.size(), 0);


    while((sendSize = send(s, &picTransmit[tmp_size], size - tmp_size , 0) > 0)) {
        tmp_size += sendSize;
        //__android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        //return env->NewStringUTF((std::string("ERROR in send") +strerror(errno)).c_str());
    }

    //Receive a reply from the server
    if (recv(s, server_reply , 32 , 0) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in recv") + strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, server_reply);

    close(s);

    return env->NewStringUTF((std::string("bytes received from server =  ") + server_reply).c_str());
}

