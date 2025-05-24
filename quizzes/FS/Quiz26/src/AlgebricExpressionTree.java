public class AlgebricExpressionTree {
    TreeNode root = null;
    public AlgebricExpressionTree(TreeNode expression){
        this.root = expression;
    }

    public double calculate(){
        return recCalculate(root);
    }

    private double recCalculate(TreeNode root){
        if (isNum(root.value)){
            return Integer.parseInt(root.value);
        }

        return calc(recCalculate(root.left), recCalculate(root.right), root.value);
    }
    private double calc(double operand1, double operand2, String operator){
        double valToReturn = 0;

        switch (operator) {
            case "+":
                valToReturn = add(operand1, operand2);
                break;
            case "*":
                valToReturn = multi(operand1, operand2);
                break;
            case "-":
                valToReturn = sub(operand1, operand2);
                break;
        }
        return valToReturn;
    }
    private double add(double operand1, double operand2){
        return operand1 + operand2;
    }
    private double sub(double operand1, double operand2){
        return operand1 - operand2;
    }
    private double multi(double operand1, double operand2){
        return operand1 * operand2;
    }
    private double divide(double operand1, double operand2){
        return operand1 / operand2;
    }
    private boolean isNum(String value){
        return Character.isDigit(value.charAt(0));
    }
}

class TreeNode {
    String value;
    TreeNode left;
    TreeNode right;

    public TreeNode(String value) {
        this.value = value;
        this.left = null;
        this.right = null;
    }
}

