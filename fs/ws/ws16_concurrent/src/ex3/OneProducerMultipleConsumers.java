/***************************
 *  Written by : Or
 *  Reviewer : Neviu
 *  Date : 11.07.2023
 ***************************/
package ex3;

import java.time.LocalDate;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class OneProducerMultipleConsumers {
    private static final Object monitor = new Object();
    static final int numConsumers = 3;
    static boolean isHasMessage = false;
    private static final Semaphore sem = new Semaphore(0);
    public static final ReentrantLock lock = new ReentrantLock();
    private static final Condition condition = lock.newCondition();
    static int count = 0;
    static String globalData = "";



    /* Moshe's implementation*/
    public static int globalInt = 0;
    public static final Lock lockCon = new ReentrantLock();
    public static final Condition allConsumed = lockCon.newCondition();
    static final Semaphore semaphore = new Semaphore(0);
    static final int CONSUMERS = 2;


    public static void main(String[] args) throws InterruptedException {
        int numProducers = 1;

        /*for (int i = 0; i < numProducers; ++i) {
            Thread thread1 = new Thread(new Producer());
            thread1.start();
        }

        for (int i = 0; i < numConsumers; ++i) {
            Thread thread2 = new Thread(new Consumer());
            thread2.start();
        }*/

        for (int i = 0; i < numProducers; ++i) {
            Thread thread1 = new Thread(new ProducerMoshe());
            thread1.start();
        }

        for (int i = 0; i < CONSUMERS; ++i) {
            Thread thread2 = new Thread(new ConsumerMoshe());
            thread2.start();
        }
    }

    static class Producer implements Runnable {
        @Override
        public void run() {
            try {
                while(true) {
                    sem.acquire(numConsumers);
                    System.out.println("Producer added globalData to buffer ");
                    isHasMessage = true;
                    globalData = "hello " + count;

                    synchronized (monitor) {
                        ++count;
                        monitor.notifyAll();
                    }
                    lock.lock();
                    while (sem.availablePermits() != numConsumers) {
                        condition.await();
                    }
                    lock.unlock();
                }
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
    static class Consumer implements Runnable {
        @Override
        public void run() {
            try {
                boolean isRead;
                int myCount = -1;

                synchronized (monitor){
                    sem.release();
                    while(!isHasMessage){
                        monitor.wait();
                    }
                }

                while(true) {
                    synchronized (monitor) {
                        System.out.println("thread - " + Thread.currentThread().getName() + " print globalData - " + globalData);
                        isRead = true;

                        sem.release();
                        lock.lock();
                        myCount = count;
                        condition.signal();
                        lock.unlock();

                        while(isRead){
                            monitor.wait();
                            if(myCount != count){
                                isRead = false;
                            }
                        }
                    }
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

class ProducerMoshe extends Thread {
    @Override
    public void run() {
        while(OneProducerMultipleConsumers.globalInt < 10) {
            try {
                OneProducerMultipleConsumers.semaphore.acquire(OneProducerMultipleConsumers.CONSUMERS);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

            synchronized (this) {
                produce();
                OneProducerMultipleConsumers.lockCon.lock();
                OneProducerMultipleConsumers.allConsumed.signalAll();
            }
            OneProducerMultipleConsumers.lockCon.unlock();
        }
    }

    private static void produce() {
        System.out.println("Produced the number: " + (++OneProducerMultipleConsumers.globalInt));
    }
}

class ConsumerMoshe extends Thread {
    @Override
    public void run() {
        while(OneProducerMultipleConsumers.globalInt < 10) {
            try {
                synchronized (this) {
                    OneProducerMultipleConsumers.lockCon.lock();
                    OneProducerMultipleConsumers.semaphore.release();
                }
                OneProducerMultipleConsumers.allConsumed.await();
                OneProducerMultipleConsumers.lockCon.unlock();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            consume();
        }
    }

    private void consume() {
        System.out.println("Consumer " + Thread.currentThread().getName() + ": Consumed - " + OneProducerMultipleConsumers.globalInt);
    }
}

