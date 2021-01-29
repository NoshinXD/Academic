package javagame;
import java.util.ArrayList;

public class Alpha_Beta_Pruning {

    static int minimax(int depth, Board board, Boolean maximizingPlayer, int alpha, int beta)
    {
        int n = board.getN();
        Game g_new = new Game();

        ArrayList<Checker> checkActiveCheckerList = g_new.getActiveCheckerList(board, Constants.BLACK);
        boolean isConnected = EndGame.isConnected(checkActiveCheckerList);
        if(isConnected)
        {
            return Integer.MAX_VALUE;
        }

        ArrayList<Checker> oppositeActiveCheckerList = g_new.getActiveCheckerList(board, Constants.WHITE);
        boolean oppositeIsConnected = EndGame.isConnected(oppositeActiveCheckerList);
        if(oppositeIsConnected)
        {
            return Integer.MIN_VALUE;
        }

        if(depth == 0)
        {
            int cost = Heuristics.getHeuristicCost(board);

            return cost;
        }

        if(maximizingPlayer)
        {
            int best = Constants.MIN;

            Game g = new Game();
            g.moves(board, Constants.BLACK); //existing black checkers er all possible moves calculate hbe; existing checker er attribute hishebe thake ei move gula

            ArrayList<Checker> activeCheckerList = g.getActiveCheckerList(board, Constants.BLACK);

            Pair p = new Pair();
            ArrayList<Pair> pairList = p.makePair(activeCheckerList);

            //System.out.println("move_sum: " + pairList.size());

            for(int i=0; i<pairList.size(); i++)
            {
                Co_ordinates from_co = pairList.get(i).from_co;
                Co_ordinates to_co = pairList.get(i).to_co;

                int from_x = from_co.getX();
                int from_y = from_co.getY();
                int to_x = to_co.getX();
                int to_y = to_co.getY();

                Board tempBoard = new Board(n);

                tempBoard.copyBoard(board);

                tempBoard.getChecker(from_x, from_y).setColor(-1);
                tempBoard.getChecker(to_x, to_y).setColor(Constants.BLACK); //tempBoard e move dilam

                int val = minimax(depth-1, tempBoard,false, alpha, beta);

                best = Math.max(best, val);
                alpha = Math.max(alpha, best);

                if(beta <= alpha)
                {
                    break;
                }
            }
            return best;
        }
        else
        {
            int best = Constants.MAX;

            Game g = new Game();
            g.moves(board, Constants.WHITE);

            ArrayList<Checker> activeOppositeCheckerList = g.getActiveCheckerList(board, Constants.WHITE);

            Pair p = new Pair();
            ArrayList<Pair> pairList = p.makePair(activeOppositeCheckerList);

            //System.out.println("move_sum: " + pairList.size());
            for(int i=0; i<pairList.size(); i++)
            {
                Co_ordinates from_co = pairList.get(i).from_co;
                Co_ordinates to_co = pairList.get(i).to_co;

                int from_x = from_co.getX();
                int from_y = from_co.getY();
                int to_x = to_co.getX();
                int to_y = to_co.getY();

                Board tempBoard = new Board(n);

                tempBoard.copyBoard(board);

                tempBoard.getChecker(from_x, from_y).setColor(-1);
                tempBoard.getChecker(to_x, to_y).setColor(Constants.WHITE);

                int val = minimax(depth-1, tempBoard,true, alpha, beta);

                best = Math.min(best, val);
                beta = Math.min(beta, best);

                if(beta <= alpha)
                {
                    break;
                }
            }
            return best;
        }
    }

}
