public abstract class Shape {
    private String color;
    private boolean filled;

    Shape() {
        color = "green";
        filled = true;
    }

    Shape(String colorFromUser, boolean fill) {
        color = colorFromUser;
        filled = fill;
    }

    abstract public double getArea();
    abstract public double getPerimeter();

    public String getColor() {
        return this.color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public boolean getFilled() {
        return this.filled;
    }

    public void setFilled(boolean fill) {
        this.filled = fill;
    }

    public String toString() {
        return "Shape with color " + this.color + " and filled = " + this.filled;
    }
}
