/*
HEADER
 */
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Test;
import GenericSLL.*;
import org.junit.jupiter.api.TestMethodOrder;
import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Iterator;

@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
class SLLTest {
    @Test
    void pushFront() {
        SLL<Integer> sll = new SLL<>();
        Integer data = 1;
        Integer data2 = 2;
        Integer data3 = 3;
        Integer data4 = 4;

        assertTrue(sll.isEmpty());

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);

        assertEquals(4, sll.getSize());
        assertNotNull(sll.iterator());
        assertFalse(sll.isEmpty());
    }

    @Test
    void popFront() {
        SLL<Integer> sll = new SLL<>();
        Integer data = 1;
        Integer data2 = 2;
        Integer data3 = 3;
        Integer data4 = 4;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);

        sll.popFront();

        assertEquals(3, sll.getSize());
    }

    @Test
    void getSize() {
        SLL<Integer> sll = new SLL<>();
        Integer data = 1;
        Integer data2 = 2;

        sll.pushFront(data);
        assertEquals(1, sll.getSize());
        sll.pushFront(data2);
        assertEquals(2, sll.getSize());

        sll.popFront();
        assertEquals(1, sll.getSize());
        sll.popFront();
        assertEquals(0, sll.getSize());
    }

    @Test
    void isEmpty() {
        SLL<Integer> sll = new SLL<>();
        assertTrue(sll.isEmpty());
    }

    @Test
    void find() {
        SLL<Integer> sll = new SLL<>();
        Integer data = 1;
        Integer data2 = 2;
        Integer data3 = 3;
        Integer data4 = 4;
        int data5 = 5;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);

        Object obj = data;
        Iterator<Integer> iterator = sll.find(obj);
        assertEquals(data, iterator.next());

        obj = data5;
        iterator = sll.find(obj);
        assertNull(iterator);
    }

    @Test
    void begin() {
        SLL<Integer> sll = new SLL<>();
        Integer data = 1;
        Integer data2 = 2;
        Integer data3 = 3;
        Integer data4 = 4;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);


    }

    @Test
    void newReverse() {
        SLL<Integer> sll = new SLL<>();
        Integer data = 1;
        Integer data2 = 2;
        Integer data3 = 3;
        Integer data4 = 4;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);

        sll.print();

        SLL<Integer> newSll = SLL.newReverse(sll);
        newSll.print();
    }

    @Test
    void merge() {
        SLL<Integer> sll = new SLL<>();
        Integer data = 1;
        Integer data2 = 2;
        Integer data3 = 3;
        Integer data4 = 4;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);
        sll.pushFront(data4);
        SLL<Integer> newSll = SLL.newReverse(sll);

        SLL.merge(sll, newSll).print();
    }

    @Test
    void exception() {
        SLL<Integer> sll = new SLL<>();
        Integer data = 1;
        Integer data2 = 2;
        Integer data3 = 3;
        Integer data4 = 4;

        sll.pushFront(data);
        sll.pushFront(data2);
        sll.pushFront(data3);

        Iterator<Integer> iterator = sll.iterator();
        iterator.next();

        Exception exception = assertThrows(ConcurrentModificationException.class, () -> {
            sll.pushFront(data4);
            iterator.next();
        });

        String expectedMessage = "ConcurrentModificationException - Iterator not up to date";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }
}