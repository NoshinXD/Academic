package javagame;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Game {
    public ArrayList<Checker> getActiveCheckerList(Board board, int color)
    {
        ArrayList<Checker> activeCheckerList = new ArrayList<Checker>();
        int n = board.getN();
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Checker ch = board.getChecker(i, j);
                if(ch.getColor() == color)
                {
                    activeCheckerList.add(ch);
                }
            }
        }
        return activeCheckerList;
    }

    public ArrayList<Checker> moves(Board board, int color)
    {
        int check_x = 4;
        int check_y = 3;
        ArrayList<Checker> activeCheckerList = getActiveCheckerList(board, color);


        int n = board.getN();

        int oppositeColor;

        if(color == Constants.BLACK) oppositeColor = Constants.WHITE;
        else oppositeColor = Constants.BLACK;

        for(int i=0; i<activeCheckerList.size(); i++)
        {
            Checker ch = activeCheckerList.get(i);
            ch.clearMoveList();

            int x = ch.getX_position();
            int y = ch.getY_position();

            int colStep = 0;
            for(int j=0; j<n; j++)
            {
                if(board.getChecker(j, y).getColor() != -1)
                {
                    colStep++;
                }
            }
            //System.out.println("step: " + step);
            //System.out.println("(" + activeCheckerList.get(i).getX_position() + "," + activeCheckerList.get(i).getY_position() + ")");
            boolean canMoveUp = moves8.upMove(board, colStep, x, y, color, oppositeColor);

            if(canMoveUp)
            {
                Co_ordinates co = new Co_ordinates(x-colStep, y);
                ch.addToMoveList(co);
            }

            boolean canMoveDown = moves8.downMove(board, colStep, x, y, color, oppositeColor);

            if(canMoveDown)
            {
                Co_ordinates co = new Co_ordinates(x+colStep, y);
                ch.addToMoveList(co);
            }
            //System.out.println("column step: " + colStep);

            int rowStep = 0;
            for(int j=0; j<n; j++)
            {
                if(board.getChecker(x, j).getColor() != -1)
                {
                    rowStep++;
                }
            }
            //System.out.println("row step: " + rowStep);

            boolean canMoveLeft = moves8.leftMove(board, rowStep, x, y, color, oppositeColor);

            if(canMoveLeft)
            {
                Co_ordinates co = new Co_ordinates(x, y-rowStep);
                ch.addToMoveList(co);
            }

            boolean canMoveRight = moves8.rightMove(board, rowStep, x, y, color, oppositeColor);

            if(canMoveRight)
            {
                Co_ordinates co = new Co_ordinates(x, y+rowStep);
                ch.addToMoveList(co);
            }

            int leftToRightStep = 1;
            int temp_x = x;
            int temp_y = y;
            while(true)
            {
                if(temp_x == 0 || temp_y == 0)
                {
                    break;
                }
                temp_x--;
                temp_y--;
                if(board.getChecker(temp_x, temp_y).getColor() != -1)
                {
                    leftToRightStep++;
                }
            }
            temp_x = x;
            temp_y = y;
            while (true)
            {
                if(temp_x == n-1 || temp_y == n-1)
                {
                    break;
                }
                temp_x++;
                temp_y++;
                if(board.getChecker(temp_x, temp_y).getColor() != -1)
                {
                    leftToRightStep++;
                }
            }

            //System.out.println("left to right step: " + leftToRightStep);

            boolean canMoveUpperLeft = moves8.upperLeftMove(board, leftToRightStep, x, y, color, oppositeColor);
            if(canMoveUpperLeft)
            {
                Co_ordinates co = new Co_ordinates(x-leftToRightStep, y-leftToRightStep);
                ch.addToMoveList(co);
            }

            boolean canMoveLowerRight = moves8.lowerRightMove(board, leftToRightStep, x, y, color, oppositeColor);

            if(canMoveLowerRight)
            {
                Co_ordinates co = new Co_ordinates(x+leftToRightStep, y+leftToRightStep);
                ch.addToMoveList(co);
            }
            
            int rightToLeftStep = 1;
            temp_x = x;
            temp_y = y;

            while(true)
            {
                if(temp_x == 0 || temp_y == n-1)
                {
                    break;
                }
                temp_x--;
                temp_y++;
                
                if(board.getChecker(temp_x, temp_y).getColor() != -1)
                {
                    rightToLeftStep++;
                }
            }

            temp_x = x;
            temp_y = y;
            while (true)
            {
                if(temp_x == n-1 || temp_y == 0)
                {
                    break;
                }
                temp_x++;
                temp_y--;
                
                if(board.getChecker(temp_x, temp_y).getColor() != -1)
                {
                    rightToLeftStep++;
                }
            }
            //System.out.println("right to left step: " + rightToLeftStep);

            boolean canMoveUpperRight = moves8.upperRightMove(board, rightToLeftStep, x, y, color, oppositeColor);
            if(canMoveUpperRight)
            {
                Co_ordinates co = new Co_ordinates(x-rightToLeftStep, y+rightToLeftStep);
                ch.addToMoveList(co);
            }

            boolean canMoveLowerLeft = moves8.lowerLeftMove(board, rightToLeftStep, x, y, color, oppositeColor);
            if(canMoveLowerLeft)
            {
                Co_ordinates co = new Co_ordinates(x+rightToLeftStep, y-rightToLeftStep);
                ch.addToMoveList(co);
            }
        }
        return activeCheckerList;
    }
}
