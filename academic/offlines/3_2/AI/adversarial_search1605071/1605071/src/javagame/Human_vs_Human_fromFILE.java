package javagame;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Human_vs_Human_fromFILE {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("checkInput.txt"));
        int n = Integer.parseInt(br.readLine());
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
            board.printBoard();

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

            //System.out.print("Please enter co-ordinates of ur chosen checker: ");
            System.out.print("Ur chosen checker: ");

            String  co_ords = br.readLine();

            String[] co_ordsArr = co_ords.trim().split("\\s+");

            from_x = Integer.parseInt(co_ordsArr[0]);
            from_y = Integer.parseInt(co_ordsArr[1]);
            System.out.print("(" + from_x + " , " + from_y + ")");
            System.out.println();

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

            to_x = Integer.parseInt(co_ordsArr[2]);
            to_y = Integer.parseInt(co_ordsArr[3]);
            System.out.print("(" + to_x + " , " + to_y + ")");
            System.out.println();
            System.out.println();

            from_ch.setColor(-1);
            Checker to_ch = board.getChecker(to_x, to_y);
            to_ch.setColor(color);
            board.printBoard();

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
