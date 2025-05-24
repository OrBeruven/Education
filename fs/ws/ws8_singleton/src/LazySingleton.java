public class LazySingleton {
    private static LazySingleton INSTANCE = null;
    private LazySingleton() {}
    public static synchronized LazySingleton getInstance() {
        if (INSTANCE == null) {
            INSTANCE = new LazySingleton();
        }
        return INSTANCE;
    }
}
