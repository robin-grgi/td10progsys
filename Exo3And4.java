import java.lang.management.ManagementFactory;
import java.util.concurrent.TimeUnit;

/**
 * Exo1
 */
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
}