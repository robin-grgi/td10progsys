#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<stdbool.h>
#include <jni.h>


int main() {
    
    JavaVM *jvm;

    JNIEnv *env;

    JavaVMOption jvmOptions[1];
    jvmOptions[0].optionString = "-Djava.class.path=.";

    JavaVMInitArgs vm_args = {
        .version = JNI_VERSION_10,
        .nOptions = 1,
        .options = jvmOptions,
        .ignoreUnrecognized = true
    };

    JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

    jclass cls = env->FindClass("Exo1");
    jmethodID mid = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
    printf("executing Exo1 using JNI\n");
    env->CallStaticVoidMethod(cls, mid, NULL);

    printf("execXX call for exercise 6\n");

    execlp("java", "java", "Exo1");

    printf("never printed\n");
}

