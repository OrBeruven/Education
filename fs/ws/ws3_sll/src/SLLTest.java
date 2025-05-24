import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SLLTest {

    @Test
    void pushFront() {
        SLL sll = new SLL();
        int data = 1;
        int data2 = 2;
        int data3 = 3;
        int data4 = 4;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);

        assertEquals(4, sll.getSize());
        assertNotNull(sll.begin());
        assertFalse(sll.isEmpty());
    }

    @Test
    void popFront() {
        SLL sll = new SLL();
        int data = 1;
        int data2 = 2;
        int data3 = 3;
        int data4 = 4;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);

        sll.popFront();

        assertEquals(3, sll.getSize());
    }

    @Test
    void getSize() {
        SLL sll = new SLL();
        assertEquals(0, sll.getSize());

    }

    @Test
    void isEmpty() {
        SLL sll = new SLL();
        assertTrue(sll.isEmpty());
    }

    @Test
    void find() {
        SLL sll = new SLL();
        int data = 1;
        int data2 = 2;
        int data3 = 3;
        int data4 = 4;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);


    }

    @Test
    void begin() {
        SLL sll = new SLL();
        int data = 1;
        int data2 = 2;
        int data3 = 3;
        int data4 = 4;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);

        ListIterator begin = sll.begin();
        begin.print();
    }
}