package innerclasses;

public class AnotherMain {
    public void foo() {
        class AIC {
            public static void foo2() {
                System.out.println("Print");
            }
        }
        AIC.foo2();
    }
}