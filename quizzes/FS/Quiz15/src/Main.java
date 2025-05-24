public class Main {
    public static void main(String[] args) {
        LRUCache2<String, Integer> cache = new LRUCache2<>(3);
        cache.put("a", 3);
        cache.put("b", 4);
        cache.put("x", 10);
        cache.put("i", 25);

//        System.out.println("break1 - " + cache.getMostRecentlyUsed().val);
        System.out.println("False == " + cache.containsKey("a"));
        System.out.println(cache.get("b"));
        System.out.println(cache.get("b"));
//        System.out.println("break1 - " + cache.getMostRecentlyUsed().val);
        cache.put("f", 15);
        cache.put("c", 15);
//        System.out.println(cache.getMostRecentlyUsed().val);

        cache.put("f", 15);
    }
}
