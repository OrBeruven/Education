public class Main {
    static Node newNode(int key) {
        Node node = new Node();
        node.key = key;
        node.left = node.right = null;
        return node;
    }

    // main function which converts a given binary tree to a doubly linked list using recursion
    private static Node recursiveConvert(Node root) {
        if (root == null)
            return root;

        if (root.left != null) {
            Node curr = recursiveConvert(root.left);
            while (null != curr.right) {
                curr = curr.right;
            }

            curr.right = root;
            root.left = curr;
        }

        if (root.right != null) {
            Node curr = recursiveConvert(root.right);
            while (null != curr.left) {
                curr = curr.left;
            }

            curr.left = root;
            root.right = curr;
        }

        return root;
    }

    public static Node treeToList(Node node) {
        if (node == null)
            return node;

        node = recursiveConvert(node);
        while (node.left != null) {
            node = node.left;
        }

        return node;
    }


    static void inorder(Node root)
    {
        // base condition
        if (root == null) {
            return;
        }
        inorder(root.left);
        inorder(root.right);
    }

    static void printDLL(Node root) {
        while (root != null) {
            System.out.print(root.key + ", ");
            root = root.right;
        }
    }

    public static void main(String[] args) {
        /*    10
            /   \
              6     14
            / \     / \
          4   8     12  16 */

        Node root = newNode(10);
        root.left = newNode(6);
        root.right = newNode(14);
        root.left.left = newNode(4);
        root.left.right = newNode(8);
        root.right.left = newNode(12);
        root.right.right = newNode(16);
        inorder(root);
        System.out.println();

        printDLL(treeToList(root));
    }

}


class Node {
    int key;
    Node left, right;
}