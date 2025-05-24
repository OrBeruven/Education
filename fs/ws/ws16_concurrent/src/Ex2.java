/***************************
 *  Written by : Or
 *  Reviewer : Neviu
 *  Date : 11.07.2023
 ***************************/
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class Ex2 {
    public static int globalCounter = 0;
    public final static Object monitor = new Object();
    public static AtomicInteger atomicCounter = new AtomicInteger(0);
    public static ReentrantLock reentrantLock = new ReentrantLock();
    public static void main(String[] args) throws InterruptedException {
        long startTime = System.nanoTime();

        Thread thread1 = new Thread1();
        Thread thread2 = new Thread2();

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();

        long endTime = System.nanoTime() - startTime;

        System.out.println("globalCounter current state : " + globalCounter);
        System.out.println("It took : " + (endTime/1000000) + "ms");
    }


    static class Thread1 extends Thread {
        /*Before optimization
        public void run(){
            for (int i = 0; i < 10000000; ++i) {
                ++globalCounter;
            }
        }*/

        /*Synchronized method*/
        public void run(){
            for (int i = 0; i < 10000000; ++i) {
                incrementGlobalCounter();
            }
        }

        /*Synchronized block
        public void run() {
            synchronized (monitor) {
                for (int i = 0; i < 10000000; ++i) {
                    ++globalCounter;
                }
            }
        }*/

        /*Atomic
        public void run() {
            for (int i = 0; i < 10000000; ++i) {
                atomicCounter.incrementAndGet();
            }
        }*/

        /*ReentrantLock
        public void run() {
            reentrantLock.lock();
            for (int i = 0; i < 10000000; ++i) {
                atomicCounter.incrementAndGet();
            }
            reentrantLock.unlock();
        }*/
    }

    static class Thread2 extends Thread {
        /*Before optimization
        public void run(){
            for (int i = 0; i < 10000000; ++i) {
                ++globalCounter;
            }
        }*/

        /*Synchronized method*/
        public void run(){
            for (int i = 0; i < 10000000; ++i) {
                incrementGlobalCounter();
            }

        }

        /*Synchronized block
        public void run() {
            synchronized (monitor) {
                for (int i = 0; i < 10000000; ++i) {
                    ++globalCounter;
                }
            }
        }*/

        /*Atomic
        public void run() {
            for (int i = 0; i < 10000000; ++i) {
                atomicCounter.incrementAndGet();
            }
        }*/

        /*ReentrantLock
        public void run() {
            reentrantLock.lock();
            for (int i = 0; i < 10000000; ++i) {
                atomicCounter.incrementAndGet();
            }
            reentrantLock.unlock();
        }*/
    }

    synchronized public static void incrementGlobalCounter() {
            ++globalCounter;
    }
}

