package javagame;
import java.util.ArrayList;
import java.util.Collections;

public class Heuristics {
    public static int[][] getPieceSquareTable_8by8()
    {
        int[][] pieceSquareTable = {
                {-80, -25, -20, -20, -20, -20, -25, -80},
                {-25,  10,  10,  10,  10,  10,  10,  -25},
                {-20,  10,  25,  25,  25,  25,  10,  -20},
                {-20,  10,  25,  50,  50,  25,  10,  -20},
                {-20,  10,  25,  50,  50,  25,  10,  -20},
                {-20,  10,  25,  25,  25,  25,  10,  -20},
                {-25,  10,  10,  10,  10,  10,  10,  -25},
                {-80, -25, -20, -20, -20, -20, -25, -80}
        };
        return pieceSquareTable;
    }

    public static int[][] getPieceSquareTable_6by6()
    {
        int[][] pieceSquareTable = {
                {-80, -25, -20, -20, -25, -80},
                {-25,  10,  10,  10,  10,  -25},
                {-20,  10,  25,  25,  10,  -20},
                {-20,  10,  25,  25,  10,  -20},
                {-25,  10,  10,  10,  10,  -25},
                {-80, -25, -20, -20, -25, -80}
        };
        return pieceSquareTable;
    }

    public static int getPieceSquareTableCost(Board board, int color)
    {
        int cost = 0;
        int n = board.getN();
        int[][] pieceSquareTable = new int[n][n];
        if(n == 8) pieceSquareTable = getPieceSquareTable_8by8();
        else if(n == 6) pieceSquareTable = getPieceSquareTable_6by6();

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Checker ch = board.getChecker(i, j);
                if(ch.getColor() == color)
                {
                    cost = cost + pieceSquareTable[i][j];
                }
            }
        }

        return cost;
    }

    public static int getAreaCost(Board board, int color)
    {
        int cost = 0;
        Game g = new Game();
        ArrayList<Checker> activeCheckerList = g.getActiveCheckerList(board, color);

        ArrayList<Integer> rowList = new ArrayList<Integer>();
        ArrayList<Integer> colmList = new ArrayList<Integer>();

        for(int i=0; i<activeCheckerList.size(); i++)
        {
            rowList.add(activeCheckerList.get(i).getX_position());
            colmList.add(activeCheckerList.get(i).getY_position());
        }

        int max_row = Collections.max(rowList);
        int min_row = Collections.min(rowList);

        int row_dist = max_row - min_row + 1;

        int max_col = Collections.max(colmList);
        int min_col = Collections.min(colmList);

        int col_dist = max_col - min_col + 1;

        cost = row_dist * col_dist;

        return cost;
    }

    public static int getQuadCost(Board board, int color)
    {
        int score = 0;
        int n = board.getN();

        for(int i=0; i<n-1; i++)
        {
            for(int j=0; j<n-1; j++)
            {
                int count = 0;
                if(board.getChecker(i, j).getColor() == color) count++;
                if(board.getChecker(i+1, j).getColor() == color) count++;
                if(board.getChecker(i, j+1).getColor() == color) count++;
                if(board.getChecker(i+1, j+1).getColor() == color) count++;

                if(count == 3 || count == 4) score++;
            }
        }

        return score;
    }

    public static int getMobilityCost(Board board, int color)
    {
        int score = 0;

        Game g = new Game();
        ArrayList<Checker> activeCheckerList = g.moves(board, color);

        for(int i=0; i<activeCheckerList.size(); i++)
        {
            score = score + activeCheckerList.get(i).getMoveList().size();
        }

        return score;
    }

    public static int getConnectedCost(Board board, int color)
    {
        int cost = 0;
        int n = board.getN();
        Game g = new Game();
        ArrayList<Checker> activeCheckerList = g.getActiveCheckerList(board, color);

        for(int i=0; i<activeCheckerList.size(); i++)
        {
            int count = 0;
            int x = activeCheckerList.get(i).getX_position();
            int y = activeCheckerList.get(i).getY_position();

            if(x > 0 && y > 0)
            {
                if(board.getChecker(x-1, y-1).getColor() == color) count++;
            }

            if(x > 0)
            {
                if(board.getChecker(x-1, y).getColor() == color) count++;
            }

            if(x > 0 && y < n-1)
            {
                if(board.getChecker(x-1, y+1).getColor() == color) count++;
            }

            if(y > 0)
            {
                if(board.getChecker(x, y-1).getColor() == color) count++;
            }

            if(y < n-1)
            {
                if(board.getChecker(x, y+1).getColor() == color) count++;
            }

            if(x < n-1 && y > 0)
            {
                if(board.getChecker(x+1, y-1).getColor() == color) count++;
            }

            if(x < n-1)
            {
                if(board.getChecker(x+1, y).getColor() == color) count++;
            }

            if(x < n-1 && y < n-1)
            {
                if(board.getChecker(x+1, y+1).getColor() == color) count++;
            }

            cost = cost + count;
        }

        return cost;
    }

    public static int getDensityCost(Board board, int color)
    {
        int n = board.getN();
        Game g = new Game();
        ArrayList<Checker> activeCheckerList = g.getActiveCheckerList(board, color);
        int num_of_checkers = activeCheckerList.size();

        int row_sum = 0;
        int col_sum = 0;

        for(int i=0; i<activeCheckerList.size(); i++)
        {
            int x = activeCheckerList.get(i).getX_position();
            int y = activeCheckerList.get(i).getY_position();

            row_sum = row_sum + x;
            col_sum = col_sum + y;
        }

        double temp_center_x = (row_sum * 1.0) / num_of_checkers;
        double temp_center_y = (col_sum * 1.0) / num_of_checkers;

        int center_x = (int) Math.round(temp_center_x);
        int center_y = (int) Math.round(temp_center_y);

        int dist_sum = 0;

        for(int i=0; i<activeCheckerList.size(); i++)
        {
            int x = activeCheckerList.get(i).getX_position();
            int y = activeCheckerList.get(i).getY_position();
            int diff_x = Math.abs(center_x - x);
            int diff_y = Math.abs(center_y - y);

            int dist = Math.max(diff_x, diff_y);

            dist_sum = dist_sum + dist;
        }

        return dist_sum;
    }

    public static int getHeuristicCost(Board board)
    {
        int cost = 0;

        int pieceSquareTableCost_b = getPieceSquareTableCost(board, Constants.BLACK);

        int pieceSquareTableCost_w = getPieceSquareTableCost(board, Constants.WHITE);

        int pieceSquareTableCost_diff = pieceSquareTableCost_b - pieceSquareTableCost_w;


        int mobilityCost_b = getMobilityCost(board, Constants.BLACK);

        int mobilityCost_w = getMobilityCost(board, Constants.WHITE);

        int mobilityCost_diff = mobilityCost_b - mobilityCost_w;


        int areaCost_b = getAreaCost(board, Constants.BLACK);

        int areaCost_w = getAreaCost(board, Constants.WHITE);

        int areaCost_diff = areaCost_b - areaCost_w;


        int quadCost_b = getQuadCost(board, Constants.BLACK);

        int quadCost_w = getQuadCost(board, Constants.WHITE);

        int quadCost_diff = quadCost_b - quadCost_w;


        int connectedCost_b = getConnectedCost(board, Constants.BLACK);

        int connectedCost_w = getConnectedCost(board, Constants.WHITE);

        int connectedCost_diff = connectedCost_b - connectedCost_w;

        int densityCost_b = getDensityCost(board, Constants.BLACK);

        int densityCost_w = getDensityCost(board, Constants.WHITE);

        int densityCost_diff = densityCost_b - densityCost_w;

        cost = pieceSquareTableCost_diff + mobilityCost_diff - areaCost_diff - densityCost_diff + quadCost_diff + connectedCost_diff;

        return cost;
    }
}
