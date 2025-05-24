public class IncorrectSyncExample {
    private static int sharedCounter = 0;

    public static void main(String[] args) {
        Thread thread1 = new Thread(() -> {
            for (int i = 0; i < 1000; i++) {
                incrementCounter();
            }
        });

        Thread thread2 = new Thread(() -> {
            for (int i = 0; i < 1000; i++) {
                incrementCounter();
            }
        });

        thread1.start();
        thread2.start();

        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Final Counter Value: " + sharedCounter);
    }

    private static void incrementCounter() {
        int temp = sharedCounter;
        synchronized (IncorrectSyncExample.class) {
            temp++;
            sharedCounter = temp;
        }
    }
}