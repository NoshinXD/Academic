public class Rectangle implements Shape {
    double a, b;

    public Rectangle(double a, double b)
    {
        this.a = a;
        this.b = b;
    }

    @Override
    public void display() {
        System.out.println("Inside Rectangle :: display() method.");
    }

    @Override
    public void draw() {
        System.out.println("Inside Rectangle :: draw() method.");
    }

    @Override
    public double surface_area() {
        //return a * b;
        System.out.println("Surface-area : " + a * b);
        return 0;
    }

    @Override
    public void perimeter() {
        //return 2 * ( a + b );
        System.out.println("Perimeter : " + 2 * (a + b));
    }
}
