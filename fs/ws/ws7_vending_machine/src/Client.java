import VendingMachine.*;
import org.junit.jupiter.api.Assertions;

import java.util.ArrayList;

public class Client {
    public static void main(String[] args) {
        VM vm = null;
        Coin shekelCoin = null;
        Monitor screen = new Monitor();
        ArrayList<Product> products = new ArrayList<>();
        products.add(new Bamba());
        products.add(new Bisli());
        products.add(new Kinder());
        vm = new VM(screen, products);
        shekelCoin = CoinEnum.SHEKEL;
        vm.on();

        vm.insertMoney(shekelCoin);
        double balance = vm.getBalance();
        Assertions.assertEquals(1, balance);

        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        balance = vm.getBalance();
        System.out.println(balance);
        Assertions.assertEquals(3, balance);
    }
}

class Bamba implements Product{
    @Override
    public String getName() {

        return "bamba";
    }
    @Override
    public double getPrice() {
        return 5;
    }
}

class Bisli implements Product{
    @Override
    public String getName() {
        return "bisli";
    }
    @Override
    public double getPrice() {
        return 3;
    }
}
class Kinder implements Product{
    @Override
    public String getName() {
        return "kinder";
    }
    @Override
    public double getPrice() {
        return 8;
    }
}
