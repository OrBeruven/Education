import java.util.HashMap;
import java.util.Map;

public class LRUCache<K, V> {
    private Map<K, Node<K, V>> cacheMap = new HashMap<>();
    private Node<K, V> dummyTail = new Node<>(null, null, null, null);
    private Node<K, V> mostRecentlyUsed = dummyTail;
    final int maxCapacity;

    public LRUCache(int maxCapacity) {
        this.maxCapacity = maxCapacity;
    }

    public void put(K key, V value) {
        Node<K, V> tmpNode = null;
        if (this.cacheMap.containsKey(key)) {
            // if exist just change the value.

            tmpNode = this.cacheMap.get(key);
            tmpNode.val = value;
            return;
        }

        if (this.maxCapacity == this.cacheMap.size()) {
            Node<K, V> leastUsed = this.dummyTail.prev;
            //detach
            leastUsed.next.prev = leastUsed.prev;
            leastUsed.prev.next = leastUsed.next;
            cacheMap.remove(leastUsed.key);
        }

        tmpNode = new Node<>(value, key, mostRecentlyUsed, null);
        mostRecentlyUsed.prev = tmpNode;
        mostRecentlyUsed = tmpNode;

        // put in the map.
        cacheMap.put(key, tmpNode);
    }


    public V get(K key) {
        Node<K, V> node = this.cacheMap.get(key);

        if (null != node && this.mostRecentlyUsed != node) {
            node.next.prev = node.prev;
            node.prev.next = node.next;

            this.mostRecentlyUsed.prev = node.prev;
            node.next = this.mostRecentlyUsed;
            node.prev = null;
            this.mostRecentlyUsed = node;
        }

        return node != null ? node.val : null;
    }

    public int getSize() {
        return this.cacheMap.size();
    }
    public Map<K, Node<K, V>> getCacheMap() {
        return cacheMap;
    }

    public void setCacheMap(Map<K, Node<K, V>> cacheMap) {
        this.cacheMap = cacheMap;
    }

    public Node<K, V> getDummyTail() {
        return dummyTail;
    }

    public void setDummyTail(Node<K, V> dummyTail) {
        this.dummyTail = dummyTail;
    }

    public Node<K, V> getMostRecentlyUsed() {
        return mostRecentlyUsed;
    }

    public void setMostRecentlyUsed(Node<K, V> mostRecentlyUsed) {
        this.mostRecentlyUsed = mostRecentlyUsed;
    }

    public int getMaxCapacity() {
        return maxCapacity;
    }

    static class Node<K, V>{
        V val = null;
        K key = null;
        Node<K, V> next = null;
        Node<K, V> prev = null;

        Node(V val, K key, Node<K, V> next, Node<K, V> prev){
            this.key = key;
            this.val = val;
            this.next = next;
            this.prev = prev;
        }
    }

}