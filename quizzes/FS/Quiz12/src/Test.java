public class Test {
    public static void main(String[] args) {
        System.out.println(func());
    }

    static int x = 5;
    static int func() {
        static int x = 10;
        return --Test.x;
    }
}

public static <T extends Comparable<T>> int findFirstGreaterThan(T[] at, T element) {...}
