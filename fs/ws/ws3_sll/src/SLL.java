import java.util.Iterator;

public class SLL {

    private long size;
    private Node head;
    int a = 5;

    private class Node {
        private Object data;
        private Node next;

        private Node(Object data) {
            this.data = data;
            this.next = null;
        }
    }
    private class IterImp implements ListIterator {
        private Node node;
        private IterImp(Node node) {
            this.node = node;
        }
        @Override
        public Object next() {
            Object obj = this.node.data;
            this.node = this.node.next;
            return obj;
        }

        @Override
        public boolean hasNext() {
            return (this.node.next != null);
        }

        @Override
        public void print() {
            System.out.println(this.node.data);
        }
    }

    SLL() {
        this.size = 0;
        this.head = null;
    }
    public void pushFront(Object data) {
        Node temp = new Node(data);
        if (this.head == null) {
            this.head = temp;
        } else {
            temp.next = this.head;
            this.head = temp;
        }
        size++;
    }
    public Object popFront() {
        Object obj = this.head.data;
        this.head = this.head.next;
        --size;
        return obj;
    }

    public ListIterator find(Object obj) {
        Node iterNode = this.head;
        while (iterNode != null && !iterNode.data.equals(obj))
        {
            iterNode = iterNode.next;
        }
        return iterNode == null ? null : new IterImp(iterNode);
    }
    public ListIterator begin() {
        return new IterImp(this.head);
    }
    public long getSize() {
        return this.size;
    }
    public boolean isEmpty() {
        return (0 == size);
    }
}
