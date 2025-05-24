public class Outer {
    static int a = 1;
    int b = 2;
    private class Innter {
        void foo2() {
            a
        }
    }
    private static class Nested {

    }
    void foo() {
        class Local{}
    }
}