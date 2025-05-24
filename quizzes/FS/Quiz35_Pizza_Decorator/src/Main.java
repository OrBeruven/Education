public class Main {
    public static void main(String[] args) {
        Pizza myPizza = new PeppyPaneer();
        System.out.println("The price of " + myPizza.getDescription() + " is " + myPizza.getPrice());
        //Should print : The price of peppy paneer pizza is 10

        myPizza = new JalapenoTopping(myPizza);
        System.out.println("The price of " + myPizza.getDescription() + " is " + myPizza.getPrice());
        //Should print : The price of peppy paneer pizza with Jalapeno is 14

        myPizza = new JalapenoTopping(myPizza);
        System.out.println("The price of " + myPizza.getDescription() + " is " + myPizza.getPrice());
        //Should print : The price of peppy paneer pizza with Jalapeno with jalapeno is 18

        myPizza = new BBQTopping(myPizza);
        System.out.println("The price of " + myPizza.getDescription() + " is " + myPizza.getPrice());
        //Should print : The price of peppy paneer pizza with Jalapeno with jalapeno with BBQ is 23
    }
}