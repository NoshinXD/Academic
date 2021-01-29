public class Circle implements Shape {
    double r;

    public Circle(double r)
    {
        this.r = r;
    }

    @Override
    public void display() {
        System.out.println("Inside Circle :: display() method.");
    }

    @Override
    public void draw() {
        System.out.println("Inside Circle :: draw() method.");
    }

    @Override
    public double surface_area() {
        System.out.println("Surface-area : " + 3.1416 * r * r);
        return 0;
    }

    @Override
    public void perimeter() {
        System.out.println("Perimeter : " + 2 * 3.1416 * r);
    }
}
