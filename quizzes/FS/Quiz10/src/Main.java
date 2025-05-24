import java.util.Stack;

public class Main {
    public static void main(String[] args) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(34);
        stack.push(3);
        stack.push(31);
        stack.push(98);
        stack.push(92);
        stack.push(23);

        System.out.println(stack.toString());

        sortStackAscending(stack);
        System.out.println(stack.toString());
    }

    public static void sortStackAscending(Stack<Integer> stackToSort) {
        Stack<Integer> auxiliaryStack = new Stack<Integer>();
        auxiliaryStack.push(stackToSort.peek());
        stackToSort.pop();

        while (!stackToSort.empty()) {
            Integer temp = stackToSort.peek();
            stackToSort.pop();

            if (temp < auxiliaryStack.peek()) {
                auxiliaryStack.push(temp);
            } else {
                while (!auxiliaryStack.empty() && auxiliaryStack.peek() < temp) {
                  stackToSort.push(auxiliaryStack.peek());
                  auxiliaryStack.pop();
                }

                auxiliaryStack.push(temp);
            }
        }

        while (!auxiliaryStack.empty()) {
            stackToSort.push(auxiliaryStack.peek());
            auxiliaryStack.pop();
        }
    }
}