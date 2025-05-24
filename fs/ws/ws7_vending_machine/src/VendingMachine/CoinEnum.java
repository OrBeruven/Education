package VendingMachine;

public enum CoinEnum implements Coin {
    EURO(4.0),
    DOLLAR(3.5),
    SHEKEL(1.0);

    private final double value;

    CoinEnum(double value) {
        this.value = value;
    }

    public double getCurrencyInShekel(double money) {
        return money * value;
    }
}