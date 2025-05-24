public class CapsicumTopping extends Topping {
    private static final int CAPSICUM_PRICE = 3;
    private Pizza pizza = null;
    public CapsicumTopping(Pizza pizza) {
        this.pizza = pizza;
    }

    @Override
    public String getDescription() {
        return pizza.getDescription() + "with Capsicum";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + CAPSICUM_PRICE;
    }
}
