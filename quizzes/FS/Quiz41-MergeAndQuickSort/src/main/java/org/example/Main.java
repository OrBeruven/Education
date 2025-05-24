package org.example;

public class Main {
    public static void main(String[] args) {
        int[] arr = {5, 4, 9, 2, 1, 3};
        printArr(arr);

        mergeSort(arr);
        printArr(arr);
    }

    public static void printArr(int[] arr) {
        for (int i : arr) {
            System.out.print(i + ", ");
        }

        System.out.println();
    }
    public static void mergeSort(int[] arr) {
        mergeRec(arr, 0, arr.length);
    }

    private static void mergeRec(int[] arr, int l, int r) {
        if (l >= r) {
            return;
        }

        int m = (l + r) / 2;
        mergeRec(arr, l, m);
        mergeRec(arr, m + 1, r);

        mergeArray(arr, l, m, r);
    }

    private static void mergeArray(int[] arr, int l, int m, int r) {
        int length_l = m - l;
        int length_r = r - m;

        int[] left = new int[length_l];
        int[] right = new int[length_r];

        System.arraycopy(arr, l, left, 0, length_l);

        System.arraycopy(arr, m, right, 0, length_r);

        mergeArrays(arr, left, right, l);
    }

    private static void mergeArrays(int[] dest, int[] src1, int[] src2, int dest_start) {
        int indx1 = 0;
        int indx2 = 0;
        int indx_dest = 0;

        while (indx1 < src1.length && indx2 < src2.length) {
            if (src1[indx1] < src2[indx2]) {
                dest[dest_start + indx_dest] = src1[indx1];
                ++indx1;
            } else {
                dest[dest_start + indx_dest] = src2[indx2];
                ++indx2;
            }

            ++indx_dest;
        }

        while (indx1 < src1.length) {
            dest[dest_start + indx_dest] = src1[indx1];
            ++indx1;
            ++indx_dest;
        }

        while (indx2 < src2.length) {
            dest[dest_start + indx_dest] = src2[indx2];
            ++indx2;
            ++indx_dest;
        }
    }
}