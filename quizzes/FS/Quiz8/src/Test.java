/*Question 1*/
/*class Base {
    public Base() {
        System  .out.println("Base");
    }
}

class Derived extends Base {
    public Derived() {
        System.out.println("Derived");
    }
}

class DeriDerived extends Derived {
    public DeriDerived() {
        System.out.println("DeriDerived");
    }
}

class Test {
    public static void main(String []args) {
        Derived b = new DeriDerived();
    }
}*/

/*Question 2*/
/*class Base {
    public Base() {
        System.out.print("Base ");
    }
    public Base(String s) {
        System.out.print("Base: " + s);
    }
}

class Derived extends Base {
    public Derived(String s) {
        //super(); // Stmt-1
        //super(s); // Stmt-2
        System.out.print("Derived ");
    }
}

class Test {
    public static void main(String []args) {
        Base a = new Derived("Hello ");
    }
}*/

/*Question 3*/
class Base {
    public void test() {}
}

class Base1 extends Base {
    public void test() {
        System.out.println("Base1");
    }
}

class Base2 extends Base {
    public void test() {
        System.out.println("Base2");
    }
}

class Test {
    public static void main(String[] args) {
        Base obj = new Base1();
        ((Base2)obj).test(); // CAST
    }
}