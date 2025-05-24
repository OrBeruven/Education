/*
import java.util.concurrent.Callable;
import java.util.concurrent.Executor;
import java.util.concurrent.Future;

public class ThreadPool implements Executor {
    public ThreadPool(int numOfThreads) {
    }

    @Override
    public void execute(Runnable command) {
    }

    public Future<Void> submit(Runnable r, Priority priority);
    public <T> Future<T> submit(Runnable r, Priority priority, T value);

    public <T> Future<T> submit(Callable<T> c);
    public <T> Future<T> submit(Callable<T> c, Priority priority);

    public void setNumOfThreads(int newNumOfThreads);

    public void pause();
    public void resume();
    public void shutDown();
    public void awaitTermination() throws InterruptException;

    private class Task {
        private ThreadPoolFuture implements Future{};
    }
}*/
