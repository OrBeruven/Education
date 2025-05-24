import java.util.LinkedHashMap;
import java.util.Map;

public class LRUCache2<K, V> {
    private LinkedHashMap<K, V> map = null;
    private final int CAPACITY;
    public LRUCache2(int capacity) {
        CAPACITY = capacity;
        map = new LinkedHashMap<>(capacity, 0.75f, true){
            @Override
            protected boolean removeEldestEntry(Map.Entry eldest) {
                return size() > CAPACITY;
            }
        };
    }
    public V get(K key) {
        return map.getOrDefault(key, null);
    }
    public void put(K key, V value) {
        map.put(key, value);
    }

    public boolean containsKey(K key) {
        return map.containsKey(key);
    }
}