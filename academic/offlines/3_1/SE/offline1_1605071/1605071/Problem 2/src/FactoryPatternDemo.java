import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FactoryPatternDemo {
    public static void shape_Comp_Act(String compName, String shapeName, double a, double b, double c)
    {
        System.out.println("Name of Compter : " + compName);
        Computer comp = null;
        Shape sh = null;
        int width = 0, height = 0;
        ComputerFactory compFactory = new ComputerFactory();
        if(compName.equals("A"))
        {
            comp = compFactory.getComuter("A");
        }
        else if(compName.equals("B"))
        {
            comp = compFactory.getComuter("B");
        }
        else if(compName.equals("C"))
        {
            comp = compFactory.getComuter("C");
        }
        width = comp.getWidth();
        height = comp.getHeight();

        System.out.println("Resolution : " + width + " X " + height);
        System.out.println("CPU name : " + comp.getCPU());
        System.out.println("MMU name : " + comp.getMMU());
        System.out.println("Name of shape : " + shapeName);

        if (shapeName.equalsIgnoreCase("CIRCLE")) {
            Circle cir = new Circle(a);
            cir.surface_area();
            cir.perimeter();
            if(height >= (2*a))
            {
                cir.display();
                cir.draw();
            }
            else
            {
                System.out.println("Resolution can't cover ; can't display!");
            }
        }
        else if (shapeName.equalsIgnoreCase("SQUARE")) {
            Square sq = new Square(a);
            sq.surface_area();
            sq.perimeter();
            if(height >= a)
            {
                sq.display();
                sq.draw();
            }
            else
            {
                System.out.println("Resolution can't cover ; can't display!");
            }
        }
        else if (shapeName.equalsIgnoreCase("RECTANGLE")) {
            Rectangle rec = new Rectangle(a,b);
            rec.surface_area();
            rec.perimeter();
            if(width >= a && height >= b)
            {
                rec.display();
                rec.draw();
            }
            else
            {
                System.out.println("Resolution can't cover ; can't display!");
            }

        }
        else if (shapeName.equalsIgnoreCase("TRIANGLE")) {
            Triangle tri = new Triangle(a,b,c);
            double area = tri.surface_area();
            tri.perimeter();
            double base;
            double h;

            /*if(a > b && a > c) base = a;
            else if(b > a && b > c) base = b;
            else base = c;
            h = (2 * area)/base;*/
            Double resh = Double.valueOf(height);
            Double resw = Double.valueOf(width);

            if(resw >= a && resh >= ((2*area)/a))
            {
                tri.display();
                tri.draw();
            }
            else if(resw >= b && resh >= ((2*area)/b))
            {
                tri.display();
                tri.draw();
            }
            else if(resw >= c && resh >= ((2*area)/c))
            {
                tri.display();
                tri.draw();
            }
            else
            {
                System.out.println("Resolution can't cover ; can't display!");
            }
        }

    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("in.txt"));

        while(true)
        {
            String compchoice, shapechoice;
            compchoice = br.readLine();
            double a = 0, b = 0, c = 0;

            if(compchoice.equalsIgnoreCase("BREAK"))
            {
                break;
            }

            shapechoice = br.readLine();

            if(shapechoice.equalsIgnoreCase("Circle"))
            {
                a = Integer.parseInt(br.readLine());
                b = 0;
                c = 0;
                //sc.nextLine();
            }
            else if(shapechoice.equalsIgnoreCase("Square"))
            {
                a = Integer.parseInt(br.readLine());
                b = 0;
                c = 0;
                //sc.nextLine();
            }
            else if(shapechoice.equalsIgnoreCase("Rectangle"))
            {
                a = Integer.parseInt(br.readLine());
                b = Integer.parseInt(br.readLine());
                c = 0;
                //sc.nextLine();
            }
            else if(shapechoice.equalsIgnoreCase("Triangle"))
            {
                a = Integer.parseInt(br.readLine());
                b = Integer.parseInt(br.readLine());
                c = Integer.parseInt(br.readLine());
                //sc.nextLine();
            }

            shape_Comp_Act(compchoice, shapechoice, a, b, c);
        }
    }
}
