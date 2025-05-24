public class FreshTomatoTopping extends Topping {
    private static final int TOMATO_PRICE = 1;
    private Pizza pizza = null;
    public FreshTomatoTopping(Pizza pizza) {
        this.pizza = pizza;
    }
    @Override
    public String getDescription() {
        return pizza.getDescription() + "with Fresh Tomato";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + TOMATO_PRICE;
    }
}
