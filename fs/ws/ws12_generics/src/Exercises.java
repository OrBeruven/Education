import java.util.ArrayList;
import java.util.List;

public class Exercises {

    public static void main(String[] args) {
        Exercises exercises = new Exercises();
        Ex1();
        exercises.Ex23();
    }

    public static void Ex1() {
        Exercises exercises = new Exercises();

        Integer[] integerArray = new Integer[3];
        integerArray[0] = 1;
        integerArray[1] = 2;
        integerArray[2] = 3;

        exercises.printArray(integerArray);

        String[] integerString = new String[3];
        integerString[0] = "one";
        integerString[1] = "two";
        integerString[2] = "three";

        exercises.printArray(integerString);

        List<Integer> integerList1 = new ArrayList<>();
        integerList1.add(1);
        List<Integer> integerList2 = new ArrayList<>();
        integerList2.add(2);
        List<Integer> integerList3 = new ArrayList<>();
        integerList3.add(3);

        List<Integer>[] lists = new ArrayList[3];
        lists[0] = integerList1;
        lists[1] = integerList2;
        lists[2] = integerList3;

        exercises.printArray(lists);
    }

    public void Ex23() {
        FooReference<Integer> integerFooReference = new Exercises.FooReference<>();
        integerFooReference.setType(7);
        System.out.println(integerFooReference.getType());
        System.out.println(integerFooReference.getClass());


        FooReference<String> stringFooReference = new Exercises.FooReference<>();
        stringFooReference.setType("Seven");
        System.out.println(stringFooReference.getType());
        System.out.println(stringFooReference.getClass());
    }

    public <T> void printArray(T[] arr) {
        for (T t : arr) {
            System.out.println(t);
        }
    }

    class FooReference<T> {
        T type;

        public T getType() {
            return type;
        }

        public void setType(T type) {
            this.type = type;
        }
    }

    public <T> T Foo(List<T> arg) {
        return new T();
    }
}
