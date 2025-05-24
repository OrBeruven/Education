/*****************************
 *  Thread Pool Testing      *
 *                           *
 *  Developer: Or Beruven    *
 *  Reviewer: Nir            *
 *  Date: 23.07.2023         *
 ****************************/
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;
import java.lang.InterruptedException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

import ThreadPool.*;
public class JunitTest {
    public static final int NUM_OF_THREADS = 4;
    public ThreadPool pool = null;

    @BeforeEach
    public void initPool() {
        pool = new ThreadPool(NUM_OF_THREADS);
    }

    @Test
    public void executeTask() throws InterruptedException {
        Runnable task = new Task1();
        Callable<Integer> task2 = new Task2<>();
        Callable<Integer> task3 = new Task3<>();

        this.pool.execute(task);
        this.pool.submit(task2, Priority.HIGH);
        this.pool.submit(task3, Priority.LOW);
        this.pool.shutdown();
        this.pool.awaitTermination();
    }

    @Test
    public void executeTask2() throws InterruptedException, ExecutionException {

        this.pool.pause();
        Callable<Integer> task2 = new Task2<>();
        Callable<Integer> task3 = new Task3<>();
        Callable<Integer> task4 = new Task2<>();
        Callable<Integer> task5 = new Task3<>();
        Callable<Integer> task6 = new Task2<>();
        Callable<Integer> task7 = new Task3<>();
        Callable<Integer> task8 = new Task2<>();
        Callable<Integer> task9 = new Task3<>();
        Callable<Integer> task10 = new Task4();

        this.pool.submit(task2, Priority.HIGH);
        this.pool.submit(task3, Priority.LOW);
        this.pool.submit(task4, Priority.HIGH);
        this.pool.submit(task5, Priority.LOW);
        this.pool.submit(task6, Priority.HIGH);
        this.pool.submit(task7, Priority.LOW);
        this.pool.submit(task8, Priority.HIGH);
        this.pool.submit(task9, Priority.LOW);

        Future<Integer> returnVal = this.pool.submit(task10);

        Thread.sleep(5000);

        this.pool.resume();

        this.pool.setNumOfThreads(2);
        this.pool.shutdown();

        System.out.println(returnVal.get());
        System.out.println(returnVal.isDone());
        System.out.println(returnVal.isCancelled());
        System.out.println(returnVal.cancel(true));
        System.out.println(returnVal.isCancelled());

        this.pool.awaitTermination();
    }

    @Test
    public void cancel() throws InterruptedException, ExecutionException {
        Future<Void> future = pool.submit(new InfinitTask(), Priority.DEFAULT);
        future.cancel(true);


        Assertions.assertThrows(CancellationException.class, future::get);
        pool.shutdown();
        pool.awaitTermination();
    }

    @Test
    public void submit() throws ExecutionException, InterruptedException {
        List<Future<Integer>> myFutures = new ArrayList<>(10);
        myFutures.add(pool.submit(new MyCallable(1)));
        myFutures.add(pool.submit(new MyCallable(2)));
        myFutures.add(pool.submit(new MyCallable(3)));
        myFutures.add(pool.submit(new MyCallable(4)));
        myFutures.add(pool.submit(new MyCallable(5)));
        myFutures.add(pool.submit(new MyCallable(6)));
        myFutures.add(pool.submit(new MyCallable(7)));
        myFutures.add(pool.submit(new MyCallable(8)));
        myFutures.add(pool.submit(new MyCallable(9)));
        myFutures.add(pool.submit(new MyCallable(10)));

        myFutures.get(9).cancel(true);
        pool.pause();
        System.out.println("paused");
        Thread.sleep(10000);
        System.out.println("resuming");
        pool.resume();

        for (Future<Integer> future : myFutures) {
            if (!future.isCancelled()) {
                System.out.println(future.get());
            }
        }

        System.out.println("Got all futures");
    }

    @Test
    public void ExceptionTest() throws ExecutionException, InterruptedException {
        //       ExecutorService executorService = Executors.newFixedThreadPool(2);
        ThreadPool executorService = new ThreadPool(2);
        executorService.submit(new ExceptionTask(1));
        executorService.submit(new ExceptionTask(2));
        executorService.submit(new ExceptionTask(3));
        executorService.submit(new ExceptionTask(4));
        Future<Integer> future = executorService.submit(new ExceptionTask(5));

        //future.cancel(false);
        Assertions.assertThrows(ExecutionException.class, future::get);
    }

    @Test
    public void FutureCancelExceptionTest() throws ExecutionException, InterruptedException {
        pool.submit(new MyCallable(1));
        pool.submit(new MyCallable(2));
        pool.submit(new MyCallable(3));
        pool.submit(new MyCallable(4));
        Future<Integer> future = pool.submit(new MyCallable(5));

        future.cancel(false);
        Assertions.assertThrows(CancellationException.class, future::get);
    }

