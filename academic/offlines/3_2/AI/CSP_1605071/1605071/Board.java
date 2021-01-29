import java.util.ArrayList;

public class Board {
    private Variable[][] board;
    private int n;

    public Board(int n) {
        this.n = n;

        board = new Variable[n][n];
    }

    public int getN() {
        return n;
    }

    public Variable[][] getBoard() {
        return board;
    }

    public void setVariable(int val, int i, int j)
    {
        Variable var = new Variable(val, i, j, n);
        board[i][j] = var;
    }

    public Variable getVariable(int i, int j)
    {
        return board[i][j];
    }

    public void copyBoard(Board diff_board)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                int value = diff_board.getVariable(i, j).getValue();
                setVariable(value, i, j);
            }
        }
    }

    public void printBoard()
    {
        System.out.println("Board: ");
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                System.out.print(board[i][j].getValue() + "\t");
            }
            System.out.println();
        }
    }
}
