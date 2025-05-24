public class Main {
    public static void main(String[] args) {
        interface SomeInterface {
            default void foo() {
                System.out.println("my foo");
            }
        }

        class SomeClass implements SomeInterface {
            @Override
            public void foo() {
                System.out.println("my new foo!");
            }
        }

        SomeClass sc = new SomeClass();
        sc.foo();
    }
}