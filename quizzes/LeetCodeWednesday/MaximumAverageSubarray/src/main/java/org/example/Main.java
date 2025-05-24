package org.example;

public class Main {
    public static void main(String[] args) {
        Main main = new Main();

        int[] nums = {1,12,-5,-6,50,3};
        System.out.println(main.findMaxAverage(nums, 4));
    }

    public double findMaxAverage(int[] nums, int k) {
        if (nums.length == k) {
            return firstSum(nums, k);
        }

        int leftIndex = 0;
        int bestSum = 0;
        int currSum = 0;

        bestSum = firstSum(nums, k);
        currSum = bestSum;

        for (int rightIndex = k; rightIndex < nums.length; ++rightIndex, ++leftIndex) {
            currSum -= nums[leftIndex];
            currSum += nums[rightIndex];

            if (currSum > bestSum) {
                bestSum = currSum;
            }
        }

        return ((double)bestSum / k);
    }

    private int firstSum(int[] nums, int k) {
        int currSum = 0;
        for (int i = 0; i < k; ++i) {
            currSum += nums[i];
        }

        return currSum;
    }
}