/*
 *       Programmer : Or
 *       Reviewer : Harel
 *       Date : 06.07.2023
 *       Description : generic Hashtable testing
 */

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

import static org.junit.jupiter.api.Assertions.*;

public class HashtableTest {
    private HashTable<String, Integer> hashtable = null;

    @BeforeEach
    void before() {
        hashtable = new HashTable<>(3);
        hashtable.put("One", 1);
        hashtable.put("Two", 2);
        hashtable.put("Three", 3);
        hashtable.put("Four", 4);
    }

    @Test
    void put() {
        Integer value = 0;
        value = hashtable.put("One", 11);
        assertEquals(1, value);

        value = hashtable.put("Two", 22);
        assertEquals(2, value);

        value = hashtable.put("Three", 33);
        assertEquals(3, value);

        value = hashtable.put("Four", 44);
        assertEquals(4, value);

        value = hashtable.put("Four", 55);
        assertEquals(44, value);

        value = hashtable.put("Five", 55);
        assertNull(value);
    }

    @Test
    void get() {
        assertEquals(1, hashtable.get("One"));
        assertEquals(3, hashtable.get("Three"));
        assertEquals(4, hashtable.get("Four"));
        assertEquals(2, hashtable.get("Two"));
        assertNull(hashtable.get("Five"));

        hashtable.put("Four", 5);
        assertEquals(5, hashtable.get("Four"));
    }

    @Test
    void size() {
        Hashtable<String, Integer> hashtable = new Hashtable<>(3);
        assertEquals(0, hashtable.size());
        hashtable.put("One", 1);
        hashtable.put("Two", 2);
        assertEquals(2, hashtable.size());
        hashtable.put("Three", 3);
        assertEquals(3, hashtable.size());
        hashtable.put("Four", 4);
        assertEquals(4, hashtable.size());
    }

    @Test
    void isEmpty() {
        Hashtable<String, Integer> hashtable = new Hashtable<>(3);
        assertTrue(hashtable.isEmpty());
        hashtable.put("One", 1);
        assertFalse(hashtable.isEmpty());
        hashtable.put("Two", 2);
        hashtable.put("Three", 3);
        assertFalse(hashtable.isEmpty());
        hashtable.put("Four", 4);
        hashtable.remove("One");
        hashtable.remove("Two");
        hashtable.remove("Three");
        hashtable.remove("Four");
        assertTrue(hashtable.isEmpty());
    }

    @Test
    void containsKey() {
        hashtable.put("Four", 5);

        assertTrue(hashtable.containsKey("One"));
        assertTrue(hashtable.containsKey("Three"));
        assertTrue(hashtable.containsKey("Four"));
        assertFalse(hashtable.containsKey("Five"));
    }

    @Test
    void containsValue() {
        hashtable.put("Four", 5);

        assertTrue(hashtable.containsValue(1));
        assertTrue(hashtable.containsValue(3));
        assertTrue(hashtable.containsValue(5));
        assertFalse(hashtable.containsValue(4));
    }

    @Test
    void remove() {
        assertEquals(4, hashtable.size());

        Integer value = hashtable.remove("One");
        assertEquals(3, hashtable.size());
        assertEquals(1, value);

        value = hashtable.remove("One");
        assertEquals(3, hashtable.size());
        assertNull(value);

        value = hashtable.remove("Two");
        assertEquals(2, hashtable.size());
        assertEquals(2, value);

        value = hashtable.remove("Three");
        assertEquals(1, hashtable.size());
        assertEquals(3, value);

        value = hashtable.remove("Four");
        assertEquals(0, hashtable.size());
        assertEquals(4, value);

        assertTrue(hashtable.isEmpty());
    }

    @Test
    void putAll() {
        Map<String, Integer> newMap = new HashMap<>();
        newMap.put("One", 11);
        newMap.put("Two", 22);
        newMap.put("Three", 33);

        hashtable.putAll(newMap);

        assertTrue(hashtable.containsValue(22));
        assertTrue(hashtable.containsValue(11));
        assertTrue(hashtable.containsValue(33));
        assertFalse(hashtable.containsValue(1));
        assertTrue(hashtable.containsValue(4));

        assertEquals(4, hashtable.size());
    }

    @Test
    void clear() {
        assertEquals(4, hashtable.size());
        assertFalse(hashtable.isEmpty());

        hashtable.clear();

        assertEquals(0, hashtable.size());
        assertTrue(hashtable.isEmpty());
        assertFalse(hashtable.containsValue(2));
        assertFalse(hashtable.containsKey("One"));
    }

    @Test
    void keySet() {
        Set<String> set = hashtable.keySet();

        for (String s : set) {
            System.out.println(s);
        }

        System.out.println(set);
    }

