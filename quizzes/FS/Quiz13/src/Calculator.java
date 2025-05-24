import java.util.HashMap;

public class Calculator {
    interface Operator {
        int operate(int a, int b);
    }

    private HashMap<String, Operator> mapOp = new HashMap<>();

    public int operate(String key, int a, int b) {
        return mapOp.get(key).operate(a, b);
    }

    public Calculator() {
        Operator add = (a, b) -> a + b;

        Operator sub = new Operator() {
            @Override
            public int operate(int a, int b) {
                return a - b;
            }
        };

        class Div implements Operator {
            @Override
            public int operate(int a, int b) {
                return a / b;
            }
        }
        Operator div = new Div();

        Operator mul = new Mul();

        mapOp.put("+", add);
        mapOp.put("-", sub);
        mapOp.put("/", div);
        mapOp.put("*", mul);
    }
}

class Mul implements Calculator.Operator {
    @Override
    public int operate(int a, int b) {
        return a * b;
    }
}
