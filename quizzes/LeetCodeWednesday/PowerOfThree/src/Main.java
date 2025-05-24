public class Main {
    public static void main(String[] args) {
        Main main = new Main();
        System.out.println(main.isPowerOfThree(19684));
    }

    public boolean isPowerOfThree(int n) {
        if (0 >= n) {
            return false;
        }

        while (n % 3 == 0) {
            n /= 3;
        }

        return n == 1;
    }
}