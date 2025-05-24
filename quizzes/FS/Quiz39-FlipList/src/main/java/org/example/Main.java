package org.example;

public class Main {
    public static void main(String[] args) {
        Node head = new Node(1, new Node(2, new Node(3, new Node(4, new Node(5)))));
        printList(head);
        printList(flipList(head));
    }

    static class Node {
        private int value;
        private Node next;

        public Node(int value) {
            this(value, null);
        }

        public Node(int value, Node next) {
            this.value = value;
            this.next = next;
        }

        public int getValue() {
            return value;
        }

        public Node getNext() {
            return next;
        }

        public void setValue(int value) {
            this.value = value;
        }

        public void setNext(Node next) {
            this.next = next;
        }
    }

    public static Node flipList(Node head) {
        if (null == head) {
            return null;
        }

        Node prev = null;
        Node next = head.getNext();;

        while (null != next) {
            head.setNext(prev);
            prev = head;
            head = next;
            next = next.getNext();
        }

        head.setNext(prev);
        return head;
    }

    public static void printList(Node head) {
        while (null != head) {
            System.out.print(head.getValue() + ", ");
            head = head.getNext();
        }
        System.out.println();
    }
}