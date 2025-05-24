public class JalapenoTopping extends Topping {
    private Pizza pizza = null;
    public JalapenoTopping(Pizza pizza) {
        this.pizza = pizza;
    }

    @Override
    public String getDescription() {
        return pizza.getDescription() + "with Jalapeno";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + 4;
    }
}
