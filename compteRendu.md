# Programmation système : TP10 : Mise en oeuvre de JNI sur un cas concret

## 1 - Récupérer l'identifiant de processus d'une JVM (processus ID)

### Exercice 1:
Apperçu des PID de la JVM utilisée par le programme :

```
░▒▓~/Documents/Polytech/S6/OS/TD10/td10▓▒░ java Exo1                                                                          
Java 8 PID: 121998@RG-Recoil-III-GTX
Java 9 PID: 121998
```

### Exercice 2:

Apperçu des PID de la JVM utilisée par le programme avec appel natif C++ de getPid():



```
░▒▓~/Documents/Polytech/S6/OS/TD10/td10▓▒░ java -Djava.library.path=lib TP10
Java 8 PID: 28184@RG-Recoil-III-GTX
Java 9 PID: 28184
C++ PID: 28184
```

Apperçu du PID de la JVM dans ps aux :


```
robin      28184  4.6  0.2 6925560 38156 pts/1   Sl+  09:16   0:00 java Exo1
robin      28246  0.0  0.0  10284  3428 pts/0    R+   09:16   0:00 ps aux
```

### Exercice 3 / 4:
Code java des exercices 3 / 4:
```java
public class Exo3And4 {

    public static native int getPid();

    public static native int fork();

    public static native void cwait(int pid);

    public static native void exit(int status);

    public static native void sleep(int time);

    public static final int P = 10;
    public static final int N = 10;

    public static void main(String[] args) {
        System.loadLibrary("Exo3And4");

        int tabPID[] = new int[P];
        int cpt = 1;
        for (int i = 0; i < P; i++) {
            switch (tabPID[i] = Exo3And4.fork()) {
                case -1:
                    System.err.println("Erreur lors de la création du processus fils");
                    Exo3And4.exit(1);
                case 0:
                    for (int j = 0; j < N; j++) {
                        ++cpt;
                        System.out.println("fils n°" + i);
                    }
                    Exo3And4.sleep(1);
                    Exo3And4.exit(0);
                default:
                    break;
            }
        }
        for(int i = 0 ; i < P ; i++){
            Exo3And4.cwait(tabPID[i]);
        }
    }
```

Code C++ des exercices 3 / 4:
```c++
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
```

Apperçu du résultat des deux premiers exercices du TP 3 avec JNI : 

```
░▒▓~/Documents/Polytech/S6/OS/TD10/td10▓▒░ java Exo3And4 

fils n°0
fils n°0
fils n°0
fils n°0
fils n°0
fils n°0
fils n°0
fils n°0
fils n°0
fils n°0                  
fils n°1
fils n°1
fils n°1
fils n°1
fils n°1
fils n°1
fils n°1
fils n°1
fils n°1
fils n°1
...
fils n°9
fils n°9
fils n°9
fils n°9
fils n°9
fils n°9
fils n°9
fils n°9
fils n°9
fils n°9
```

### Exercice 5 / 6:

Le principal avantage d'exec par rapport à JNI est qu'il est beaucoup plus simple à coder, une ligne de code suffit pour faire un appel à la jvm depuis C++. En revanche JNI a l'avantage de poursuivre l'exécution du programme en cours contrairement à execXX qui écrase complètement la suite du processus (bien que cela reste contournable avec un fork).