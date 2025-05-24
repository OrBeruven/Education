public class Farmhouse extends PizzaBase {
    private final static int FARMHOUSE_PRICE = 11;
    public Farmhouse() {
        super();
    }
    @Override
    public String getDescription() {
        return super.getDescription() + " PeppyPaneer";
    }

    @Override
    public int getPrice() {
        return super.getPrice() + FARMHOUSE_PRICE;
    }
}
