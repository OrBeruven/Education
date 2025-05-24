/*
 *       Programmer : Or
 *       Reviewer : Harel
 *       Date : 06.07.2023
 *       Description : generic Hashtable implementation
 */

import java.util.*;

public class HashTable<K extends Comparable<K>, V> implements Map<K, V> {
    private static final int TREE_THRESHOLD = 8;
    private Collection<HashEntry<K, V>>[] table = null;
    private float loadFactor = 0;
    private int modCount = 0;
    private int size = 0;

    public HashTable(int capacity, float loadFactor) {
        table = initTable(capacity);
        this.loadFactor = loadFactor;
    }

    public HashTable(int capacity) {
        this(capacity, 0.75f);
    }

    HashTable() {
        this(11, 0.75f);
    }

    private static class HashEntry<K extends Comparable<K>, V> implements Map.Entry<K, V>, Comparable<HashEntry<K, V>> {
        private K key = null;
        private V value = null;

        HashEntry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public K getKey() {
            return this.key;
        }

        @Override
        public V getValue() {
            return this.value;
        }

        @Override
        public V setValue(V value) {
            V oldValue = this.getValue();
            this.value = value;
            return oldValue;
        }

        @Override
        public String toString() {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.append("(");
            stringBuilder.append(this.getKey());
            stringBuilder.append(", ");
            stringBuilder.append(this.getValue());
            stringBuilder.append(")");

            return stringBuilder.toString();
        }

        @Override
        public int compareTo(HashEntry<K, V> o) {
            return this.getKey().compareTo(o.getKey());
        }
    }

    @SuppressWarnings("unchecked")
    private Collection<HashEntry<K, V>>[] initTable(int capacity) {
        Collection<?>[] newTable = new Collection<?>[capacity];
        int i = 0;

        for (Collection<?> collection : newTable) {
            newTable[i] = new LinkedList<HashEntry<K, V>>();
            ++i;
        }

        return (Collection<HashEntry<K, V>>[]) newTable;
    }

    @Override
    public int size() {
        return this.size;
    }

    @Override
    public boolean isEmpty() {
        return this.size == 0;
    }

    @Override
    public boolean containsKey(Object key) throws NullPointerException {
        return null != get(key);
    }

    @Override
    public boolean containsValue(Object value) {
        boolean contains = false;

        for (V v : this.values()) {
            if (v.equals(value)) {
                contains = true;
                break;
            }
        }

        return contains;
    }

    @Override
    public V get(Object key) {
        if (null == key) {
            throw new NullPointerException();
        }
        int index = getIndex(key, this.getTable().length);
        Collection<HashEntry<K, V>> bucket = this.getTable()[index];
        V value = null;

        for (HashEntry<K, V> entry : bucket) {
            if (entry.getKey().equals(key)) {
                value = entry.getValue();
            }
        }

        return value;
    }

    @Override
    public V put(K key, V value) {
        if (null == key) {
            throw new NullPointerException();
        }
        ++this.modCount;
        rehash();

        HashEntry<K, V> newEntry = new HashEntry<>(key, value);
        int index = getIndex(key, this.getTable().length);
        Collection<HashEntry<K, V>> bucket = this.getTable()[index];
        V toRet = null;

        if (this.getTable()[index].size() >= TREE_THRESHOLD && !(this.getTable()[index] instanceof TreeSet)) {
            this.getTable()[index] = convertCollectionToTree(index);
            System.out.println("Converted");
        }

        if (!bucket.isEmpty()) {
            for (HashEntry<K, V> entry : bucket) {
                if (entry.getKey().equals(key)) {
                    toRet = entry.getValue();
                    entry.setValue(value);
                    break;
                }
            }
        }

        if (null == toRet) {
            ++this.size;
            bucket.add(newEntry);
        }

        return toRet;
    }

    @Override
    public V remove(Object key) {
        if (null == key) {
            throw new NullPointerException();
        }
        int index = getIndex(key, this.getTable().length);
        V value = null;
        Collection<HashEntry<K, V>> bucket = this.getTable()[index];

        if (!bucket.isEmpty()) {
            for (HashEntry<K, V> entry : bucket) {
                if (entry.getKey().equals(key)) {
                    ++modCount;
                    --this.size;
                    value = entry.getValue();
                    bucket.remove(entry);
                    break;
                }
            }
        }

        return value;
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> m) {
        for (Map.Entry<? extends K, ? extends V> e : m.entrySet()) {
            this.put(e.getKey(), e.getValue());
        }
    }

    @Override
    public void clear() {
        ++modCount;
        for (Collection<HashEntry<K, V>> bucket : this.getTable()) {
            bucket.clear();
        }
        this.size = 0;
    }

    @Override
    public Set<K> keySet() {
        return new KeySet();
    }

    @Override
    public Collection<V> values() {
        //return new ValueCollection();
        return new ValueCollection();
    }

    @Override
    public Set<Map.Entry<K, V>> entrySet() {
        //return new EntrySet();
        return new EntrySet();
    }


    /*********************************************************
     *                  put Help methods
     *********************************************************/
    private void rehash() {
        if ((int) (this.getLength() * this.loadFactor) > this.size()) {
            return;
        }

        int newTableLength = (this.getLength() << 1) + 1;
        Collection<HashEntry<K, V>>[] newTable = initTable(newTableLength);

        for (Collection<HashEntry<K, V>> bucket : this.getTable()) {
            for (HashEntry<K, V> entry : bucket) {
                newTable[getIndex(entry.getKey(), newTableLength)].add(entry);
            }
        }

        this.table = newTable;
    }

