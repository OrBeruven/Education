import java.util.HashMap;
import java.util.Map;

public class Main {
    private final static int RANGE = 10;

    public static void main(String[] args) {
        int[] arr1_1 = {1, 1, 2, 1};
        int[] arr1_2 = {1, 2, 1, 1};

        int[] arr2_1 = {1, 1, 1, 1, 3, 3, 3, 3};
        int[] arr2_2 = {3, 3, 3, 3, 1, 1, 1, 1};

        int[] arr3_1 = {1, 2, 1, 1, 3, 3, 3, 3};
        int[] arr3_2 = {3, 3, 3, 3, 1, 1, 1, 1};

        int[] arr4_1 = {-20000000, 23541231, 512313};
        int[] arr4_2 = {23541231, -20000000, 512313};
        System.out.println("No range, true? = " + IsLetterAmountEqual(arr1_1, arr1_2));
        System.out.println("No range, true? = " + IsLetterAmountEqual(arr2_1, arr2_2));
        System.out.println("No range, false? = " + IsLetterAmountEqual(arr3_1, arr3_2));
        System.out.println("No range, true? = " + IsLetterAmountEqual(arr4_1, arr4_2));

        System.out.println("Range, true? = " + IsLetterAmountEqualRange(arr1_1, arr1_2));
        System.out.println("Range, true? = " + IsLetterAmountEqualRange(arr2_1, arr2_2));
        System.out.println("Range, false? = " + IsLetterAmountEqualRange(arr3_1, arr3_2));
    }

    public static boolean IsLetterAmountEqual(int[] arr1, int[] arr2) {
        if (arr1.length != arr2.length) {
            return false;
        }

        Map<Integer, mapWrapper> map = new HashMap<>();

        for (int j : arr1) {
            addOrIncrement(map, j);
        }

        if (!subOrDecrement(map, arr2)) {
            return false;
        }

        for (Map.Entry<Integer, mapWrapper> en : map.entrySet()) {
            if (en.getValue().getVal() != 0) {
                return false;
            }
        }

        return true;
    }

    private static void addOrIncrement(Map<Integer, mapWrapper> map, int num) {
        mapWrapper value = null;

        if (null == (value = map.get(num))) {
            map.put(num, new mapWrapper());
        } else {
            value.incrementVal();
        }
    }

    private static boolean subOrDecrement(Map<Integer, mapWrapper> map, int[] arr) {
        mapWrapper value = null;

        for (int j : arr) {
            if (null == (value = map.get(Integer.valueOf(j)))) {
                return false;
            } else {
                value.decrementVal();
            }
        }

        return true;
    }

    public static boolean IsLetterAmountEqualRange(int[] arr1, int[] arr2) {
        if (arr1.length != arr2.length) {
            return false;
        }

        int[] lut = new int[RANGE];

        for (int j : arr1) {
            ++lut[j - 1];
        }

        for (int j : arr2) {
            --lut[j - 1];
        }

        for (int i = 0; i < RANGE; ++i){
            if (0 != lut[i]) {
                return false;
            }
        }

        return true;
    }

    static class mapWrapper {
        Integer val = 1;
        public void incrementVal() {
            ++val;
        }

        public void decrementVal() {
            --val;
        }

        public int getVal() {
            return this.val;
        }
    }
}