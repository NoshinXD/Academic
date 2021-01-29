public class Triangle implements Shape {
    double a, b, c;

    public Triangle(double a, double b, double c)
    {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    @Override
    public void display() {
        System.out.println("Inside Triangle :: display() method.");
    }

    @Override
    public void draw() {
        System.out.println("Inside Triangle :: draw() method.");
    }

    @Override
    public double surface_area() {
        double s = 0.5 * (a + b + c);
        double t = s * (s - a) * (s - b) * (s - c);
        double res = Math.sqrt(t);
        System.out.println("Surface-area : " + res);
        return res;
    }

    @Override
    public void perimeter() {
        //return a + b + c;
        System.out.println("Perimeter : " + (a + b + c));
    }
}
