#include <jni.h>
#include <string>
#include <string.h>
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <android/log.h>
#include <errno.h>
#define LOG_TAG "CLIENT_APP"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_tensorapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    int s;
    sockaddr_in server;
    char server_reply[2000] = {0};
    std::string message = "hello server jan";

    if (((s = socket(AF_INET , SOCK_STREAM , 0)) < 0)) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in socket") +strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "Socket created");

    server.sin_addr.s_addr = inet_addr("192.168.58.130");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    if (connect(s, (struct sockaddr *)&server , sizeof(server)) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in connect") +strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "connected!");

    if(send(s, message.c_str(), message.size() , 0) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in send") +strerror(errno)).c_str());
    }

    //Receive a reply from the server
    if (recv(s, server_reply , 2000 , 0) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in recv") + strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, server_reply);

    close(s);

    return env->NewStringUTF(server_reply);
}