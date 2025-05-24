public class Outer {
    int x = 3;
    static int y = 4;

    public class Inner {
        private int InnerVar = 20;
        private static int staticInnerVar = 21;
        void foo() {
            System.out.println(x);
            System.out.println(y);
            System.out.println(InnerVar);
            System.out.println(staticInnerVar);
        }

        static void foo2() {
            //System.out.println(x); error
            System.out.println(y);
            //System.out.println(InnerVar); error
            System.out.println(staticInnerVar);
        }

        enum InnerEnum {
            TRUE,
            FALSE;

            void foo3() {
                //System.out.println(x); error
                System.out.println(y);
            }
        }
    }

    enum Enum {
        RED;
        void foo() {
            //System.out.println(x); error
            System.out.println(y);
        }
    }

    public static class Nested {
        private int nestedVar = 20;
        private static int staticNestedVar = 21;
        void foo(int z) {
            System.out.println("in nested class foo : " + z);
            //System.out.println(x); error
            System.out.println(y);
            System.out.println(nestedVar);
            System.out.println(staticNestedVar);
        }

        static void foo2() {
            //System.out.println(nestedVar); error
            System.out.println(staticNestedVar);
        }
    }

    public static void main(String[] args) {
        Outer.Nested on = new Outer.Nested();
        on.foo(1);

        Outer.Nested on2 = new Outer.Nested();
        on2.foo(2);
    }
}