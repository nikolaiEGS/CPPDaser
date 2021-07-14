#include <jni.h>
#include <string>
#include <string.h>
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <android/log.h>
#include <errno.h>
#include <fstream>
#include <vector>

#define LOG_TAG "CLIENT_APP"

std::string jstringToSTDString(JNIEnv* env, jstring jstr) {
    jboolean isCopy;
    const char* convertedValue = env->GetStringUTFChars(jstr, &isCopy);
    std::string str = std::string(convertedValue, strlen(convertedValue));
    return str;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_tensorapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject thizz, jbyteArray imageBuff) {

    int s;
    std::size_t sentLen;
    std::size_t sentCounter = 0;

    sockaddr_in server;
    char server_reply1[2000] = {0};
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

    jboolean isCopy;
    jbyte* b = env->GetByteArrayElements(imageBuff, &isCopy);
    char* imageBuffCh = (char*) b;
    int l = env->GetArrayLength(imageBuff);

    if(send(s, std::to_string(l).c_str(), std::to_string(l).size() , 0) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in send") +strerror(errno)).c_str());
    }

    if(recv(s, server_reply1, 2000 , 0) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in recv 1") + strerror(errno)).c_str());
    } else {
        __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, server_reply1);
    }

    while ((sentLen = send(s, imageBuffCh+sentCounter, l-sentCounter, 0)) > 0) {
        sentCounter += sentLen;
        __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, (std::string("sent len: ") + std::to_string((sentCounter))).c_str());
    }


    if (recv(s, server_reply , 100 , 0) < 0) {
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, strerror(errno));
        return env->NewStringUTF((std::string("ERROR in recv") + strerror(errno)).c_str());
    }

    __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, server_reply);

    close(s);

    return env->NewStringUTF(server_reply);
}