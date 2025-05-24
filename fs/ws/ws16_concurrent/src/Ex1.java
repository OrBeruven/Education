public class Ex1 {
    public static void main(String[] args) throws InterruptedException {
        Thread threadOfThread = new RunTaskThread();
        Thread threadOfRunnable = new Thread(new RunTaskRunnable());

        threadOfThread.start();
        threadOfThread.join();

        threadOfRunnable.start();
        threadOfRunnable.join();
        System.out.println("In public class Thread");
    }

}
class RunTaskThread extends Thread {
    public void run() {
        System.out.println("In thread extending Thread");
    }
}

class RunTaskRunnable implements Runnable {

    @Override
    public void run() {
        System.out.println("In thread implements Runnable");
    }
}
