import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        Derived d = new Derived();
    }
}

class Base {
    private int member1 = 1;
    private int member2 = 2;
    public Base() throws IOException {
        System.out.println("Base Ctor");
        print();
    }
    public void print() throws IOException {
        System.out.println(member1 + " " + member2);
    }
}

class Derived extends Base {
    private int member3 = 3;
    private int member4 = 4;
    public Derived() throws IOException {
        super();
        System.out.println("Derived Ctor");
        print();
    }

    @Override
    public void print() throws RuntimeException{
        System.out.println(member3 + " " + member4);
    }
}