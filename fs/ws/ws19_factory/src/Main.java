/***************************
 *  Written by : Or
 *  Reviewer : Mor
 *  Date : 17.07.2023
 *  Factory Design pattern tests
 ***************************/
import java.security.InvalidKeyException;

public class Main {
    public static void main(String[] args) throws InvalidKeyException {
        Duck duck = new Main().new Duck();
        FactoryClass<String, Integer, String> factoryClass = new FactoryClass<>();
        factoryClass.add("One", Main::func1);
        factoryClass.add("Two", (Integer i) -> {return ((Integer)(i + 2)).toString();});
        factoryClass.add("Three", duck::funcDuck);
        factoryClass.add("Four", new Main()::instanceMethod);

        System.out.println(factoryClass.getInstance("One", 5));
        System.out.println(factoryClass.getInstance("Two", 5));
        System.out.println(factoryClass.getInstance("Three", 5));
        System.out.println(factoryClass.getInstance("Four", 5));
        //System.out.println(factoryClass.getInstance("Five", 5));

        //factoryClass.add(null, Main::func1);
        //System.out.println(factoryClass.getInstance(null, 5));

        //factoryClass.add("Six", null);
        //System.out.println(factoryClass.getInstance("Six", 5));
    }

    public static String func1(Integer i) {
        return ((Integer)(i + 1)).toString();
    }
    public String instanceMethod(Integer integer) {
        return ((Integer)(integer + 4)).toString();
    }

    class Duck {
        public String funcDuck(Integer integer) {
            String toReturn = "";
            for (int i = 0; i < integer; ++i) {
                toReturn += "quack";
            }

            return toReturn;
        }
    }
}
