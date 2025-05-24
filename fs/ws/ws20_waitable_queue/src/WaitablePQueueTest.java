/*
 *       Programmer : Or
 *       Reviewer : Neviu
 *       Date : 18.07.2023
 *       Description : WaitableQueue Testing
 */
import WaitablePQueue.*;

import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;

import java.util.Random;
import java.util.concurrent.PriorityBlockingQueue;
import java.util.concurrent.TimeoutException;
import static org.junit.jupiter.api.Assertions.*;


@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
class WaitablePQueueTest {

    public static WaitablePQueue<Integer> wpq = new WaitablePQueue<>(Integer::compareTo);

    @Test
    @Order(1)
    void enqueTest() throws InterruptedException {
        Thread[] threads = new Thread[10];

        for (int i = 0; i < 10; ++i) {
            threads[i] = new enqueThread();
            threads[i].start();
        }

        for (int i = 0; i < 10; ++i) {
            threads[i].join();
        }
    }

    @Test
    @Order(2)
    void dequeTest() throws InterruptedException {
        Thread[] threads = new Thread[10];

        for (int i = 0; i < 10; ++i) {
            threads[i] = new dequeThread();
            threads[i].start();
        }

        for (int i = 0; i < 10; ++i) {
            wpq.enque(i);
        }

        for (int i = 0; i < 10; ++i) {
            threads[i].join();
        }
    }

    @Test
    @Order(3)
    void testdeque() throws InterruptedException {
        Thread[] enqueThreads = new Thread[10];
        Thread[] dequeThreads = new Thread[10];

        for (int i = 0; i < 10; ++i) {
            dequeThreads[i] = new TimeddequeThread();
            dequeThreads[i].start();
            enqueThreads[i] = new enqueThread();
            enqueThreads[i].start();
        }

        for (int i = 0; i < 10; ++i) {
            enqueThreads[i].join();
            dequeThreads[i].join();
        }
    }

    @Test
    @Order(4)
    void removeTest() throws InterruptedException {
        enqueByNumberThread[] enqueByNumberThread = new enqueByNumberThread[100];
        RemoveThread[] removeThreads = new RemoveThread[100];

        for (int i = 0; i < 100; ++i) {
            enqueByNumberThread[i] = new enqueByNumberThread(i);
            enqueByNumberThread[i].start();
        }

        for (int i = 0; i < 100; ++i) {
            enqueByNumberThread[i].join();
        }

        for (int i = 0; i < 100; ++i) {
            removeThreads[i] = new RemoveThread(i);
            removeThreads[i].start();
        }

        for (int i = 0; i < 100; ++i) {
            removeThreads[i].join();
        }

        assertFalse(WaitablePQueueTest.wpq.remove(40));
    }

    @Test
    void create() throws InterruptedException, TimeoutException {
        WaitablePQueue<Integer> wpq = new WaitablePQueue();
        wpq.enque(1);
        wpq.enque(2);
        wpq.enque(3);
        wpq.enque(4);
        wpq.enque(5);
        wpq.enque(6);
        wpq.enque(7);
        wpq.enque(8);

        assertEquals(wpq.deque(), 1);
        assertEquals(wpq.deque(), 2);
        assertEquals(wpq.deque(), 3);
        assertEquals(wpq.deque(), 4);
        assertEquals(wpq.deque(), 5);
        assertEquals(wpq.deque(), 6);
        assertEquals(wpq.deque(), 7);
        assertEquals(wpq.deque(), 8);}
}

class enqueThread extends Thread {
    @Override
    public void run() {
        Random rand = new Random();
        int toInsert = rand.nextInt();

        assertTrue(WaitablePQueueTest.wpq.enque(toInsert));
        System.out.println("inserted: " + toInsert);
    }
}

class enqueByNumberThread extends Thread {
    int num = 0;

    enqueByNumberThread(int num) {
        this.num = num;
    }
    @Override
    public void run() {
        assertTrue(WaitablePQueueTest.wpq.enque(num));
        System.out.println("inserted: " + num);

    }
}

class RemoveThread extends Thread {
    Object obj = null;

    RemoveThread(Object obj) {
        this.obj = obj;
    }
    @Override
    public void run() {
        assertTrue(WaitablePQueueTest.wpq.remove(obj));
        System.out.println("removed: " + obj);
    }
}

class dequeThread extends Thread {
    @Override
    public void run() {
        try {
            System.out.println("dequed: " + WaitablePQueueTest.wpq.deque());
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}

class TimeddequeThread extends Thread {
    @Override
    public void run() {
        try {
            System.out.println("dequed: " + WaitablePQueueTest.wpq.deque(10000000));
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

    }
}
