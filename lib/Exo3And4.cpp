#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include "Exo3And4.h"

JNIEXPORT jint JNICALL Java_Exo3And4_getPid(JNIEnv *env, jclass cls) {
    return (jint)getpid();
}

JNIEXPORT jint JNICALL Java_Exo3And4_fork(JNIEnv *env, jclass cls) {
    return (jint)fork();
}

JNIEXPORT void JNICALL Java_Exo3And4_cwait(JNIEnv *env, jclass cls, jint pid) {
    wait(&pid);
}

JNIEXPORT void JNICALL Java_Exo3And4_exit(JNIEnv *env, jclass cls, jint status) {
    exit(status);
}

JNIEXPORT void JNICALL Java_Exo3And4_sleep(JNIEnv *env, jclass cls, jint time) {
    sleep(time);
}