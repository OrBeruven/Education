public class Singleton<T> {
    private Singleton<T> instance = null;
    public Singleton<T> getInstance() {
        if (instance == null) {
            System.out.println("Create Instance");
            instance = new Singleton<T>();
        }

        System.out.println("Return an Instance");
        return instance;
    }
}
