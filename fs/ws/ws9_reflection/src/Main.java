import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class Main {
    public static void main(String[] args) throws Exception {
        // Get the Class object of a class
        Class<Person> personClass = Person.class;

        // Get the declared fields of the class
        Field[] fields = personClass.getDeclaredFields();
        System.out.println("Declared Fields:");
        for (Field field : fields) {
            System.out.println(field.getName());
        }

        // Get the declared methods of the class
        Method[] methods = personClass.getDeclaredMethods();
        System.out.println("Declared Methods:");
        for (Method method : methods) {
            System.out.println(method.getName());
        }
    }
}

class Person {
    private String name;
    private int age;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}