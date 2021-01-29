package javagame;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class checkMoveLOA {
    public static void main(String[] args) throws IOException {
        /*Game_moveFromFile g = new Game_moveFromFile();
        Board board = g.gameMoves();
        board.printBoard();*/

        int n = 8;
        Board board = new Board(n);
        board.initiateBoard();

        System.out.println("real board: ");
        board.printBoard(); //checked
        board.printBoardwithStr();

        /*Board tempBoard = new Board(n);
        tempBoard.copyBoard(board);
        System.out.println("copy board: ");
        tempBoard.printBoard();

        System.out.println("after changing: ");
        tempBoard.getChecker(3, 2).setColor(0);
        System.out.println("real board:");
        board.printBoard();
        System.out.println("copy board:");
        tempBoard.printBoard();*/

        Scanner sc=new Scanner(System.in);

        int from_x, from_y, to_x, to_y;

        int turn = 0;
        int color = 0;

        //board.blankBoard();
        //Checker from_ch = board.getChecker(5, 3);
        //board.getChecker(5, 3).setColor(0); //checking black=0

        /*board.getChecker(1, 0).setColor(1);
        board.getChecker(1, 7).setColor(1);
        board.getChecker(2, 0).setColor(1);
        board.getChecker(2, 7).setColor(1);
        board.getChecker(3, 0).setColor(1);
        board.getChecker(3, 7).setColor(1);
        board.getChecker(4, 0).setColor(1);
        board.getChecker(4, 7).setColor(1);
        board.getChecker(5, 0).setColor(1);
        board.getChecker(5, 7).setColor(1);
        board.getChecker(6, 0).setColor(1);
        board.getChecker(6, 7).setColor(1);*/

        /*board.getChecker(1,4).setColor(1);
        board.getChecker(2,2).setColor(1);
        board.getChecker(2,3).setColor(1);
        board.getChecker(3,2).setColor(1);
        board.getChecker(3,3).setColor(1);
        board.getChecker(4,3).setColor(1);
        board.getChecker(4,4).setColor(1);
        //board.getChecker(4,6).setColor(1);
        board.getChecker(5,2).setColor(1);*/
        //board.getChecker(0, 1).setColor(-1);
        //board.getChecker(0, 7).setColor(color);

        /*board.printBoard();

        int cost = Heuristics.getMobilityCost(board, 0);
        System.out.println("blackmobilityCost: " + cost);
        cost = Heuristics.getMobilityCost(board, 1);
        System.out.println("whitemobilityCost: " + cost);
        System.out.println();
        cost = Heuristics.getAreaCost(board, 0);
        System.out.println("blackareaCost: " + cost);
        cost = Heuristics.getAreaCost(board, 1);
        System.out.println("whiteareaCost: " + cost);
        System.out.println();
        cost = Heuristics.getPieceSquareTableCost(board, 0);
        System.out.println("blackpieceSquareCost: " + cost);
        cost = Heuristics.getPieceSquareTableCost(board, 1);
        System.out.println("whitepieceSquareCost: " + cost);
        System.out.println();
        cost = Heuristics.getQuadCost(board, 0);
        System.out.println("blackquadCost: " + cost);
        cost = Heuristics.getQuadCost(board, 1);
        System.out.println("whitequadCost: " + cost);
        System.out.println();
        cost = Heuristics.getConnectedCost(board, 0);
        System.out.println("blackConnectionCost: " + cost);
        cost = Heuristics.getConnectedCost(board, 1);
        System.out.println("whiteConnectionCost: " + cost);
        System.out.println("-----------------------------------------");*/
        Game g = new Game();
        g.moves(board, color);
        ArrayList<Checker> activeCheckerList = g.getActiveCheckerList(board, color);

        int cost = Heuristics.getDensityCost(board, color);
        System.out.println("cost: " + cost);

        /*Pair p = new Pair();
        ArrayList<Pair> pairList = p.makePair(activeCheckerList);
        for(int i=0; i<pairList.size(); i++)
        {
            System.out.println("-----------------");
            pairList.get(i).from_co.print();
            pairList.get(i).to_co.print();
            System.out.println("-----------------");
        }*/

        /*Collections.shuffle(pairList);
        System.out.println("after shuffle");
        for(int i=0; i<pairList.size(); i++)
        {
            System.out.println("-----------------");
            pairList.get(i).from_co.print();
            pairList.get(i).to_co.print();
            System.out.println("-----------------");
        }*/
        /*System.out.println("from checkMoveLOA: ");
        System.out.println();
        for(int i=0; i<activeCheckerList.size(); i++)
        {
            Checker ch = activeCheckerList.get(i);
            ArrayList<Co_ordinates> moveList = ch.getMoveList();
            for(int j=0; j<moveList.size(); j++)
            {
                Co_ordinates co = moveList.get(j);
                System.out.println("---------------------");
                ch.printCheckerCoOrdinates();
                co.print();
                System.out.println("---------------------");
            }
        }*/

        boolean isConnected = EndGame.isConnected(activeCheckerList);

        System.out.println("isConnected: " + isConnected);

        double q = 3.2;
        int q_x = (int) Math.round(q);
        System.out.println(q_x);

        /*System.out.println("now move: ");
        board.printBoard();

        Game g = new Game();
        g.moves(board, 0);

        ArrayList<Co_ordinates> moveList = from_ch.getMoveList();

        for(int i=0; i<moveList.size(); i++)
        {
            moveList.get(i).print();
        }

        from_ch.setColor(-1);*/
    }
}
