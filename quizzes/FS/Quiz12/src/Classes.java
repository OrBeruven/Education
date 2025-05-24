import java.util.ArrayList;
import java.util.List;

public class Classes {
    public static void main(String[] args) {
        Node<Circle> nc = new Node<>();
        Node<Shape> ns = nc;

        List<String> stringList = new ArrayList<>();
        Classes c = new Classes();
        c.temp(stringList);
    }

    public void temp(List<Object> l) {}
}

class Shape {}
class Circle extends Shape {}
class Rectangle extends Shape {}
class Node<T> {}