    @Test
    public void PauseResumeByPriority() throws InterruptedException {
        pool.pause();
        Callable<Integer> low1 = new LowPriorityTask();
        Callable<Integer> low2 = new LowPriorityTask();
        Callable<Integer> low3 = new LowPriorityTask();
        Callable<Integer> low4 = new LowPriorityTask();

        pool.submit(low1, Priority.LOW);
        pool.submit(low2, Priority.LOW);
        pool.submit(low3, Priority.LOW);
        pool.submit(low4, Priority.LOW);

        Callable<Integer> high1 = new HighPriorityTask();
        Callable<Integer> high2 = new HighPriorityTask();
        Callable<Integer> high3 = new HighPriorityTask();
        Callable<Integer> high4 = new HighPriorityTask();

        pool.submit(high1, Priority.HIGH);
        pool.submit(high2, Priority.HIGH);
        pool.submit(high3, Priority.HIGH);
        pool.submit(high4, Priority.HIGH);

        pool.resume();

        pool.shutdown();
        pool.awaitTermination();
    }

//    @Test
//    void setNumOfThreads() throws InterruptedException {
//        Assertions.assertEquals(4, pool.getNumOfThreads());
//        pool.setNumOfThreads(7);
////        Thread.sleep(1000);
//        Assertions.assertEquals(7, pool.getNumOfThreads());
//        pool.setNumOfThreads(5);
//        Thread.sleep(1000);
//        System.out.println("Wait make process");
//        System.out.println("Here");
//        System.out.println("AHAHAH");
//        /*might not go through as it depends on cpu time*/
//        Assertions.assertEquals(5, pool.getNumOfThreads());
//
//
//        pool.shutdown();
//        pool.awaitTermination();
//    }

    @Test
    void pause() throws InterruptedException {
        pool.pause();
        pool.submit(new MyCallable(1));
        pool.resume();

        pool.shutdown();
        pool.awaitTermination();
    }

    @Test
    void testPause() throws InterruptedException, ExecutionException {
        ThreadPool singleThreadpool = new ThreadPool(1);

        singleThreadpool.submit(Tasks::sleepLover, Priority.LOW);
        Future<Integer> fut = singleThreadpool.submit(Tasks::sumIndexTask, Priority.HIGH);
        singleThreadpool.pause();
        System.out.println("Pause for 5 sec");
        Thread.sleep(5000);
        Assertions.assertFalse(fut.isDone());
        System.out.println("resume");
        singleThreadpool.resume();
        singleThreadpool.shutdown();
        singleThreadpool.awaitTermination();
        Assertions.assertTrue(fut.isDone());
        Assertions.assertEquals(10, fut.get());
    }
}

class Task1 implements Runnable{
    @Override
    public void run() {
        System.out.println("Run 1");
    }
}

class Task2<V> implements Callable<V>{
    @Override
    public V call() throws Exception {
        Thread.sleep(1000);
        System.out.println("run 2");
        return null;
    }
}

class Task3<V> implements Callable<V>{
    @Override
    public V call() throws Exception {
        Thread.sleep(1000);
        System.out.println("run 3");
        return null;
    }
}

class Task4 implements Callable<Integer> {
    @Override
    public Integer call() throws Exception {
        Thread.sleep(1000);
        Object o = new Object();
        Thread.sleep(1000);
        return (4);
    }
}

class InfinitTask implements Runnable {
    @Override
    public void run() {
        for (int i = 0; i < 10000000 && !Thread.currentThread().isInterrupted(); ++i) {
            System.out.println("E");
        }
    }
}
class MyCallable implements Callable<Integer> {
    Integer num = null;
    public MyCallable(Integer num) {
        this.num = num;
    }

    @Override
    public Integer call() throws Exception {
        System.out.println("inside my callable");
        Thread.sleep(5000);
        return num;
    }
}

class ExceptionTask implements Callable<Integer> {
    Integer num = null;
    public ExceptionTask(Integer num) {
        this.num = num;
    }

    @Override
    public Integer call() throws Exception {
        System.out.println("inside my callable");
        throw new InterruptedException();
    }
}

class HighPriorityTask implements Callable<Integer> {
    @Override
    public Integer call() throws InterruptedException {
        Thread.sleep(1000);
        System.out.println("HIGH");
        return 1;
    }
}

class LowPriorityTask implements Callable<Integer> {
    @Override
    public Integer call() throws InterruptedException {
        Thread.sleep(1000);
        System.out.println("LOW");
        return 1;
    }
}

class Tasks {
    public static String sleepLover() throws InterruptedException {
        System.out.println("sleepLover task running");
        Thread.sleep(5000);
        System.out.println("bla bla");
        return "Task slept for 5 sec";
    }

    public static Integer sumIndexTask() {
        System.out.println("sumIndex task running");
        int res = 0;
        for (int i = 0; i < 5; ++i) {
            res += i;
        }
        return res;
    }
}