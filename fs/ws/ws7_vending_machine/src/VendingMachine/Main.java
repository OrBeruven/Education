/*
 *       Programmer : Or
 *       Reviewer : Moshe
 *       Date : 21.06.2023
 */
package VendingMachine;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;
public class Main {
    private VM vm;
    private Coin shekelCoin;

    @BeforeEach
    public void setUp() {
        Monitor screen = new Monitor();
        ArrayList<Product> products = new ArrayList<>();
        products.add(new Bamba());
        products.add(new Bisli());
        products.add(new Kinder());
        vm = new VM(screen, products);
        shekelCoin = CoinEnum.SHEKEL;
        vm.on();
    }

    @Test
    public void testInsertMoney() {
        vm.insertMoney(shekelCoin);
        double balance = vm.getBalance();
        Assertions.assertEquals(1, balance);

        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        balance = vm.getBalance();
        Assertions.assertEquals(3, balance);
    }

    @Test
    public void testchooseProduct() {
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.chooseProduct("bamba");
        Assertions.assertEquals(0, vm.getBalance());
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);

        vm.chooseProduct("koko");
        Assertions.assertEquals(8, vm.getBalance());

        vm.insertMoney(shekelCoin);
        vm.chooseProduct("kinder");
        Assertions.assertEquals(0, vm.getBalance());
        vm.insertMoney(shekelCoin);
        Assertions.assertEquals(1, vm.getBalance());
    }

    @Test
    public void testCancel() {
        vm.insertMoney(shekelCoin);
        vm.insertMoney(shekelCoin);
        vm.cancel();
        double balance = vm.getBalance();
        Assertions.assertEquals(0, balance);
    }

    @Test
    public void testOff() {
        vm.off();
        boolean isOn = vm.isOn();
        Assertions.assertFalse(isOn);

        vm.on();
        isOn = vm.isOn();
        Assertions.assertTrue(isOn);

        vm.on();
        isOn = vm.isOn();
        Assertions.assertTrue(isOn);
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
