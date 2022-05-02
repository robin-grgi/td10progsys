import java.lang.management.ManagementFactory;

/**
 * Exo1
 */
public class Exo2 {

    public static native int getPid();

    public static void main(String[] args) {
        
        System.loadLibrary("Exo1And2");

        System.out.println("Java 8 PID : " + ManagementFactory.getRuntimeMXBean().getName());
        System.out.println("Java 9 PID : " + ProcessHandle.current().pid());
        System.out.println("C++ PID : " + Exo2.getPid());

    }
}