    @Test
    void values() {
        Collection<Integer> collection = hashtable.values();
        System.out.println(collection);
    }

    @Test
    void entrySet() {
        Set<Map.Entry<String, Integer>> set = hashtable.entrySet();
        System.out.println(set);
    }

    @Test
    void rehash() {
        hashtable = new HashTable<>(3);
        hashtable.put("One", 1);
        hashtable.put("Two", 2);
        System.out.println(hashtable.size());
        hashtable.put("Three", 3);
        hashtable.put("Four", 4);
        System.out.println(hashtable.size());
    }

    @Test
    void tree() {
        HashTable<TreeTest, Integer> hashtable1 = new HashTable<>(100);

        TreeTest t1 = new TreeTest(1);
        TreeTest t1_too = new TreeTest(1);
        TreeTest t2 = new TreeTest(2);
        TreeTest t3 = new TreeTest(3);
        TreeTest t4 = new TreeTest(4);
        TreeTest t5 = new TreeTest(5);
        TreeTest t6 = new TreeTest(6);
        TreeTest t7 = new TreeTest(7);
        TreeTest t8 = new TreeTest(8);
        TreeTest t9 = new TreeTest(9);
        TreeTest t10 = new TreeTest(10);

        assertFalse(t1.equals(t2));
        assertTrue(t1_too.equals(t1));

        hashtable1.put(t1, 1);
        hashtable1.put(t2, 2);
        hashtable1.put(t3, 3);
        hashtable1.put(t4, 4);
        hashtable1.put(t5, 5);
        hashtable1.put(t6, 6);
        hashtable1.put(t7, 7);
        hashtable1.put(t8, 8);
        hashtable1.put(t9, 9);
        hashtable1.put(t10, 10);

        /*containsValue*/
        assertTrue(hashtable1.containsValue(1));
        assertTrue(hashtable1.containsValue(3));
        assertTrue(hashtable1.containsValue(5));
        assertFalse(hashtable1.containsValue(11));

        /*containsKey*/
        assertTrue(hashtable1.containsKey(t1));
        assertTrue(hashtable1.containsKey(t1_too));
        assertTrue(hashtable1.containsKey(new TreeTest(7)));
        assertFalse(hashtable1.containsKey(new TreeTest(11)));

        /*size*/
        assertEquals(10, hashtable1.size());

        /*keySet*/
        Set<TreeTest> set = hashtable1.keySet();
        System.out.println(set);

        /*isEmpty & clear*/
        assertFalse(hashtable1.isEmpty());
        hashtable1.clear();
        assertTrue(hashtable1.isEmpty());
    }

    @Test
    void exception() {
        Exception exception = assertThrows(ConcurrentModificationException.class, () -> {
            Collection<Integer> collection = hashtable.values();
            for (Integer i : collection) {
                hashtable.put("Exception", 666);
            }
        });

        String expectedMessage = "ConcurrentModificationException - Iterator not up to date";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));

        exception = assertThrows(ConcurrentModificationException.class, () -> {
            Set<String> set = hashtable.keySet();
            for (String s : set) {
                hashtable.put("Exception", 666);
            }
        });

        expectedMessage = "ConcurrentModificationException - Iterator not up to date";
        actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));

        exception = assertThrows(ConcurrentModificationException.class, () -> {
            Set<Map.Entry<String, Integer>> set = hashtable.entrySet();
            for (Map.Entry<String, Integer> s : set) {
                hashtable.put("Exception", 666);
            }
        });

        expectedMessage = "ConcurrentModificationException - Iterator not up to date";
        actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void loadDictionary() throws IOException {
        HashTable<Integer, String> hashTable1 = new HashTable<>(3, 0.75f);
        int lineNumber = 1;

        BufferedReader reader = new BufferedReader(new FileReader("/usr/share/dict/american-english"));
        String line = reader.readLine();

        while (null != line) {
            hashTable1.put(lineNumber, line);
            ++lineNumber;
            line = reader.readLine();
        }

        reader.close();
        for (Map.Entry<Integer, String> entry : hashTable1.entrySet()) {
            System.out.println(entry);
        }

        hashTable1.printLength();
    }
}

class TreeTest implements Comparable<TreeTest> {
    int i = 0;

    TreeTest(int i) {
        this.i = i;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj instanceof TreeTest) {
            TreeTest treeTest = (TreeTest) obj;
            if (this.i == treeTest.i) {
                return true;
            }
        }

        return false;
    }

    @Override
    public int hashCode() {
        return 1;
    }

    @Override
    public int compareTo(TreeTest o) {
        return this.i - o.i;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(this.i);
        return stringBuilder.toString();
    }
}
