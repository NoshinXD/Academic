package javagame;
import java.util.ArrayList;

public class moves8 {
    public static boolean upMove(Board board, int step, int x, int y, int color, int oppositeColor)
    {
        //boolean canMove = false;
        if(x-0 < step)
        {
            return false;
        }

        if(board.getChecker(x-step, y).getColor() == color)
        {
            return false;
        }

        int temp_x = x;

        for(int i=0; i<step-1; i++)
        {
            temp_x--;
            Checker ch = board.getChecker(temp_x, y);
            if(ch.getColor() == oppositeColor)
            {
                return false;
            }
        }

        return true;
    }

    public static boolean downMove(Board board, int step, int x, int y, int color, int oppositeColor)
    {
        int n = board.getN();

        if((n-1)-x < step)
        {
            return false;
        }
        if(board.getChecker(x+step, y).getColor() == color)
        {
            return false;
        }

        int temp_x = x;

        for(int i=0; i<step-1; i++)
        {
            temp_x++;
            Checker ch = board.getChecker(temp_x, y);
            if(ch.getColor() == oppositeColor)
            {
                return false;
            }
        }

        return true;
    }

    public static boolean leftMove(Board board, int step, int x, int y, int color, int oppositeColor)
    {
        if(y-0 < step)
        {
            return false;
        }
        if(board.getChecker(x, y-step).getColor() == color)
        {
            return false;
        }

        int temp_y = y;

        for(int i=0; i<step-1; i++)
        {
            temp_y--;
            Checker ch = board.getChecker(x, temp_y);
            if(ch.getColor() == oppositeColor)
            {
                return false;
            }
        }

        return true;
    }

    public static boolean rightMove(Board board, int step, int x, int y, int color, int oppositeColor)
    {
        int n = board.getN();

        if((n-1)-y < step)
        {
            return false;
        }
        if(board.getChecker(x, y+step).getColor() == color)
        {
            return false;
        }

        int temp_y = y;
        for(int i=0; i<step-1; i++)
        {
            temp_y++;
            Checker ch = board.getChecker(x, temp_y);
            if(ch.getColor() == oppositeColor)
            {
                return false;
            }
        }
        return true;
    }

    public static boolean upperLeftMove(Board board, int step, int x, int y, int color, int oppositeColor)
    {
        if(x-step < 0 || y-step < 0)
        {
            return false;
        }

        if(board.getChecker(x-step, y-step).getColor() == color)
        {
            return false;
        }

        int temp_x = x;
        int temp_y = y;

        for(int i=0; i<step-1; i++)
        {
            temp_x--;
            temp_y--;

            Checker ch = board.getChecker(temp_x, temp_y);
            if(ch.getColor() == oppositeColor)
            {
                return false;
            }
        }

        return true;
    }

    public static boolean lowerRightMove(Board board, int step, int x, int y, int color, int oppositeColor)
    {
        int n = board.getN();
        if(x+step > n-1 || y+step > n-1)
        {
            return false;
        }

        if(board.getChecker(x+step, y+step).getColor() == color)
        {
            return false;
        }

        int temp_x = x;
        int temp_y = y;
        for(int i=0; i<step-1; i++){
            temp_x++;
            temp_y++;

            Checker ch = board.getChecker(temp_x, temp_y);
            if(ch.getColor() == oppositeColor)
            {
                return false;
            }
        }

        return true;
    }

    public static boolean upperRightMove(Board board, int step, int x, int y, int color, int oppositeColor)
    {
        int n = board.getN();
        if(x-step < 0 || y+step > n-1)
        {
            return false;
        }
        if(board.getChecker(x-step, y+step).getColor() == color)
        {
            return false;
        }

        int temp_x = x;
        int temp_y = y;

        for(int i=0; i<step-1; i++)
        {
            temp_x--;
            temp_y++;

            Checker ch = board.getChecker(temp_x, temp_y);
            if(ch.getColor() == oppositeColor)
            {
                return false;
            }
        }

        return true;
    }

    public static boolean lowerLeftMove(Board board, int step, int x, int y, int color, int oppositeColor)
    {
        int n = board.getN();
        if(x+step > n-1 || y-step < 0)
        {
            return false;
        }

        if(board.getChecker(x+step, y-step).getColor() == color)
        {
            return false;
        }

        int temp_x = x;
        int temp_y = y;
        for(int i=0; i<step-1; i++)
        {
            temp_x++;
            temp_y--;

            Checker ch = board.getChecker(temp_x, temp_y);
            if(ch.getColor() == oppositeColor)
            {
                return false;
            }
        }

        return true;
    }
}
