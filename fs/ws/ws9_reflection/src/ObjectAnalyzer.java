import java.lang.reflect.*;
import java.util.ArrayList;
import java.util.Comparator;

public class ObjectAnalyzer {
    public static void printAncestors(Class<?> foo) {
        Class<?> ancestor = foo.getSuperclass();

        System.out.println("List ancestors of " + foo.getCanonicalName());
        while (ancestor != null) {
            System.out.println(ancestor.getCanonicalName());
            ancestor = ancestor.getSuperclass();
        }
    }

    public static void listModifiers(Class<?> foo) {
        System.out.println("List modifiers of " + foo.getCanonicalName());
        Class<?>[] classArr = foo.getDeclaredClasses();
        int mod;
        String className;
        for (Class<?> inner : classArr) {
            mod = inner.getModifiers();
            className = inner.getSimpleName();
            System.out.println(Modifier.toString(mod) + " " + className);

        }
    }

    public static void listInterfaces(Class<?> foo) {
        System.out.println("List interfaces of " + foo.getCanonicalName());
        Class<?>[] interfaces = foo.getInterfaces();
        for (Class<?> iterInterface : interfaces) {
            System.out.println(iterInterface.getName());
        }
    }

    public static void listMembers(Class<?> foo) {
        System.out.println("List members of " + foo.getCanonicalName());
        Field[] fields = foo.getDeclaredFields();
        for (Field f : fields) {
            System.out.println(f.getName());
        }
    }

    public static Object createNewInstance(Class<?> foo) throws NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        Constructor<?> constructor = foo.getConstructor();
        return constructor.newInstance();
    }

    public static void callPrivateMethod(Class<?> foo) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException, InstantiationException {
        int x = 5;
        Object obj = createNewInstance(foo);
        String methodName = "foo1";
        Method method = obj.getClass().getMethod(methodName, int.class);
        method.invoke(obj, x);
    }

    public static void main(String[] args) throws InvocationTargetException, NoSuchMethodException, InstantiationException, IllegalAccessException {
        FooSon foo = new FooSon();
        //printAncestors(foo.getClass());
        //listModifiers(foo.getClass());
        //listInterfaces(foo.getClass());
        //listMembers(Foo.class);

        //Object obj = createNewInstance(foo.getClass());
        //System.out.println(obj.getClass().getName());
        callPrivateMethod(foo.getClass());
    }
}

class FooFather {
    int x = 2;
}

class Foo extends FooFather {
    int y = 1;
}

class FooSon extends Foo implements Comparable<FooSon> , Comparator<FooSon> {
    private int a;
    public static final String name = "Max";
    private ArrayList<Integer> arrList;

    public  FooSon() {

    }

    public void test() {
        System.out.println("FooGrandSon");
    }
    public void foo1(int a) {
        System.out.println("i am foo1 " + a);
    }

    @Override
    public int compareTo(FooSon fooGrandSon) {
        return 0;
    }

    @Override
    public int compare(FooSon fooGrandSon, FooSon t1) {
        return 0;
    }

    private static class InnerStatic {

    }
    private class Engine {

    }
}

