/**
 * Definition for a binary tree node.*/
public class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}
class Solution {
    private static int level = 0;
    private static int sum = 0;

    public int deepestLeavesSum(TreeNode root) {
        if (null == root) {
            return 0;
        }
        level = 0;
        sum = 0;
        recursiveSumDeepest(root, 0);
        return sum;
    }

    private static void recursiveSumDeepest(TreeNode node, int currLevel) {
        if (null == node) {
            return;
        }

        recursiveSumDeepest(node.left, currLevel + 1);
        recursiveSumDeepest(node.right, currLevel + 1);

        if (currLevel == level) {
            sum += node.val;
        } else if (currLevel > level) {
            level = currLevel;
            sum = node.val;
        }
    }
}