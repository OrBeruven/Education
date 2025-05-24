import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class TestStaticClass {
    int num = 0;

    TestStaticClass(int num) {
        this.num = num;
        ExecutorService ex = Executors.newFixedThreadPool(2);
    }

    public void print() {
        this.Inner.print();
        System.out.println("Outer");
    }

    class Inner extends TestStaticClass {
        @Override
        public void print() {
            super.print();
            System.out.println("Innter");
        }
    }

    public static void main(String[] args) {
        TestStaticClass testStaticClass = new TestStaticClass(3);

        TestStaticClass.Inner inner = testStaticClass.new Inner();
    }
}
