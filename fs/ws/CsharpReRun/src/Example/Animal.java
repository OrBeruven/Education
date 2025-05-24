package Example;

public class Animal {
    private int numOfLegs = 2;
    
    public void makeNoise() {
        System.out.println("Hello + " + numOfLegs);
    }

    public static void main(String[] args) {

    }
}

class Dog extends Animal {
    int numOfLegs = 4;
    Dog(int numOfLegs) {
        super();
        this.numOfLegs = numOfLegs;
    }

    @Override
    public void makeNoise() {
        System.out.println("Hav");
    }
}

abstract class Shape {
    int num;
    private void stam() {
        System.out.println("stam");
    }
}

