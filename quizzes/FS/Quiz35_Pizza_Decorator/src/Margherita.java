public class Margherita extends PizzaBase {
    private final static int MARGHERITA_PRICE = 12;
    public Margherita() {
        super();
    }
    @Override
    public String getDescription() {
        return super.getDescription() + " Margherita";
    }

    @Override
    public int getPrice() {
        return super.getPrice() + MARGHERITA_PRICE;
    }
}
