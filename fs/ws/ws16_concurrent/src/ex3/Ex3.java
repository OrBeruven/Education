package ex3;
/*
public class Ex3 {
    public static LinkedList<Integer> list = new LinkedList<>();
    public static int capacity = 2;
    public final static Object monitor = new Object();
    public static class Producer extends Thread{
        public void run() {
            Integer dataToProduce = 0;
            while (true) {
                synchronized (monitor) {
                    while (list.size() == capacity) {
                        try {
                            wait();
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }

                    System.out.println("Producer produced : " + dataToProduce);
                    list.add(dataToProduce++);

                    notifyAll();

                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }
    }

    public static class Consumer extends Thread{
        public void run() {
            Integer dataConsumed = 0;

            while (true) {
                synchronized (monitor) {
                    while (list.isEmpty()) {
                        try {
                            wait();
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }

                    dataConsumed = list.removeFirst();
                    System.out.println("Consumer consumed : " + dataConsumed);

                    notifyAll();

                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread producer = new Producer();
        Thread consumer = new Consumer();

        producer.start();
        consumer.start();

        producer.join();
        consumer.join();
    }
}*/

public class Ex3{
    private String data = null;
    private boolean shouldWait = true;

    public synchronized String consumer() {
        while (shouldWait) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        shouldWait = true;

        String dataToConsume = data;
        notifyAll();
        return dataToConsume;
    }

    public synchronized void produce(String newData) {
        while (!shouldWait) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        shouldWait = false;

        this.data = newData;
        notifyAll();
    }
}
