#include <iostream>

#include "engine/me_pocolor_traincraft_engine_Engine.h"

JNIEXPORT void JNICALL
Java_me_pocolor_traincraft_engine_Engine_test(JNIEnv *env, jobject obj) {
    std::cout << "Hello world from a native function!" << std::endl;
}