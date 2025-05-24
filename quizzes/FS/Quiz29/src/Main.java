import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Main {
    public static void main(String[] args) {
        Tree t13 = new Tree(13, null, null, null);
        Tree t12 = new Tree(12, null, null, null);
        Tree t11 = new Tree(11, null, null, null);
        Tree t4 = new Tree(4, t11, t12, t13);

        Tree t10 = new Tree(10, null, null, null);
        Tree t9 = new Tree(9, null, null, null);
        Tree t8 = new Tree(8, null, null, null);
        Tree t3 = new Tree(3, t8, t9, t10);

        Tree t7 = new Tree(7, null, null, null);
        Tree t6 = new Tree(6, null, null, null);
        Tree t5 = new Tree(5, null, null, null);
        Tree t2 = new Tree(2, t5, t6, t7);

        Tree t1 = new Tree(1, t2, t3, t4);

        printZigZag(t1, 3);
    }

    static class Tree {
        Tree[] children;
        int val;

        Tree (int val, Tree c1, Tree c2, Tree c3) {
            this.val = val;
            this.children = new Tree[3];
            this.children[0] = c1;
            this.children[1] = c2;
            this.children[2] = c3;
        }
    }

    public static void printZigZag(Tree root, int n) {
        List<Tree> arr = new ArrayList<>();
        Queue<Tree> que = new LinkedList<>();
        int powerLevel = 0;

        que.add(root);

        while (!que.isEmpty()) {
            while (!que.isEmpty()) {
                arr.add(que.remove());
            }

            for (Tree node : arr) {
                for (int i = 0; i < n; ++i) {
                    if (null == node.children[i]) {
                        continue;
                    }
                    que.add(node.children[i]);
                }
            }

            if (powerLevel % 2 == 0) {
                printInOrder(arr);
            } else {
                printReverseOrder(arr);
            }

            ++powerLevel;
        }
    }

    private static void printInOrder(List<Tree> arr) {
        for (Tree node : arr) {
            System.out.print(node.val + " ");
        }

        System.out.println();
        arr.clear();
    }

    private static void printReverseOrder(List<Tree> arr) {
        for (int i = arr.size() - 1; i >= 0; --i) {
            System.out.print(arr.get(i).val + " ");
        }

        System.out.println();
        arr.clear();
    }
}