public class Main {
    public static void main(String[] args) {
        printReverse("ABC");

        System.out.println("1 = " + isPalindrome("1"));
        System.out.println("2222 = " + isPalindrome("2222"));
        System.out.println("12321 = " + isPalindrome("12321"));
        System.out.println("112321 = " + isPalindrome("112321"));

        printAllPermutation("abc", "");
    }

    private static void printReverse(String str) {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(str);
        stringBuilder.reverse();
        System.out.println(stringBuilder);

        String toRet = "";
        char ch = 0;
        for (int i = 0; i < str.length(); ++i) {
            ch = str.charAt(i);
            toRet = ch + toRet;
        }
        System.out.println(toRet);
    }

    private static boolean isPalindrome(String str) {
        int length = str.length() / 2;

        for (int i = 0; i < length; ++i) {
            if (str.charAt(i) != str.charAt(str.length() - i - 1)) {
                return false;
            }
        }

        return true;
    }

    private static void printAllPermutation(String str, String ans)
    {
        if (str.length() == 0) {
            System.out.print(ans + " ");
            return;
        }

        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);
            String ros = str.substring(0, i) + str.substring(i + 1);
            printAllPermutation(ros, ans + ch);
        }
    }
}