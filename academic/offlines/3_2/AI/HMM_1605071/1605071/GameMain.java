import java.util.Scanner;

public class GameMain {
    public static void main(String[] args) {
        int time = 0;
        System.out.println("Time : " + time);
        System.out.println();

        Room room = UpdateProbability.initialStateOfRoom();

        room.printRoom();
        //room.printGhost();

        Scanner sc = new Scanner(System.in);

        while(true)
        {
            System.out.println("1. Advance time");
            System.out.println("2. Use sensor");
            System.out.println("3. Catch ghost");
            System.out.println("Press 0 to end game");

            int choice = sc.nextInt();

            if(choice == 0) break;

            else if(choice == 1)
            {
                time++;
                System.out.println("Time: " + time);
                System.out.println();
                UpdateProbability.nextMoveGhost(room);
                //room.printGhost();
                UpdateProbability.updateProba_afterTimeAdvanced(room);
                System.out.println("after advancing time; updating with transiontion probability:");
                room.printRoom();
                //room.printGhost();
            }
            else if(choice == 2)
            {
                System.out.println("Please enter cell position to place sensor: ");
                int user_i = sc.nextInt();
                int user_j = sc.nextInt();

                //revealing color of sensed cell
                int color = UpdateProbability.findColor(room, user_i, user_j);
                String colorStr;
                if(color == Contstants.RED) colorStr = "RED";
                else if(color == Contstants.ORANGE) colorStr = "ORANGE";
                else colorStr = "GREEN";

                System.out.println("Color revealing for cell(" + user_i + " , " + user_j + ") ...   " + colorStr);

                UpdateProbability.updateProba_afterSesor(room, user_i, user_j);
                room.printRoom();
                //room.printGhost();
            }
            else if(choice == 3)
            {
                System.out.println("Please enter cell position to place sensor: ");
                int user_i = sc.nextInt();
                int user_j = sc.nextInt();

                int ghost_x = room.getGhost_Xpos();
                int ghost_y = room.getGhost_Ypos();

                if(user_i == ghost_x && user_j == ghost_y)
                {
                    System.out.println("Bingo! Caught ghost!");
                }
                else
                {
                    System.out.println("Sorry You lose!");
                    room.printGhost();
                }

                break;
            }
        }
    }
}
