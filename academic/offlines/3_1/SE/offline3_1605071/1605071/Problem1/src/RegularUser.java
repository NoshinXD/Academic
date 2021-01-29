import java.util.Random;
import java.util.Scanner;

public class RegularUser implements IObserver {
    private int id;
    private boolean op;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public boolean isOp() {
        return op;
    }

    public void setOp(boolean op) {
        this.op = op;
    }

    @Override
    public void update(String cls, int i, int j) {
        int reply = 0;

        if(i == 0 && j == 1)
        {
            System.out.println("Regular user prompt: Server is partially down now\n");

            while(true)
            {
                System.out.println("Do you want to continue using the limited functionality or pay $20 per hour to enjoy the full functionality taking service from server of DEF company? In the 2nd case, all your data will be copied to the server of DEF company.");
                System.out.println("Please choose:");
                System.out.println("1. limited functionality");
                System.out.println("2. pay for full functionality");

                Scanner sc = new Scanner(System.in);
                reply = sc.nextInt();

                if(reply == 1)
                {
                    System.out.println("Server ABC is giving limited functionality\n");
                    setOp(false);
                    break;
                }
                else if(reply == 2)
                {
                    setOp(true);
                    break;
                }
                else
                {
                    System.out.println("Please press 1 or 2");
                }
            }
        }

        if(i == 0 && j == 2)
        {
            System.out.println("Regular user prompt: Server is fully down now.\n");

            while(true)
            {
                System.out.println("Do you want to pay $20 per hour to take service from the server of DEF company? Note that, it will copy all your data to the server of DEF company.");
                System.out.println("Please choose:");
                System.out.println("1. yes, pay $20 per hour");
                System.out.println("2. no");

                Scanner sc = new Scanner(System.in);
                reply = sc.nextInt();


                if(reply == 1)
                {
                    setOp(true);
                    break;
                }
                if(reply == 2)
                {
                    setOp(false);
                    break;
                }
                else
                {
                    System.out.println("Please press 1 or 2");
                }
            }
        }

        if(i == 1 && j == 0)
        {
            System.out.println("Regular user prompt: Now the server is operational again.");

            if(isOp() == true)
            {
                System.out.println("Your total bill: x taka");
            }
            //s = "one";
            setOp(false);

        }
        if(i == 2 && j == 0)
        {
            System.out.println("Regular user prompt: Now the server is operational again.");

            if(isOp() == true)
            {
                System.out.println("Your total bill: x taka\n");
            }
            setOp(false);
        }

        if(i == 1 && j == 2)
        {
            System.out.println("Regular user prompt: Server is fully down now.\n");
        }

        if(i == 2 && j == 1)
        {
            System.out.println("Regular user prompt: Server is partially down now\n");
        }

    }
}
