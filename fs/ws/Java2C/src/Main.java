class Base {
    public Base() {
        polymorphicMethod();
    }

    public void polymorphicMethod() {
        System.out.println("Base class implementation");
    }
}

class Derived extends Base {
    @Override
    public void polymorphicMethod() {
        System.out.println("Derived class implementation");
    }
}

public class Main {
    public static void main(String[] args) {
        Base baseObj = new Derived();  // Output: "Base class implementation"
    }
}