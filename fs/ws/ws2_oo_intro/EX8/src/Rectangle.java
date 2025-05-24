import java.lang.Math.*;
public class Rectangle extends Shape {
    private double width;
    private double length;

    Rectangle() {
        length = 1.0;
        width = 1.0;
    }

    Rectangle(double newWidth, double newLength) {

        this.width = newWidth;
        this.length = newLength;
    }

    Rectangle(double newWidth, double newLength, String color, boolean fill) {
        this.width = newWidth;
        this.length = newLength;
        this.setColor(color);
        this.setFilled(fill);
    }

    public double getWidth() {
        return this.width;
    }

    public void setWidth(double newWidth) {
        this.width = newWidth;
    }
    public double getLength() {
        return this.length;
    }

    public void setLength(double newLength) {
        this.length = newLength;
    }

    public double getArea() {
        return this.length * this.width;
    }

    public double getPerimeter() {
        return (2 * this.width) +  (2 * this.length);
    }

    @Override
    public String toString() {
        return "A Rectangle with length " + this.length + " and width " + this.width + " which is subclass of " + super.toString();
    }
}
