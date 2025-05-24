public class JavaQuiz1 {
    public static void main(String[] args) {
        Q5();
    }
    public static void Q1() {
        String s1 = "hi";
        String s2 = new String("hi");
        String s3 = "hi";

        if (s1 == s2) {
            System.out.println("1 2 equal");
        } else {
            System.out.println("1 2 not equal");
        }

        if (s1 == s3) {
            System.out.println("1 3 equal");
        } else {
            System.out.println("1 3 not equal");
        }
    }


    public static void Q3() {
        Integer i = 10;
        Integer j = 11;
        Integer k = new Integer(11);
        System.out.println("k == j is " + (k == j));
        System.out.println("k.equals(j) is " + k.equals(j));
    }

    public static void Q4() {
        int[] arr1 = {1, 2, 3, 4, 5};
        int[] arr2 = {1, 2, 3, 4, 5};

        System.out.println("arr1 = arr2 is " + (arr1 == arr2));
        System.out.println("arr1.equals(arr2) is " + arr1.equals(arr2));
    }

    public static void foo(Integer i) { System.out.println("foo(Integer)"); }
    public static void foo(short i) { System.out.println("foo(short)"); }
    public static void foo(long i) { System.out.println("foo(long)"); }
    public static void foo(int ... i) { System.out.println("foo(int ...)"); }

    public static void Q5() {
        foo(10);
    }
}