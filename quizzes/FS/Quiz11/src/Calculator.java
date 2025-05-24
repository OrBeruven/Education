import java.util.HashMap;

public class Calculator {
    private HashMap<String, Operator> mapOperator = new HashMap<String, Operator>();

    public Calculator() {
        Operator add = (a, b) -> a + b;
        mapOperator.put("+", add);

        Operator sub = new Operator() {
            @Override
            public int operate(int a, int b) {
                return a - b;
            }
        };
        mapOperator.put("-", sub);
        class Div implements Operator {
            @Override
            public int operate(int a, int b) {
                return a / b;
            }
        }

        Operator div = new Div();
        mapOperator.put("/", div);

        Operator mul = new Mul();
        mapOperator.put("*", mul);
    }

    static class Mul implements Operator {
        @Override
        public int operate(int a, int b) {
            return a * b;
        }
    }

    interface Operator {
        int operate(int a, int b);
    }

    public void addOperator(String key, Operator o) {
        mapOperator.put(key, o);
    }

    public int operate(String key, int a, int b) {
        return mapOperator.get(key).operate(a, b);
    }

    public static void main(String[] args) {
        Calculator calc = new Calculator();

        System.out.println(calc.operate("+", 1, 2));
        System.out.println(calc.operate("-", 2, 1));
        System.out.println(calc.operate("/", 4, 2));
        System.out.println(calc.operate("*", 4, 2));
    }
}