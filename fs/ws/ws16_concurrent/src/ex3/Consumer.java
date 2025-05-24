package ex3;
public class Consumer implements Runnable {
    private Ex3 ex3;

    Consumer(Ex3 ex3) {
        this.ex3 = ex3;
    }
    @Override
    public void run() {
        for (String s = ex3.consumer(); !"9".equals(s); s = ex3.consumer()) {
            System.out.println("Consumed : " + s);

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

    }
}
