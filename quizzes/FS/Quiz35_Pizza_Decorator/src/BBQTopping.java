public class BBQTopping extends Topping {
    private static final int BBQ_PRICE = 5;
    private Pizza pizza = null;
    public BBQTopping(Pizza pizza) {
        this.pizza = pizza;
    }

    @Override
    public String getDescription() {
        return pizza.getDescription() + "with BBQ";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + BBQ_PRICE;
    }
}
