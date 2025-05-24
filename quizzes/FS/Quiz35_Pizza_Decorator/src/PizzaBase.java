abstract class PizzaBase implements Pizza{
    @Override
    public String getDescription() {
        return "Pizza";
    }

    @Override
    public int getPrice() {
        return 0;
    }
}
