package javagame;
import java.util.ArrayList;

public class Find_AI_Move {
    public static ArrayList<Co_ordinates> getAI_Move(Board board, Boolean maximizingPlayer, int alpha, int beta)
    {
        int n = board.getN();

        double allowed_time = 0;

        if(n == 8) allowed_time = 2.0;
        else if(n == 6) allowed_time = 1.0;

        int color = Constants.BLACK;
        ArrayList<Co_ordinates> from_to = new ArrayList<Co_ordinates>();

        Game g = new Game();
        g.moves(board, color);

        ArrayList<Checker> activeCheckerList = g.getActiveCheckerList(board, color);

        int final_from_x = -1;
        int final_from_y = -1;
        int final_to_x = -1;
        int final_to_y = -1;

        int max_val = Integer.MIN_VALUE;

        int best = Constants.MIN;

        Pair p = new Pair();
        ArrayList<Pair> pairList = p.makePair(activeCheckerList);

        final_from_x = pairList.get(0).from_co.getX();
        final_from_y = pairList.get(0).from_co.getY();
        final_to_x = pairList.get(0).to_co.getX();
        final_to_y = pairList.get(0).to_co.getY();

        long startTime = System.currentTimeMillis();

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
            tempBoard.getChecker(to_x, to_y).setColor(color);

            int depth = 3;
            int val = Alpha_Beta_Pruning.minimax(depth, tempBoard, false, alpha, beta);

            best = Math.max(best, val);
            alpha = Math.max(alpha, best);

            if(val > max_val)
            {
                max_val = val;
                final_from_x = from_x;
                final_from_y = from_y;
                final_to_x = to_x;
                final_to_y = to_y;
            }

            long endTime = System.currentTimeMillis();

            long duration = endTime - startTime;

            double dub_duration = (double) ((duration * 1.0) / 1000);

            if(dub_duration >= allowed_time)
            {
                //System.out.println("Time: " + dub_duration);
                break;
            }
        }

        //System.out.println("max_val: " + max_val);

        Co_ordinates from_co = new Co_ordinates(final_from_x, final_from_y);
        Co_ordinates to_co = new Co_ordinates(final_to_x, final_to_y);

        from_to.add(from_co);
        from_to.add(to_co);

        return from_to;
    }
}