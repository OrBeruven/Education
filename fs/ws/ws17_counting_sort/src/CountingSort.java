/***************************
 *  Written by : Or
 *  Reviewer : Lilach
 *  Date : 11.07.2023
 *  Counting sort Implementation
 ***************************/
public class CountingSort {
    private final static int ASCII = 256;
    private static final int[] mergedCount = new int[ASCII];
    public static char[] countSort(char[] arr, int numOfThreads) {
        final Thread[] threads = new Thread[numOfThreads];
        int sizeToCount = arr.length / numOfThreads;
        int from = 0;
        int to = sizeToCount - 1;
        int remainder = arr.length % numOfThreads;
        --numOfThreads;

        for (int i = 0; i < numOfThreads; ++i) {
            threads[i] = new CountingThread(arr, from, to);
            threads[i].start();
            from += sizeToCount;
            to += sizeToCount;
        }

        threads[numOfThreads] = new CountingThread(arr, from, to + remainder);
        threads[numOfThreads].start();

        ++numOfThreads;
        for (int i = 0; i < numOfThreads; ++i) {
            try {
                threads[i].join();
            } catch (Exception e) {
                System.out.println("Exception : " + e);
            }
        }

        finalizeSort(arr);
        return arr;
    }

    private static class CountingThread extends Thread {
        private int from = 0;
        private int to = 0;
        private final int[] threadArray = new int[ASCII];
        private final char[] arrayToSort;
        CountingThread(char[] arr, int from, int to) {
            this.arrayToSort = arr;
            this.from = from;
            this.to = to;
        }

        @Override
        public void run() {
            for (; from <= to; ++from) {
                ++threadArray[arrayToSort[from]];
            }

            synchronized (mergedCount) {
                for (int i = 0; i < ASCII; ++i) {
                    mergedCount[i] += threadArray[i];
                }
            }
        }
    }

    private static void finalizeSort(char[] arrayToSort) {
        int arrIndex = 0;
        for (int i = 0; i < ASCII; ++i) {
            while (mergedCount[i] > 0 ) {
                arrayToSort[arrIndex] = (char) i;
                --mergedCount[i];
                ++arrIndex;
            }
        }
    }
}