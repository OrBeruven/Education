package ex3;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        Ex3 ex3 = new Ex3();
        Thread producer = new Thread(new Producer(ex3));
        Thread consumer = new Thread(new Consumer(ex3));

        producer.start();
        consumer.start();

        producer.join();
        consumer.join();
    }
}
