import java.util.HashMap;
import java.util.Map;

public class TwoThreeClassesException {
    public static void main(String[] args) {
        Animal animal = new Animal();
        Cat cat = new Cat();
        James james = new James();

        animal.foo();
        cat.foo();
        james.foo();
    }
}

class Animal {
    private final int num_of_legs = 5;
    HashMap<String, Integer> a = new HashMap<String, Integer>();

    void foo() {
        a.put("a", 2);
        System.out.println(a.toString());
        System.out.println("num of legs for animal : " + this.num_of_legs);
    }
}

class Cat {
    private final int num_of_legs = 4;

    void foo() {
        System.out.println("num of legs for cat : " + this.num_of_legs);
    }
}

class James {
    private final int num_of_legs = 2;

    void foo() {
        System.out.println("num of legs for james : " + this.num_of_legs);
    }
}