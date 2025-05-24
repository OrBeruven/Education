/***************************
 *  Written by : Or
 *  Reviewer : Neviu
 *  Date : 11.07.2023
 ***************************/
package ex3;

import java.util.LinkedList;
import java.util.concurrent.Semaphore;

public class MultipleProducersMultipleConsumers {
    public static void main(String[] args) throws InterruptedException {
        LinkedList<Integer> shared = new LinkedList<>();
        final MonitorObject monitor = new MonitorObject();
        Semaphore sem = new Semaphore(0);

        Thread producer1 = new Thread(new Producers(shared, monitor, sem));
        Thread producer2 = new Thread(new Producers(shared, monitor, sem));
        Thread producer3 = new Thread(new Producers(shared, monitor, sem));

        Thread consumer1 = new Thread(new Consumers(shared, monitor, sem));
        Thread consumer2 = new Thread(new Consumers(shared, monitor, sem));
        Thread consumer3 = new Thread(new Consumers(shared, monitor, sem));

        producer1.start();
        consumer1.start();
        producer2.start();
        consumer2.start();
        producer3.start();
        consumer3.start();

        producer1.join();
        consumer1.join();
        producer2.join();
        consumer2.join();
        producer3.join();
        consumer3.join();
    }
}

class Producers implements Runnable {
    LinkedList<Integer> shared = null;
    final MonitorObject monitor;
    Semaphore sem = null;

    public Producers(LinkedList<Integer> shared, MonitorObject monitor, Semaphore sem) {
        this.shared = shared;
        this.monitor = monitor;
        this.sem = sem;
    }

    @Override
    public void run() {
        for (int i = 0; i < 3; ++i) {
            synchronized (monitor) {
                try {
                    Thread.sleep(300);
                    System.out.println("Produced : " + ++monitor.counter);
                    shared.add(monitor.counter);
                    sem.release();

                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }
}

class Consumers implements Runnable {
    LinkedList<Integer> shared = null;
    final MonitorObject monitor;
    Semaphore sem = null;


    public Consumers(LinkedList<Integer> shared, MonitorObject monitor, Semaphore sem) {
        this.shared = shared;
        this.monitor = monitor;
        this.sem = sem;
    }

    @Override
    public void run() {
        for (int i = 0; i < 3; ++i) {
            try {
                sem.acquire();
                synchronized (monitor) {
                    Thread.sleep(300);
                    System.out.println("Consumed : " + shared.removeFirst());
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

class MonitorObject {
    int counter = 0;
}
