import java.io.IOException;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        DynamicJarLoader dynamicLoader = new DynamicJarLoader("/home/beru/BeruEnv/or.beruven/fs/ws/tree_composite.jar", "tree_composite/Component");
        List<Class<?>> classList = dynamicLoader.load();

        System.out.println("Here " + classList.toString());
        for (Class<?> temp : classList) {
            System.out.println(temp);
        }
    }
}
