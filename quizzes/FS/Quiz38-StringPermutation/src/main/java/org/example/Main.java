package org.example;

public class Main {
    public static void main(String[] args) {
        stringPermutation("ABCef");
    }

    public static void stringPermutation(String str) {
        printPermute(str.toCharArray(), 0, str.length());
    }

    private static void printPermute(char[] str, int l, int r) {
        if (l == r) {
            System.out.println(String.valueOf(str));
            return;
        }

        for (int i = l; i < r; ++i) {
            swapChars(str, l, i);
            printPermute(str, l + 1, r);
            swapChars(str, l, i);
        }
    }

    private static void swapChars(char[] arr, int a, int b) {
        char temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }
}