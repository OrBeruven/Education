/***************************
 *  Written by : Or
 *  Reviewer : Neviu
 *  Date : 11.07.2023
 ***************************/
package ex3;
import java.util.concurrent.atomic.AtomicBoolean;

public class AtomicVarPingPong {
    public static void main(String[] args) {
        AtomicBoolean var = new AtomicBoolean(true);
        Thread ping = new Thread(new AtomicVarPing(var));
        Thread pong = new Thread(new AtomicVarPong(var));
        ping.start();
        pong.start();
    }
}

class AtomicVarPing implements Runnable {
    AtomicBoolean var = null;

    public AtomicVarPing(AtomicBoolean var) {
        this.var = var;
    }

    @Override
    public void run() {
        while (true) {
            while (!var.get());

            System.out.println("Ping");
            try {
                Thread.sleep(1000);

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }

            var.set(false);
        }
    }
}

class AtomicVarPong implements Runnable {
    AtomicBoolean var = null;

    public AtomicVarPong(AtomicBoolean var) {
        this.var = var;
    }

    @Override
    public void run() {
        while (true) {
            while (var.get());

            System.out.println("Pong");
            try {
                Thread.sleep(1000);

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }

            var.set(true);
        }
    }
}


