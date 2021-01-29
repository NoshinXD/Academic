import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;

public class Move_matrix {
    public static final int UP = 1;
    public static final int DOWN = 3;
    public static final int LEFT = 0;
    public static final int RIGHT = 2;
    //ArrayList<int[][]> stateList = new ArrayList<int[][]>();
    //ArrayList<int[][]> pathList = new ArrayList<int[][]>();

    /*int[][] old_matrix = new int[4][4];
    int[][] temp_matrix = new int[4][4];
    int[][] goal_matrix = new int[4][4];*/

    /*int[][] up_matrix = new int[4][4];
    int[][] down_matrix = new int[4][4];
    int[][] left_matrix = new int[4][4];
    int[][] right_matrix = new int[4][4];*/

    //int blanki = 0, blankj = 0;

    //boolean isCng = false;

    //int up = -1, down = -2, left = -3, right = -4;
    //int win = 0;

    //int level = 1;

    /*public void send_matrix(int[][] init_matrix, int[][] final_matrix)
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                old_matrix[i][j]=init_matrix[i][j];
                temp_matrix[i][j] = init_matrix[i][j];
                goal_matrix[i][j]=final_matrix[i][j];

                /*if(init_matrix[i][j] == 0)
                {
                    blanki = i;
                    blankj = j;
                }
            }
        }
        pathList.add(init_matrix);
    }*/

    public static Matrix fromUp(Matrix temp_matrix)
    {
        int blanki = temp_matrix.getBlankX();
        int blankj = temp_matrix.getBlankY();
        int[][] up_matrix = new int[4][4];

        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                up_matrix[i][j]=temp_matrix.get(i, j);
            }
        }

        up_matrix[blanki][blankj] = temp_matrix.get(blanki-1, blankj);
        up_matrix[blanki-1][blankj] = 0;

        //stateList.add(up_matrix);

        Matrix up_mat = new Matrix(up_matrix);
        up_mat.setType(1);

        //return new Matrix(up_matrix);
        return up_mat;
    }

    public static Matrix fromDown(Matrix temp_matrix)
    {
        int blanki = temp_matrix.getBlankX();
        int blankj = temp_matrix.getBlankY();
        int[][] down_matrix = new int[4][4];

        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                down_matrix[i][j]=temp_matrix.get(i, j);
            }
        }

        down_matrix[blanki][blankj] = temp_matrix.get(blanki+1,blankj);
        down_matrix[blanki+1][blankj] = 0;

        //stateList.add(down_matrix);
        Matrix down_mat = new Matrix(down_matrix);
        down_mat.setType(3);

        return down_mat;
    }

    public static Matrix fromLeft(Matrix temp_matrix)
    {
        int blanki = temp_matrix.getBlankX();
        int blankj = temp_matrix.getBlankY();
        int[][] left_matrix = new int[4][4];

        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                left_matrix[i][j]=temp_matrix.get(i, j);
            }
        }

        left_matrix[blanki][blankj] = temp_matrix.get(blanki,blankj-1);
        left_matrix[blanki][blankj-1] = 0;

        //stateList.add(left_matrix);
        Matrix left_mat = new Matrix(left_matrix);
        left_mat.setType(0);

        return left_mat;
    }

    public static Matrix fromRight(Matrix temp_matrix)
    {
        int blanki = temp_matrix.getBlankX();
        int blankj = temp_matrix.getBlankY();
        int[][] right_matrix = new int[4][4];

        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                right_matrix[i][j]=temp_matrix.get(i, j);
            }
        }

        right_matrix[blanki][blankj] = temp_matrix.get(blanki,blankj+1);
        right_matrix[blanki][blankj+1] = 0;

        //stateList.add(right_matrix);
        Matrix right_mat = new Matrix(right_matrix);
        right_mat.setType(2);

        return right_mat;
    }
}
