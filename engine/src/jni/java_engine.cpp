#include "jni/me_pocolor_traincraft_engine_Engine.h"
#include "engine/application.h"

JNIEXPORT void JNICALL
Java_me_pocolor_traincraft_engine_Engine_run(JNIEnv *, jobject) {
    Application::init();
    Application::run();
    Application::shutdown();
}