    private Collection<HashEntry<K, V>> convertCollectionToTree(int index) {
        return new TreeSet<>(this.getTable()[index]);
    }


    /*********************************************************
     *                  private Getters
     *********************************************************/
    private Collection<HashEntry<K, V>>[] getTable() {
        return this.table;
    }

    private int getLength() {
        return this.getTable().length;
    }

    private int getModCount() {
        return this.modCount;
    }

    private static int getIndex(Object key, int length) {
        return Math.abs(key.hashCode() % length);
    }


    /*********************************************************
     *              Iteration help methods
     *********************************************************/
    private HashEntry<K, V> getNextEntry(HashEntry<K, V> currEntry) {
        HashEntry<K, V> iteratorEntry = null;
        int currIndex = getIndex(currEntry.getKey(), this.getTable().length);
        Iterator<HashEntry<K, V>> iterator = this.getTable()[currIndex].iterator();

        while (iterator.hasNext()) {
            iteratorEntry = iterator.next();
            if (iteratorEntry.getKey().equals(currEntry.getKey())) {
                if (iterator.hasNext()) {
                    iteratorEntry = iterator.next();
                } else {
                    iteratorEntry = null;
                }
                break;
            }
        }

        if (null == iteratorEntry) {
            iteratorEntry = getFirstEntry(++currIndex);
        }

        return iteratorEntry;
    }

    private HashEntry<K, V> getFirstEntry(int index) {
        HashEntry<K, V> entryToRet = null;

        for (; index < this.getTable().length; ++index) {
            if (null != this.getTable()[index] && !this.getTable()[index].isEmpty()) {
                entryToRet = this.getTable()[index].iterator().next();
                break;
            }
        }

        return entryToRet;
    }


    /*********************************************************
     *              Sets and Collection classes
     *********************************************************/
    private final class KeySet extends AbstractSet<K> {
        @Override
        public Iterator<K> iterator() {
            return new HashKeyIterator();
        }

        @Override
        public int size() {
            return size;
        }

        private final class HashKeyIterator implements Iterator<K> {
            HashEntry<K, V> currEntry = null;
            int modCount = 0;

            private HashKeyIterator() {
                this.modCount = getModCount();
                this.currEntry = getFirstEntry(0);
            }

            @Override
            public boolean hasNext() {
                if (this.modCount != getModCount()) {
                    throw new ConcurrentModificationException("ConcurrentModificationException - Iterator not up to date");
                }
                return null != this.currEntry;
            }

            @Override
            public K next() {
                if (this.modCount != getModCount()) {
                    throw new ConcurrentModificationException("ConcurrentModificationException - Iterator not up to date");
                }

                K keyToRet = this.currEntry.getKey();
                this.currEntry = getNextEntry(this.currEntry);
                return keyToRet;
            }
        }
    }

    private final class ValueCollection extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            return new HashValueIterator();
        }

        @Override
        public int size() {
            return size;
        }

        private final class HashValueIterator implements Iterator<V> {
            HashEntry<K, V> currEntry = null;
            int modCount = 0;

            HashValueIterator() {
                this.modCount = getModCount();
                this.currEntry = getFirstEntry(0);
            }

            @Override
            public boolean hasNext() {
                if (this.modCount != getModCount()) {
                    throw new ConcurrentModificationException("ConcurrentModificationException - Iterator not up to date");
                }
                return null != this.currEntry;
            }

            @Override
            public V next() {
                if (this.modCount != getModCount()) {
                    throw new ConcurrentModificationException("ConcurrentModificationException - Iterator not up to date");
                }
                V valueToRet = this.currEntry.getValue();
                this.currEntry = getNextEntry(this.currEntry);
                return valueToRet;
            }
        }
    }

    private final class EntrySet extends AbstractSet<Map.Entry<K, V>> {

        @Override
        public Iterator<Map.Entry<K, V>> iterator() {
            return new HashEntryIterator();
        }

        @Override
        public int size() {
            return size;
        }

        private final class HashEntryIterator implements Iterator<Map.Entry<K, V>> {
            HashEntry<K, V> currEntry = null;
            int modCount = 0;

            HashEntryIterator() {
                this.modCount = getModCount();
                this.currEntry = getFirstEntry(0);
            }

            @Override
            public boolean hasNext() {
                if (this.modCount != getModCount()) {
                    throw new ConcurrentModificationException("ConcurrentModificationException - Iterator not up to date");
                }
                return null != this.currEntry;
            }

            @Override
            public Map.Entry<K, V> next() {
                if (this.modCount != getModCount()) {
                    throw new ConcurrentModificationException("ConcurrentModificationException - Iterator not up to date");
                }
                HashEntry<K, V> entryToRet = this.currEntry;
                this.currEntry = getNextEntry(this.currEntry);
                return entryToRet;
            }
        }
    }

    /*********************************************************
     *                      For Testing
     *********************************************************/
    public void printLength() {
        System.out.println("Length : " + getLength());
        System.out.println("Size : " + size());
        System.out.println("Current load factor : " + ((double) size() / (double) getLength()));
    }
}