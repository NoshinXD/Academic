package javagame;
import java.util.ArrayList;
import java.util.Scanner;

public class Human_vs_Human {
    public static void play_human_vs_human (int n) {
        //int n = 8;
        Board board = new Board(n);
        board.initiateBoard();

        Scanner sc=new Scanner(System.in);

        int turn = 0;
        int color, oppositeColor;

        int from_x, from_y, to_x, to_y;

        while (true)
        {
            turn++;

            if(turn%2 != 0)
            {
                System.out.println("move for BLACK: ");
                color = Constants.BLACK;
                oppositeColor = Constants.WHITE;
            }
            else
            {
                System.out.println("move for WHITE");
                color = Constants.WHITE;
                oppositeColor = Constants.BLACK;
            }
            System.out.println();
            //board.printBoard();
            board.printBoardwithStr();

            Game g = new Game();
            ArrayList<Checker> activeCheckerList = g.getActiveCheckerList(board, color);
            ArrayList<Checker> canMoveCheckerList = new ArrayList<Checker>();
            g.moves(board, color);

            System.out.println("Co-ordinates of existing checkers: ");
            for(int i=0; i<activeCheckerList.size(); i++)
            {
                Checker ch = activeCheckerList.get(i);
                ch.printCheckerCoOrdinates();
                if(ch.getMoveList().size() != 0)
                {
                    canMoveCheckerList.add(ch);
                }
            }
            System.out.println();
            System.out.println();
            System.out.println("Co-ordinates of existing checkers with moves:");

            for(int i=0; i<canMoveCheckerList.size(); i++)
            {
                canMoveCheckerList.get(i).printCheckerCoOrdinates();
            }

            System.out.println();
            System.out.print("Please enter co-ordinates of ur move: ");

            while(true)
            {
                from_x = sc.nextInt();
                from_y = sc.nextInt();

                Boolean validChecker = false;
                for(int i=0; i<canMoveCheckerList.size(); i++)
                {
                    if(canMoveCheckerList.get(i).isEqualCoOrdinates(from_x, from_y))
                    {
                        System.out.println("got valid checker!");
                        validChecker = true;
                        break;
                    }
                }

                if(validChecker)
                {
                    break;
                }
                else
                {
                    System.out.println("please choose a valid checker with next move.");
                }
            }
            System.out.println("all possible move for " + "(" + from_x + "," + from_y + "):" );
            Checker from_ch = board.getChecker(from_x, from_y);

            ArrayList<Co_ordinates> moveList = from_ch.getMoveList();

            for(int i=0; i<moveList.size(); i++)
            {
                moveList.get(i).print();
            }

            System.out.println("Please enter ur move: ");

            while(true)
            {
                to_x = sc.nextInt();
                to_y = sc.nextInt();

                Boolean validMove = false;
                for(int i=0; i<moveList.size(); i++)
                {
                    if(moveList.get(i).isEqual(to_x, to_y))
                    {
                        System.out.println("Got valid move!");
                        validMove = true;
                        break;
                    }
                }

                if(validMove)
                {
                    break;
                }
                else
                {
                    System.out.println("Please enter a valid move.");
                }
            }

            from_ch.setColor(-1);
            Checker to_ch = board.getChecker(to_x, to_y);
            to_ch.setColor(color);
            //board.printBoard();
            board.printBoardwithStr();

            System.out.println(";;;;;;;;;;;;;;;;;;;;;;;;;");
            int cost = Heuristics.getHeuristicCost(board);
            System.out.println("heuristic: cost: " + cost);
            System.out.println(";;;;;;;;;;;;;;;;;;;;;;;;;");

            ArrayList<Checker> newActiveCheckerList = g.getActiveCheckerList(board, color);
            boolean isConnected = EndGame.isConnected(newActiveCheckerList);
            if(isConnected)
            {
                if(color == Constants.BLACK) System.out.println("BLACK wins!");
                else System.out.println("WHITE wins");
                break;
            }

            ArrayList<Checker> activeOppositeCheckerList = g.getActiveCheckerList(board, oppositeColor);
            boolean isOppositeConnected = EndGame.isConnected(activeOppositeCheckerList);
            if(isOppositeConnected)
            {
                //System.out.println("here");
                if(oppositeColor == Constants.BLACK) System.out.println("BLACK wins!");
                else System.out.println("WHITE wins");
                break;
            }
        }
    }
}
