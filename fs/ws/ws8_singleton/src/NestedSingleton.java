public class NestedSingleton {
    private NestedSingleton() {
        System.out.println("NestedSingleton constructor invoked");
    }
    private static class NestedSingletonClass {
        private static final NestedSingleton INSTANCE = new NestedSingleton();
    }

    public static NestedSingleton getInstance() {
        return NestedSingletonClass.INSTANCE;
    }
}
