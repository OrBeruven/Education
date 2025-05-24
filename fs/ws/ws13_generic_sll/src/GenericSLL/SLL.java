package GenericSLL;

import java.time.LocalDateTime;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class SLL<E> implements Iterable<E>{
    private Node head = null;
    private LocalDateTime sllModCount = LocalDateTime.now();

    private class Node {
        private E data = null;
        private Node next = null;
        private Node(E data, Node next) {
            this.data = data;
            this.next = next;
        }

        private E getData() {
            return this.data;
        }

        private Node getNext() {
            return this.next;
        }

        private void setNext(Node next) {
            this.next = next;
        }
    }

    private class IteratorImp implements Iterator<E> {
        private Node node = null;
        private LocalDateTime iterModCount = getModCount();

        IteratorImp(Node node) {
            this.node = node;
        }
        @Override
        public boolean hasNext() throws ConcurrentModificationException {
            if (!isSameModification()) {
                throw new ConcurrentModificationException();
            }

            return this.node != null;
        }

        @Override
        public E next() throws ConcurrentModificationException {
            if (!isSameModification()) {
                throw new ConcurrentModificationException();
            }

            E data = this.node.getData();
            this.node = this.node.getNext();
            return data;
        }

        private boolean isSameModification() {
            return this.iterModCount.equals(getModCount());
        }

    }

    @Override
    public IteratorImp iterator() {
        return new IteratorImp(this.getHead());
    }
    public void pushFront(E data) {
        Node newHead = new Node(data, this.head);
        this.setHead(newHead);
        setSllModCount(LocalDateTime.now());
    }

    public E popFront() throws NoSuchElementException{
        E element = null;

        try {
            element = this.getHead().getData();
        } catch (NullPointerException e) {
            throw new NoSuchElementException(e);
        }

        this.setHead(this.getHead().getNext());
        setSllModCount(LocalDateTime.now());
        return element;
    }

    public long getSize() {
        long size = 0;
        for (E ignored : this) {
            /*
            E type is named ignored to suppress IntelliJ warnings
             */
            ++size;
        }

        return size;
    }

    public boolean isEmpty() {
        return null == this.getHead();
    }

    public IteratorImp find(Object obj) {
        IteratorImp iterator = this.iterator();
        for (E element : this) {
            if (element.equals(obj)) {
                return iterator;
            }
            iterator.next();
        }

        return null;
    }

    public static <E> SLL<E> newReverse(SLL<E> sll) {
        SLL<E> newSLL = new SLL<>();
        for (E e : sll) {
            newSLL.pushFront(e);
        }

        return newSLL;
    }

    public void print() {
        System.out.print("[");
        for (E e : this) {
            System.out.print(e.toString() + ", ");
        }

        System.out.println("]");
    }

    public static <E> SLL<E> merge(SLL<E> sll1, SLL<E> sll2) {
        SLL<E>.Node nodeIterator = sll1.head;

        while (null != nodeIterator.getNext()) {
            nodeIterator = nodeIterator.getNext();
        }

        nodeIterator.setNext(sll2.getHead());
        sll2.setHead(null);

        sll1.setSllModCount(LocalDateTime.now());
        sll2.setSllModCount(LocalDateTime.now());
        return sll1;
    }
    private LocalDateTime getModCount() {
        return this.sllModCount;
    }

    private void setSllModCount(LocalDateTime newMod) {
        this.sllModCount = newMod;
    }

    public Node getHead() {
        return head;
    }

    public void setHead(Node head) {
        this.head = head;
    }
}