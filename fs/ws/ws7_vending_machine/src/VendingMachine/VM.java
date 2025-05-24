/*
*       Programmer : Or
*       Reviewer : Moshe
*       Date : 21.06.2023
 */
package VendingMachine;
import java.util.ArrayList;
public class VM {
    private double balance = 0;
    private States state = States.OFF;
    private Monitor monitor_obj = null;
    private ArrayList<Product> products = null;
    private Product currentProduct = null;

    public VM(Monitor monitor, ArrayList<Product> products) {
        this.monitor_obj = monitor;
        this.products = products;
    }

    private void setState(States newState) {
        this.state = newState;
    }
    public double getBalance() {
        return this.balance;
    }
    private void setBalance(double balance) {
        this.balance = balance;
    }
    Monitor getMonitorObj() {
        return this.monitor_obj;
    }
    States getState() {
        return this.state;
    }
    Product getCurrentProduct() {
        return this.currentProduct;
    }
    void setCurrentProduct(Product currentProduct) {
        this.currentProduct = currentProduct;
    }
    public void insertMoney(Coin coin) {
        this.setBalance(this.getBalance() + coin.getCurrencyInShekel(1));
    }

    void chooseProduct(String item) {
        for (Product prod : this.products) {
            if (prod.getName().equals(item)) {
                this.setCurrentProduct(prod);
                this.getState().chooseItem(this);
                return;
            }
        }

        this.getMonitorObj().print("Product not found");
    }

    public void on() {
        this.state.on(this);
    }
    public void off() {
        this.state.off(this);
    }
    public void cancel() {
        this.state.cancel(this);
    }

    private boolean hasEnoughMoney(){
        return (this.getBalance() >= this.getCurrentProduct().getPrice());
    }

    void getChange() {
        this.getMonitorObj().print("Your change is: " + this.getBalance());
        this.setBalance(0);
    }
    public boolean isOn() {
        return this.getState() != States.OFF;
    }

    enum States {
        IDLE {
            @Override
            void chooseItem(VM vm) {
                if (vm.hasEnoughMoney()){
                    vm.getMonitorObj().print("take your "+ vm.getCurrentProduct().getName() + " and leave!");
                    vm.setBalance(vm.getBalance() - vm.getCurrentProduct().getPrice());
                    vm.getChange();
                }
                else{
                    vm.getMonitorObj().print("Enter More money!");
                    vm.setState(WAIT);
                }
            }

            @Override
            void on(VM vm) {
                vm.getMonitorObj().print("Vending Machine is already ON");
            }
            @Override
            void cancel(VM vm) {
                vm.getChange();
                vm.getMonitorObj().print("Action Canceled");
            }

        },
        WAIT {
            @Override
            void chooseItem(VM vm) {
                if (vm.hasEnoughMoney()){
                    vm.getMonitorObj().print("take your "+ vm.getCurrentProduct().getName() + "and leave!");
                    vm.setBalance(vm.getBalance() - vm.getCurrentProduct().getPrice());
                    vm.getChange();
                    vm.setState(IDLE);
                }
                else{
                    vm.getMonitorObj().print("Enter More money!");
                }
            }

            @Override
            void on(VM vm) {
                vm.getMonitorObj().print("Vending Machine is already ON");
            }

            @Override
            void cancel(VM vm) {
                vm.getChange();
                vm.getMonitorObj().print("Action Canceled");
                vm.setState(IDLE);
            }
        },
        OFF {
            @Override
            void chooseItem(VM vm) {
                vm.getMonitorObj().print("Vending Machine is OFF");
            }
            @Override
            void on(VM vm) {
                vm.setState(IDLE);
                vm.getMonitorObj().print("Vending Machine is now ON");
            }
            @Override
            void off(VM vm) {
                vm.getMonitorObj().print("Vending Machine is OFF");
            }

            @Override
            void cancel(VM vm) {
                vm.getMonitorObj().print("Vending Machine is OFF");
            }
        };
        void off(VM vm) {
            vm.getChange();
            vm.getMonitorObj().print("Shutting down machine");
            vm.setState(OFF);
        }

        abstract void chooseItem(VM vm);
        abstract void on(VM vm);
        abstract void cancel(VM vm);
    }

}
