import java.util.*;

class HelloWorld {
    public static void main(String[] args) {
        foo(5);
    }


    public static <E> void foo(E element, int arraySize){
        List<?>[] list = new ArrayList<?>[arraySize];
        list.add(element);
        System.out.println(list);
    }
}
