public class DoubleCheckedLockingSingleton {
    private static DoubleCheckedLockingSingleton instance = null;

    private DoubleCheckedLockingSingleton() {
        System.out.println("DoubleCheckedLockingSingleton constructor invoked");
    }
    public static DoubleCheckedLockingSingleton getInstance() {
        if (instance == null) {
            synchronized (DoubleCheckedLockingSingleton.class) {
                if (instance == null) {
                    instance = new DoubleCheckedLockingSingleton();
                }
            }
        }

        return instance;
    }
}
