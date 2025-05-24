import java.util.*;

/*
 *           TO DO
 * 1. modCount = exceptions
 * 2. loadFactor = more buckets
 * 3. Change to Tress = after threshold
 * 4. return sets and collection in O(1)
 */
public class Hashtable<K extends Comparable<K>, V> implements Map<K, V> {

    private Collection<?>[] table = null;
    private float loadFactor = 0;
    private int modCount = 0;
    private int size = 0;

    public Hashtable(int capacity, float loadFactor) {
        table = new Collection<?>[capacity];
        int i = 0;

        for (Collection<?> collection : table){
            table[i] = new LinkedList<HashEntry<K, V>>();
            ++i;
        }
        this.loadFactor = loadFactor;
    }

    public Hashtable(int capacity) {
        this(capacity, 0.75f);
    }

    Hashtable() {
        this(11, 0.75f);
    }

    private static class HashEntry<K extends Comparable<K>, V> implements Map.Entry<K, V> {
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
    public boolean containsKey(Object key) {
        return null != get(key);
    }

    @Override
    @SuppressWarnings("unchecked")
    public boolean containsValue(Object value) {
        boolean contains = false;
        HashEntry<K, V> hashEntry = null;

        for (Collection<?> c : this.getTable()) {
            for (Object entry : c) {
                hashEntry = (HashEntry<K, V>)entry;
                if (hashEntry.getValue().equals(value)) {
                    contains = true;
                    break;
                }
            }
        }

        return contains;

        /*for (V v : this.values()) {
            if (v.equals(value)) {
                contains = true;
                break;
            }
        }

        return contains;*/
    }

    @Override
    public V get(Object key) {
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
    @SuppressWarnings("unchecked")
    public V put(K key, V value) {
        HashEntry<K, V> newEntry = new HashEntry<>(key, value);
        int index = getIndex(key, this.getTable().length);
        Collection<HashEntry<K, V>> bucket = this.getTable()[index];
        V toRet = null;



        HashEntry<K, V> newEntry = new HashEntry<>(key, value);
        int index = getIndex(key, this.getTable().length);
        HashEntry<K, V> currEntry = (HashEntry<K, V>) this.getTable()[index];
        V toRet = null;

        if (null != this.getTable()[index]) {
            while (null != currEntry) {
                if (currEntry.getKey().equals(key)) {
                    toRet = currEntry.getValue();
                    currEntry.setValue(value);
                    break;
                }
                currEntry = currEntry.getNext();
            }

            if (null == toRet) {
                ++this.size;
                newEntry.setNext((HashEntry<K, V>) this.getTable()[index]);
                this.getTable()[index] = newEntry;
            }
        } else {
            ++this.size;
            this.getTable()[index] = newEntry;
        }

        return toRet;
    }

    @Override
    @SuppressWarnings("unchecked")
    public V remove(Object key) {
        int index = getIndex(key, this.getTable().length);
        V value = null;

        if (null != this.getTable()[index]) {
            HashEntry<K, V> bucket = (HashEntry<K, V>) this.getTable()[index];
            HashEntry<K, V> prevBucket = null;

            while (null != bucket.getNext() && !bucket.getKey().equals(key)) {
                prevBucket = bucket;
                bucket = bucket.getNext();
            }

            if (bucket.getKey().equals(key)) {
                --this.size;
                value = bucket.getValue();
                if (null == prevBucket) {
                    this.getTable()[index] = bucket.getNext();
                } else {
                    prevBucket.setNext(bucket.getNext());
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
        for (int i = 0; i < this.getTable().length; ++i) {
            this.getTable()[i] = null;
        }

        this.size = 0;
    }

    @Override
    public Set<K> keySet() {
        return new KeySet();
    }

    @Override
    public Collection<V> values() {
        return new ValueCollection();
    }

    @Override
    public Set<Map.Entry<K, V>> entrySet() {
        return new EntrySet();
    }

    @SuppressWarnings("unchecked")
    private Collection<HashEntry<K, V>>[] getTable() {
        return (Collection<HashEntry<K, V>>[]) this.table;
    }

    private static int getIndex(Object key, int length) {
        return key.hashCode() % length;
    }

    @SuppressWarnings("unchecked")
    private HashEntry<?, ?> getNextEntry(HashEntry<?, ?> currEntry) {
        int currIndex = currEntry.getKey().hashCode() % getTable().length;

        if (null != currEntry.getNext()) {
            currEntry = currEntry.getNext();
        } else {
            currEntry = null;
            for (++currIndex; currIndex < getTable().length; ++currIndex) {
                if (null != getTable()[currIndex]) {
                    currEntry = (HashEntry<K, V>) getTable()[currIndex];
                    break;
                }
            }
        }

        return  currEntry;
    }

    private HashEntry<?, ?> getFirstEntry() {
        HashEntry<?, ?> currEntry = getTable()[0];
        if (null == currEntry) {
            currEntry = getNextEntry(null);
        }

        return currEntry;
    }

    /*********************************************************
     *        Sets and Collection Iterators class
     *********************************************************/
    private final class HashKeyIterator implements Iterator<K> {
        HashEntry<K, V> currEntry = null;

        @SuppressWarnings("unchecked")
        HashKeyIterator() {
            this.currEntry = (HashEntry<K, V>)getFirstEntry();
        }

        @Override
        public boolean hasNext() {
            return null != this.currEntry;
        }

        @Override
        @SuppressWarnings("unchecked")
        public K next() {
            K keyToRet = this.currEntry.getKey();
            this.currEntry =(HashEntry<K, V>) getNextEntry(this.currEntry);
            return keyToRet;
        }
    }
    private final class HashValueIterator implements Iterator<V> {
        HashEntry<K, V> currEntry = null;

        @SuppressWarnings("unchecked")
        HashValueIterator() {
            currEntry = (HashEntry<K, V>) getFirstEntry();
        }

        @Override
        public boolean hasNext() {
            return null != this.currEntry;
        }

        @Override
        @SuppressWarnings("unchecked")
        public V next() {
            V valueToRet = this.currEntry.getValue();
            this.currEntry = (HashEntry<K, V>) getNextEntry(this.currEntry);
            return valueToRet;
        }
    }
    private final class HashEntryIterator implements Iterator<Map.Entry<K, V>> {
        HashEntry<K, V> currEntry = null;

        @SuppressWarnings("unchecked")
        HashEntryIterator() {
            currEntry = (HashEntry<K, V>) getFirstEntry();
        }

        @Override
        public boolean hasNext() {
            return null != this.currEntry;
        }

        @Override
        @SuppressWarnings("unchecked")
        public Map.Entry<K, V> next() {
            HashEntry<K, V> entryToRet = this.currEntry;
            this.currEntry = (HashEntry<K, V>) getNextEntry(this.currEntry);
            return entryToRet;
        }
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
    }
}