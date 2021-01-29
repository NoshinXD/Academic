package javagame;
import java.util.Scanner;

public class LOA {
    public static void main(String[] args) {
        Scanner sc= new Scanner(System.in);

        System.out.println("Enter board size: ");
        //int n = sc.nextInt();
        int n = 8;

        System.out.println("Options:");
        System.out.println("1. Human vs Human");
        System.out.println("2. Human vs AI");

        System.out.println("Enter ur option (1 or 2): ");

        int choice;

        while (true)
        {
            choice = sc.nextInt();
            if(choice == 1 || choice == 2)
            {
                break;
            }
            else
            {
                System.out.println("Please enter 1 or 2");
            }
        }

        if(choice == 1)
        {
            Human_vs_Human.play_human_vs_human(n);
        }
        else
        {
            HUMAN_vs_AI.play_human_vs_ai(n);
        }
    }
}
