public class Square implements Shape {
    double a;

    public Square(double a)
    {
        this.a = a;
    }

    @Override
    public void display() {
        System.out.println("Inside Square :: display() method.");
    }

    @Override
    public void draw() {
        System.out.println("Inside Square :: draw() method.");
    }

    @Override
    public double surface_area() {
        //return a * a ;
        System.out.println("Surface-area : " + a * a);
        return 0;
    }

    @Override
    public void perimeter() {
        //return 4 * a;
        System.out.println("Perimeter : " + 4 * a);
    }
}
