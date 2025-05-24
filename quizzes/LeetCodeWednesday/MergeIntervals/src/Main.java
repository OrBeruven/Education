import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    private static final int END = 1;
    private static final int START = 0;
    public int[][] merge(int[][] intervals) {
        List<List<Integer>> nonLapInterval = new ArrayList<>();
        List<Integer> interval = new ArrayList<>(2);
        interval.add(-1);
        interval.add(-1);

        for (int i = 0; i < intervals.length; ++i) {
            if (make(intervals, nonLapInterval, i, interval)) {
                continue;
            }

            interval = new ArrayList<>(2);
            interval.add(-1);
            interval.add(-1);

            if (i == intervals.length - 1) {
                make(intervals, nonLapInterval, i, interval);
                nonLapInterval.add(interval);
            }
        }

        int[][] array = new int[nonLapInterval.size()][2];
        for (int i = 0; i < nonLapInterval.size(); ++i) {
            array[i][START] = nonLapInterval.get(i).get(START);
            array[i][END] = nonLapInterval.get(i).get(END);
        }

        return array;
    }

    private boolean make(int[][] intervals, List<List<Integer>> nonLapInterval, int i, List<Integer> interval) {
        if (-1 == interval.get(START)) {
            interval.set(START, intervals[i][START]);
            interval.set(END, intervals[i][END]);
            return true;
        } else if (intervals[i][START] < interval.get(END)) {
            if (intervals[i][END] < interval.get(END)) {
                return true;
            } else {
                interval.set(END, intervals[i][END]);
            }
        }

        nonLapInterval.add(interval);
        return false;
    }

    public static void main(String[] args) {
        int[][] x = { {1, 3}, {2, 6}, {8, 10} , {15, 18} };

        Solution solution = new Solution();
        int[][] array = solution.merge(x);

        for (int i = 0; i < array.length; ++i) {
            for (int j = 0; j < array[0].length; ++j) {
                System.out.println(array[i][j]);
            }
        }
    }
}