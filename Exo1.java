import java.lang.management.ManagementFactory;

/**
 * Exo1
 */
public class Exo1 {
    public static void main(String[] args) {
        
        System.out.println("Java 8 PID : " + ManagementFactory.getRuntimeMXBean().getName());
        System.out.println("Java 9 PID : " + ProcessHandle.current().pid());

    }
}