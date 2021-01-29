package javagame;
import java.util.ArrayList;
import java.util.Scanner;

public class HUMAN_vs_AI {
    public static void play_human_vs_ai (int n) {
        Scanner sc=new Scanner(System.in);

        //int n = 8;
        Board board = new Board(n);
        board.initiateBoard();

        int turn = 0;
        int color, oppositeColor;

        int from_x, from_y, to_x, to_y;

        while (true)
        {
            turn++;

            if(turn%2 != 0)
            {
                System.out.println("move for AI: ");
                color = Constants.BLACK;
                oppositeColor = Constants.WHITE;

                System.out.println();
                //board.printBoard();
                board.printBoardwithStr();

                Game g = new Game();

                long startTime = System.currentTimeMillis();

                ArrayList<Co_ordinates> from_to_list = Find_AI_Move.getAI_Move(board, true, Constants.MIN, Constants.MAX);

                //board.printBoard();

                Co_ordinates from_co = from_to_list.get(0);
                Co_ordinates to_co = from_to_list.get(1);

                from_x = from_co.getX();
                from_y = from_co.getY();
                System.out.println("from_co: (" + from_x + "," + from_y + ")");
                board.getChecker(from_x, from_y).setColor(-1);

                to_x = to_co.getX();
                to_y = to_co.getY();
                System.out.println("to_co: (" + to_x + "," + to_y + ")");
                board.getChecker(to_x, to_y).setColor(color);

                long endTime = System.currentTimeMillis();

                long duration = endTime - startTime;
                //System.out.println("Time: " + duration);

                System.out.println();
                //board.printBoard();
                board.printBoardwithStr();
                System.out.println();

                //int cost = Heuristics.getHeuristicCost(board);
                //System.out.println("cost: " + cost);

                ArrayList<Checker> newActiveCheckerList = g.getActiveCheckerList(board, color);
                boolean isConnected = EndGame.isConnected(newActiveCheckerList);
                if(isConnected)
                {
                    System.out.println("BLACK wins");
                    break;
                }

                ArrayList<Checker> activeOppositeCheckerList = g.getActiveCheckerList(board, oppositeColor);
                boolean isOppositeConnected = EndGame.isConnected(activeOppositeCheckerList);
                if(isOppositeConnected)
                {
                    System.out.println("WHITE wins!");
                    break;
                }
            }
            else
            {
                System.out.println("move for HUMAN");
                color = Constants.WHITE;
                oppositeColor = Constants.BLACK;

                System.out.println();
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
                    System.out.print("Co-ordinate: ");
                    Checker canMoveCh = canMoveCheckerList.get(i);
                    canMoveCh.printCheckerCoOrdinates();
                    System.out.println();
                    System.out.println("all possible move: ");
                    ArrayList<Co_ordinates> possibleMoveList = canMoveCh.getMoveList();

                    for(int j=0; j<possibleMoveList.size(); j++)
                    {
                        possibleMoveList.get(j).print();
                    }
                    System.out.println();
                }
                System.out.println("---------------------------------------");
                System.out.println();

                System.out.print("Ur chosen checker: ");

                from_x = sc.nextInt();
                from_y = sc.nextInt();

                System.out.println("all possible move for " + "(" + from_x + "," + from_y + "):" );
                Checker from_ch = board.getChecker(from_x, from_y);

                ArrayList<Co_ordinates> moveList = from_ch.getMoveList();

                for(int i=0; i<moveList.size(); i++)
                {
                    moveList.get(i).print();
                }
                System.out.println("---------------------------------------");
                //System.out.print("Please enter ur move: ");
                System.out.print("Ur move: ");

                to_x = sc.nextInt();
                to_y = sc.nextInt();

                System.out.println();
                System.out.println();

                from_ch.setColor(-1);
                Checker to_ch = board.getChecker(to_x, to_y);
                to_ch.setColor(color);
                //board.printBoard();
                board.printBoardwithStr();
                System.out.println();

                ArrayList<Checker> newActiveCheckerList = g.getActiveCheckerList(board, color);
                boolean isConnected = EndGame.isConnected(newActiveCheckerList);
                if(isConnected)
                {
                    System.out.println("WHITE wins");
                    break;
                }

                ArrayList<Checker> activeOppositeCheckerList = g.getActiveCheckerList(board, oppositeColor);
                boolean isOppositeConnected = EndGame.isConnected(activeOppositeCheckerList);
                if(isOppositeConnected)
                {
                    System.out.println("BLACK wins!");
                    break;
                }
            }

            //if(turn == 1) break;
        }
    }
}
