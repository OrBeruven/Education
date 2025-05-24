package org.example;

public class Main {
    public static void main(String[] args) {
        Integer[] arr = {4, 2, 6, 3, 6, 1};
        printArr(arr);

        bubbleSort(arr);
        printArr(arr);
    }

    public static<K extends Comparable<K>> void insertSort(K[] arr) {
        for (int i = 0; i < arr.length; ++i) {
            for (int j = i; j > 0; --j) {
                if (arr[j].compareTo(arr[j - 1]) >= 0) {
                    break;
                } else {
                    swapObj(arr, j, j - 1);
                }
            }
        }
    }

    public static<K extends Comparable<K>> void selectSort(K[] arr) {
        int smallestIndex = 0;

        for (int i = 0; i < arr.length; ++i) {
            smallestIndex = i;

            for (int j = i + 1; j < arr.length; ++j) {
                if (arr[j].compareTo(arr[smallestIndex]) < 0) {
                    smallestIndex = j;
                }
            }

            swapObj(arr, smallestIndex, i);
        }
    }

    public static<K extends Comparable<K>> void bubbleSort(K[] arr) {
        boolean swapped = false;

        for (int i = 0; i < arr.length - 1; ++i) {
            for (int j = 0; j < arr.length - 1; ++j) {
                if (arr[j].compareTo(arr[j + 1]) > 0) {
                    swapObj(arr, j, j + 1);
                    swapped = true;
                }
            }

            if (!swapped) {
                 break;
            }
        }
    }

    private static<K> void swapObj(K[] arr, int a, int b) {
        K temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    public static<K> void printArr(K[] arr) {
        for (K k : arr) {
            System.out.print(k.toString() + ", ");
        }

        System.out.println();
    }
}