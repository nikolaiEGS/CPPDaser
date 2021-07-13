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

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_tensorapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    int s;
    sockaddr_in server;
    char server_reply[32] = {0};
    std::string message = "hello server TEST";

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

    jbyteArray* cData = env->GetByteArrayElements(data);
    std::size_t size = sizeof(cData);
    char* picTransmit = new char[size];
    picTransmit = (char*)cData;
    std::string length = std::to_string(size);
    std::size_t sendSize = 0, tmp_size = 0;
    send(s, &length, length.size(), 0);
    while((sendSize = send(s, &picTransmit[tmp_size], size - tmp_size , 0) > 0) {
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

    return env->NewStringUTF("bytes received from server =  " + server_reply);
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_tensorapp_MainActivity_sendData(JNIEnv *env, jobject thiz, jbyteArray data) {
    // TODO: implement sendData()
}