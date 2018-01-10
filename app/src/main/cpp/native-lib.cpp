#include <jni.h>
#include <string>
#include <oboe/Oboe.h>
#include <android/log.h>
#include <thread>
#include "AudioEngine.h"


static AudioEngine engine;

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_donturner_oboecrashtest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    engine.runTest();

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
