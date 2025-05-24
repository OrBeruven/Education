import java.util.PriorityQueue;

public class Main {
    public static void main(String[] args) {
        Integer[] intput = {10, 20, 11, 70, 50, 40, 100, 5};

        for (Integer i : KthLargest(intput, intput.length, 3)) {
            System.out.print(i + ", ");
        }
    }

    public static Integer[] KthLargest(Integer[] input, int n, int k) {
        Integer[] output = new Integer[n];
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        for (int i = 0; i < n; ++i) {
            if (minHeap.size() < k) {
                minHeap.add(input[i]);
            } else {
                if (input[i] > minHeap.peek()) {
                    minHeap.remove();
                    minHeap.add(input[i]);
                }
            }

            output[i] = (minHeap.size() < k) ? Integer.valueOf(-1) : minHeap.peek();
        }

        return output;
    }
}