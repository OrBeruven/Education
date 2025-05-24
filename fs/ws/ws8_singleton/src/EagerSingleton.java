public class EagerSingleton {
    private static final EagerSingleton INSTANCE = new EagerSingleton();
    private EagerSingleton() {
        System.out.println("EagerSingleton constructor has been invoked");
    }
    public static EagerSingleton getInstance() {
        return INSTANCE;
    }
}