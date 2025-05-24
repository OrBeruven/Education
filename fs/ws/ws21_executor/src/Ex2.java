import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class Ex2 {
    public static void main(String[] args) throws InterruptedException {
        //singleThreadPool();
        //fixedThreadPool();
        //cachedThreadPool();

        schedulerThreadPool();
    }

    public static void singleThreadPool() {
        ExecutorService singleThread = Executors.newSingleThreadExecutor();
        int i = 0;
        for (; i < 5; ++i) {
            singleThread.submit(() -> {
                System.out.println(Thread.currentThread().getName() + " Is running this task");
            } );
        }

        singleThread.shutdown();
    }

    public static void fixedThreadPool() {
        ExecutorService fixedPool = Executors.newFixedThreadPool(3);
        int i = 0;
        for (; i < 5; ++i) {
            fixedPool.submit(() -> {
                System.out.println(Thread.currentThread().getName() + " Is running this task");
            } );
        }

        fixedPool.shutdown();
    }

    public static void cachedThreadPool() {
        ExecutorService cachedPool = Executors.newCachedThreadPool();
        int i = 0;
        for (; i < 5; ++i) {
            cachedPool.submit(() -> {
                System.out.println(Thread.currentThread().getName() + " Is running this task");
            } );
        }

        cachedPool.shutdown();
    }

    public static void schedulerThreadPool() throws InterruptedException {
        ScheduledExecutorService schedPool = Executors.newScheduledThreadPool(3);
        int i = 0;
        for (; i < 5; ++i) {
            schedPool.scheduleAtFixedRate(() -> {
                System.out.println(Thread.currentThread().getName() + " Is running this task");
            }, 1, 3, TimeUnit.SECONDS);
        }

        schedPool.awaitTermination(10, TimeUnit.SECONDS);
    }
}
