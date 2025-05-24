public class Main {
    public static void main(String[] args) {
        int[] arr1 = {-2, -3, 4, -1, -2, 1, 5, -3};
        int[] arr2 = {6, -3, 4, -1, -2, 1, 5, -3};
        int[] arr3 = {0, 2, -3, 2, 6, -4, 8, 2, 1};
        int[] arr4 = {0, -2, -3, -2, -6, -4, -8, -2, -1};
        int[] arr5 = {-2, -1, -3, -2, -6, -4, -8, -2, -2};

        System.out.println("2 - 6 ? = ");
        largestSumSubarray(arr1);
        System.out.println();

        System.out.println("0 - 6 ? = ");
        largestSumSubarray(arr2);
        System.out.println();

        System.out.println("3 - 8 ? = ");
        largestSumSubarray(arr3);
        System.out.println();

        System.out.println("0 - 0 ? = ");
        largestSumSubarray(arr4);
        System.out.println();

        System.out.println("1 - 1 ? = ");
        largestSumSubarray(arr5);
        System.out.println();
    }

    public static void largestSumSubarray(int[] arr) {
        int currSum = arr[0];
        int start = 0, end = 0;
        int nextSum = 0;

        for (int i = 1; i < arr.length; ++i) {
            nextSum = currSum + arr[i];
            if (nextSum > currSum) {
                if (currSum <= 0) {
                    start = i;
                    currSum = arr[i];
                } else {
                    currSum = nextSum;
                }

                end = i;
            } else {
                currSum = nextSum;
            }
        }

        System.out.println("Start : " + start + " End : " + end);
    }
}