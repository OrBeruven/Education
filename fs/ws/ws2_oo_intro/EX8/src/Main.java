import java.util.Arrays;

public class Main {
    public static void main(String[] args) throws ClassNotFoundException, InstantiationException, IllegalAccessException {
        Class<?> myClass = Class.forName(args[0]);
        Square rectangle = (Square) myClass.newInstance();

        System.out.println("Interfaces: " + Arrays.toString(myClass.getInterfaces()));
        System.out.println("Name: " + myClass.getName());
        System.out.println("is Interface: " + myClass.isInterface());
        System.out.println("Superclass: " + myClass.getSuperclass());
        System.out.println("Simple name: " + rectangle);
        System.out.println("Is string assignable from Object? " + String.class.isAssignableFrom(Object.class));
    }
}