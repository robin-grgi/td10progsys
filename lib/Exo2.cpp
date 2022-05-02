#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <wait.h>
#include "Exo2.h"

JNIEXPORT jint JNICALL Java_Exo1And2_getPid(JNIEnv *env, jclass cls) {
    return (jint)getpid();
}

