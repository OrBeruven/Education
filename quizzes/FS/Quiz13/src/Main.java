import java.util.Collection;
import java.util.Hashtable;
import java.util.Map;
import java.util.Set;

public class Main {
    public static void main(String[] args) {
        Ex();
        Hashtable
    }

    public static void Q1() {
        /*Code for removing static*/
        Singleton<Integer> singleton = new Singleton<>();
        singleton = singleton.getInstance();

        /*code for removing <T> and using raw type*/
        //Singleton<Integer> singleton2 = Singleton.getInstance();
    }

    public static void Q2() {
        interface Person {
            default void sayHello() {
                System.out.println("Hello");
            }
        }

        interface Male {
            default void sayHello() {
                System.out.println("Hi");
            }
        }

        class Sam implements Person, Male {

            @Override
            public void sayHello() {
                Person.super.sayHello();
            }
        }

        Sam sam = new Sam();
        sam.sayHello();
        Sam secondSam = new Sam();
        secondSam.sayHello();
    }

    public static void Ex() {
        Calculator calc = new Calculator();
        System.out.println("1 + 2 = " + calc.operate("+", 1, 2));
        System.out.println("1 - 2 = " + calc.operate("-", 1, 2));
        System.out.println("1 / 2 = " + calc.operate("/", 1, 2));
        System.out.println("1 * 2 = " + calc.operate("*", 1, 2));
    }
}