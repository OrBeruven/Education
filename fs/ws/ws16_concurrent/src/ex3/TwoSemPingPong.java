/***************************
 *  Written by : Or
 *  Reviewer : Neviu
 *  Date : 11.07.2023
 ***************************/
package ex3;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicBoolean;

public class TwoSemPingPong {
    public static void main(String[] args) {
        Semaphore pingSemaphore = new Semaphore(1);
        Semaphore pongSemaphore = new Semaphore(1);
        Thread ping = new Thread(new TwoSemPing(pingSemaphore, pongSemaphore));
        Thread pong = new Thread(new TwoSemPong(pingSemaphore, pongSemaphore));
        ping.start();
        pong.start();
    }
}

class TwoSemPing implements Runnable {
    Semaphore pingSem = null;
    Semaphore pongSem = null;

    public TwoSemPing(Semaphore pingSem, Semaphore pongSem) {
        this.pingSem = pingSem;
        this.pongSem = pongSem;
    }

    @Override
    public void run() {
        while (true) {
            try {
                Thread.sleep(1000);
                pingSem.acquire();
                System.out.println("Ping");
                pongSem.release();

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

class TwoSemPong implements Runnable {
    Semaphore pingSem = null;
    Semaphore pongSem = null;

    public TwoSemPong(Semaphore pingSem, Semaphore pongSem) {
        this.pingSem = pingSem;
        this.pongSem = pongSem;
    }

    @Override
    public void run() {
        while (true) {
            try {
                pongSem.acquire();
                System.out.println("Pong");
                Thread.sleep(1000);
                pingSem.release();

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

