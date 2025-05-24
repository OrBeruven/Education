import java.lang.Math.*;
public class Circle extends Shape {
    private double radius;

    Circle() {
        radius = 1.0;
    }

    Circle(double newRadius) {
        this.radius = newRadius;
    }

    Circle(double newRadius, String color, boolean fill) {
        this.radius = newRadius;
        this.setColor(color);
        this.setFilled(fill);
    }

    public double getRadius() {
        return this.radius;
    }

    public void setRadius(double newRadius) {
        this.radius = newRadius;
    }

    public double getArea() {
        return this.radius * this.radius * Math.PI;
    }

    public double getPerimeter() {
        return 2 * Math.PI * this.radius;
    }

    @Override
    public String toString() {
        return "A Circle with radius " + this.radius + "wich is subclass of " + super.toString();
    }
}
