public class PaneerTopping extends Topping {
    private static final int PANEER_PRICE = 2;
    private Pizza pizza = null;
    public PaneerTopping(Pizza pizza) {
        this.pizza = pizza;
    }

    @Override
    public String getDescription() {
        return pizza.getDescription() + "with Paneer";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + PANEER_PRICE;
    }
}
