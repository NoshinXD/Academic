import java.util.Scanner;

public class PremiumUser implements IObserver{
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
            System.out.println("Premium user prompt: Server is partially down now\n");

            while(true)
            {
                System.out.println("Do you want to use service from two servers(partially from the server of our company and partially from the server of DEF company) or from one server (server of DEF company)?)");
                System.out.println("Please choose:");
                System.out.println("1. one server");
                System.out.println("2. two servers");

                Scanner sc = new Scanner(System.in);
                reply = sc.nextInt();


                if(reply == 1)
                {
                    System.out.println("Sever DEF is functioning\n");
                    setOp(false);
                    break;
                }
                if(reply == 2)
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
            System.out.println("Premium user prompt: Server is fully down now. Service is now being provided by DEF company.\n");
            setOp(true);
        }

        if(i == 1 && j == 2)
        {
            System.out.println("Premium user prompt: Server is fully down now.\n");

            if(isOp() == true)
            {
                System.out.println("All of your services has been shifted to the server of DEF company.\n");

                //setOp(false);
            }
            setOp(true);
        }

        if(i == 1 && j == 0)
        {
            System.out.println("Premium user prompt: Now the server is operational again.\n");
        }

        if(i == 2 && j == 0)
        {
            System.out.println("Premium user prompt: Now the server is operational again.\n");
        }

        if(i == 2 && j == 1)
        {
            System.out.println("Premium user prompt: Server is partially down now.\n");
        }

    }
}
