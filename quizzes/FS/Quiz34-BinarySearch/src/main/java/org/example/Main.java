package org.example;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.RandomAccess;

public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");

        List<Integer> list = new ArrayList<>();
        list.add(1);
        list.add(2);
        list.add(3);
        list.add(4);
        list.add(5);
        list.add(6);
        list.add(7);
        list.add(8);

        System.out.println(binarySearch(list, 3));

        System.out.println(list.get(0));
        list.remove(0);
        System.out.println(list.get(0));
    }

    public static<K extends Comparable<K>> int binarySearch(List<K> list, K element) {
        if (list instanceof ArrayList<K> arrayList) {
            return IBinarySearch(arrayList, element);
        } else {
            return IBinarySearch(list, element);
        }
    }

    private static<K extends Comparable<K>> int IBinarySearch(ArrayList<K> list, K element) {
        System.out.println("In array list");
        int l = 0;
        int r = list.size() - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;

            if (list.get(m).equals(element)) {
                return m;
            } else if (list.get(m).compareTo(element) < 0) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        return -1;
    }

    private static<K extends Comparable<K>> int IBinarySearch(List<K> list, K element) {
        System.out.println("In list");
        int i = 0;

        for (K k : list) {
            if (k.equals(element)) {
                return i;
            }

            ++i;
        }

        return -1;
    }
}