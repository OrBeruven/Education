import java.util.concurrent.*;

public class Ex1 {
    public static void main(String[] args) throws ExecutionException, InterruptedException {
        ExecutorService pool = Executors.newFixedThreadPool(2);

        Future f2 = pool.submit(new Callable<String>() {

            @Override
            public String call() throws Exception {
                System.out.println("Second task - Callable");
                return "Callable return value";
            }
        });

        pool.submit(() -> { System.out.println("First task - Runnable"); });


        System.out.println("f2.get() = " + f2.get());

        pool.shutdown();
    }
}