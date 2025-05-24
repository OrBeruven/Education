import java.io.IOException;

public class Foo {
    void func1() throws IOException {
        throw new IOException();
    }

    void func2() {
        throw new NullPointerException();
    }
    void func3() throws MyException2 {
        throw new MyException2();
    }
    void func4() {
        throw new MyException1();
    }

    public static void main(String[] args) {
        Foo foo = new Foo();
        try {
            foo.func1();
        }
        catch (IOException e) {
            System.out.println("HELLOOO");
        }
        //foo.func2();

        try {
            foo.func3();
        }
        catch (IOException e) {
            System.out.print("HELLOOO My Exception2 : ");
            System.out.println(e.getMessage());
        }

        foo.func4();

        /*byte[] arr = new byte[100];
        arr[101] = 1;*/
    }

    class MyException1 extends RuntimeException {
        static final String errMsg = "MyException1 RuntimeException";

        MyException1() {
            super(errMsg);
        }
    }

    class MyException2 extends IOException {
        static final String errMsg = "MyException2 IOException";
        MyException2() {
            super(errMsg);
        }
    }
}