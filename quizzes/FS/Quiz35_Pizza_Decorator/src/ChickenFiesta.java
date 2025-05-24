public class ChickenFiesta extends PizzaBase {
    private final static int CHICKENPRICE_PRICE = 13;
    public ChickenFiesta() {
        super();
    }
    @Override
    public String getDescription() {
        return super.getDescription() + " PeppyPaneer";
    }

    @Override
    public int getPrice() {
        return super.getPrice() + CHICKENPRICE_PRICE;
    }
}
