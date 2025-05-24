/****************************************************************************
 *  Thread Pool implementation : Executor interface, Fixed size thread pool *
 *                                                                          *
 *  Developer: Or Beruven                                                   *
 *  Reviewer: Nir                                                           *
 *  Date: 23.07.2023                                                        *
 ***************************************************************************/
package ThreadPool;

import WaitablePQueue.WaitablePQueue;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class ThreadPool implements Executor {
    private final WaitablePQueue<Task<?>> wpq = new WaitablePQueue<Task<?>>();
    private final ConcurrentLinkedQueue<Thread> pool = new ConcurrentLinkedQueue<>();
    private final AtomicBoolean isShutDown = new AtomicBoolean(false);
    private final Semaphore pauseSemaphore = new Semaphore(0);
    private boolean isPause = false;
    private int numOfThreads = 0;

    public ThreadPool(int numOfThreads) {
        this.numOfThreads = numOfThreads;
        for (int i = 0; i < this.numOfThreads; ++i) {
            this.pool.add(new ManagerThread());
        }

        for (Thread thread : this.pool) {
            thread.start();
        }
    }

    private class ManagerThread extends Thread {
        private boolean enable = true;
        @Override
        public void run() {
            Task<?> task = null;
            while (enable) {

                try {
                    task = wpq.deque();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }

                task.setTaskRunnerThread(Thread.currentThread());
                task.run();

                Thread.interrupted();
            }

            if (!ThreadPool.this.isShutDown.get()) {
                ThreadPool.this.pool.remove(Thread.currentThread());
            }
        }
    }

    private class Task<T> implements Runnable, Comparable<Task<T>> {
        private final Callable<T> task;
        private final ThreadPoolPriorityI priority;
        private Thread taskRunnerThread = null;
        private final TaskFuture future = new TaskFuture();
        private final ReentrantLock doneLock = new ReentrantLock();
        private final Condition getWhenDone = doneLock.newCondition();
        private boolean isDone = false;
        private boolean isCancelled = false;
        private Exception thrownException = null;

        Task(Callable<T> task, ThreadPoolPriorityI priority) {
            this.priority = priority;
            this.task = task;
        }

        private class TaskFuture implements Future<T> {
            private T valueToReturn = null;
            @Override
            public boolean cancel(boolean mayInterruptIfRunning) {
                if (ThreadPool.this.wpq.remove(Task.this)) {
                    Task.this.setCancelled();
                    return true;
                }

                Task.this.doneLock.lock();
                if (mayInterruptIfRunning && !this.isDone() && !this.isCancelled()) {
                    Task.this.taskRunnerThread.interrupt();
                    Task.this.setCancelled();
                }
                Task.this.doneLock.unlock();

                return isCancelled();
            }

            @Override
            public boolean isCancelled() {
                return Task.this.isCancelled;
            }

            @Override
            public boolean isDone() {
                return Task.this.isDone;
            }

            @Override
            public T get() throws InterruptedException, ExecutionException {
                Task.this.doneLock.lock();
                while (!Task.this.isDone) {
                    throwCancellationIfNeeded();
                    try {
                        Task.this.getWhenDone.await();
                    } finally {
                        Task.this.doneLock.unlock();
                    }
                }

                throwCancellationIfNeeded();

                if (null != thrownException) {
                    throw new ExecutionException(thrownException);
                }

                return this.valueToReturn;
            }

            private void throwCancellationIfNeeded() throws CancellationException {
                if (this.isCancelled()) {
                    throw new CancellationException("Get to canceled task");
                }
            }

            @Override
            public T get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
                timeout = unit.toNanos(timeout);

                while (!Task.this.isDone && timeout > 0) {
                    throwCancellationIfNeeded();
                    Task.this.doneLock.lock();
                    try {
                        timeout = Task.this.getWhenDone.awaitNanos(timeout);
                    } finally {
                        Task.this.doneLock.unlock();
                    }
                }

                if (0 >= timeout) {
                    throw new TimeoutException("Timed out");
                }
                if (null != thrownException) {
                    throw new ExecutionException(thrownException);
                }

                return this.valueToReturn;
            }

            private void setValueToReturn(T value) {
                this.valueToReturn = value;
            }
        }
        @Override
        public int compareTo(Task<T> o) {
            return this.getPriority().comparePriority(o.getPriority());
        }

        @Override
        public void run() {
            try {
                this.future.setValueToReturn(this.task.call());
            } catch (Exception e) {
                this.thrownException = e;
            } finally {
                this.doneLock.lock();
                this.isDone = true;
                this.getWhenDone.signalAll();
                this.doneLock.unlock();
            }
        }
        private Future<T> getFuture() {
            return this.future;
        }

        private ThreadPoolPriorityI getPriority() {
            return this.priority;
        }

        private void setCancelled() {
            this.isCancelled = true;
        }

        private void setTaskRunnerThread(Thread runnerThread) {
            this.taskRunnerThread = runnerThread;
        }
    }

    @Override
    public void execute(Runnable command) {
         submit(command, Priority.DEFAULT);
    }

    public Future<Void> submit(Runnable runnable, Priority priority) {
        return submit(runnable, priority, null);
    }
    public <T> Future<T> submit(Runnable runnable, Priority priority, T value) {
        return submit(Executors.callable(runnable, value), priority);
    }
    public <T> Future<T> submit(Callable<T> callable) {
        return submit(callable, Priority.DEFAULT);
    }
    public <T> Future<T> submit(Callable<T> callable, Priority priority) {
        if (this.isShutDown.get()) {
            throw new RejectedExecutionException("Submitted task after shut down");
        }
        if (null == callable) {
            throw new NullPointerException("illegal null task");
        }

        Task<T> task = new Task<T>(callable, priority);
        this.wpq.enque(task);
        return task.getFuture();
    }

    public void setNumOfThreads(int newNumOfThreads) {
        if (0 > newNumOfThreads) {
            throw new IllegalArgumentException("Negative num of threads");
        } else if (isPause) {
            throw new IllegalStateException("Can't change num of threads while paused");
        } else if (this.numOfThreads == newNumOfThreads) {
            /*No changes to be made*/
            return;
        }

        if (this.numOfThreads < newNumOfThreads) {
            addThreadsToPool(newNumOfThreads - this.numOfThreads);
        } else {
            removeThreadsFromPool(this.numOfThreads - newNumOfThreads, DeveloperPriority.DEV_HIGH);
        }
    }
    private void addThreadsToPool(int numOfThreads) {
        for (int i = 0; i < numOfThreads; ++i) {
            Thread newThread = new Thread(new ManagerThread());
            this.pool.add(newThread);
            newThread.start();
        }

        this.numOfThreads += numOfThreads;
    }
    private void removeThreadsFromPool(int numOfThreads, ThreadPoolPriorityI priority) {
        for (int i = 0; i < numOfThreads; ++i) {
            submitManagerialTask(() -> ((ManagerThread)Thread.currentThread()).enable = false, priority);
        }

        this.numOfThreads -= numOfThreads;
    }

    private void submitManagerialTask(Runnable runnable, ThreadPoolPriorityI priority) {
        Task<Void> task = new Task<Void>(Executors.callable(runnable, null), priority);
        this.wpq.enque(task);
    }

    public void pause() {
        if (!this.isPause) {
            this.setIsPause(true);

            for (int i = 0; i < this.numOfThreads; ++i) {
                submitManagerialTask(() -> {
                    try {
                        this.pauseSemaphore.acquire();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }, DeveloperPriority.DEV_HIGH);
            }
        }
    }
    public void resume() {
        if (this.isPause) {
            this.setIsPause(false);
            this.pauseSemaphore.release(this.numOfThreads);
        }
    }

    public void shutdown() {
        this.isShutDown.set(true);
        removeThreadsFromPool(this.numOfThreads, DeveloperPriority.DEV_LOW);
    }
    public void awaitTermination() throws InterruptedException {
        if (!isShutDown.get()) {
            throw new IllegalStateException("Can't await termination without calling shutdown() method beforehand");
        }

        for (Thread thread : this.pool) {
            thread.join();
        }

        this.pool.clear();
    }

    private void setIsPause(boolean isPause) {
        this.isPause = isPause;
    }
}