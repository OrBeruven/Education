public class Square extends Rectangle{
    Square() {
        super ();
    }
    Square(double side) {
        super(side, side);
    }

    Square(double side, String color, boolean filled) {
        super(side, side, color, filled);
    }

    public void setSide(double side) {
        this.setLength(side);
        this.setWidth(side);
    }

    public double getSide() {
        return this.getWidth();
    }

    @Override
    public String toString() {
        return "Square";
    }
}
