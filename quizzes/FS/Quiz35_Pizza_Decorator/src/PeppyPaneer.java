public class PeppyPaneer extends PizzaBase {
    private final static int PEPPYPANEER_PRICE = 10;
    public PeppyPaneer() {
        super();
    }
    @Override
    public String getDescription() {
        return super.getDescription() + " PeppyPaneer";
    }

    @Override
    public int getPrice() {
        return super.getPrice() + PEPPYPANEER_PRICE;
    }
}
