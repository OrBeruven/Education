package innerclasses;

public class Main {
    public static void main(String[] args) {
        OuterClass st = new OuterClass();
        OuterClass.InnerClass fl = st.new InnerClass();
        fl.foo(23);

        AnotherMain anotherMain = new AnotherMain();
        anotherMain.foo();
    }
}

class OuterClass {
    public int x = 0;
    class InnerClass {
        public int x = 1;
        void foo(int x) {
            System.out.println("x = " + x);
            System.out.println("this.x = " + this.x);
            System.out.println("OuterClass.this.x = "
                    + OuterClass.this.x);
        }
    }
}