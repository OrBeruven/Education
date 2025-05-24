import ThreadPool.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

public class ThreadPoolTests {

//    public static void main(String[] args) throws InterruptedException, ExecutionException {
//        ThreadPool threadPool = new ThreadPool(2);
//        threadPool.execute(() -> System.out.println("Run 1"));
//
//        Future<Integer> future = threadPool.submit(new CallTask(), Priority.DEFAULT);
//        Thread.sleep(100);
//
//        threadPool.shutdown();
//    }




    static class CallTask implements Callable<Integer> {
        @Override
        public Integer call() throws Exception {
            System.out.println("Returning 1");
            return 1;
        }
    }
}
