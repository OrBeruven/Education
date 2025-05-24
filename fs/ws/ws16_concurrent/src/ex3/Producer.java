package ex3;
public class Producer implements Runnable {
    private Ex3 ex3;

    Producer(Ex3 ex3) {
        this.ex3 = ex3;
    }
    @Override
    public void run() {
        for (Integer counter = 0; counter < 10; ++counter) {
            ex3.produce(counter.toString());
            System.out.println("Produced : " + counter.toString());

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
