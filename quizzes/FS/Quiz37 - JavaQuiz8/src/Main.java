public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");
    }
}

class A<T> {
    public void foo(Object o) {}
    public void foo(T t) {}
}

class B<T> {
    public void foo (Object o) {}
    public <Z extends Number>void foo (Z t) {}
}

class C<T extends Number> {
    public void foo (Object o) {}
    public void foo (T t) {}
}