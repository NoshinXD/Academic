package javagame;
public class Board {
    //2D matrix
    private Checker[][] checker_board;
    private int n;
    private int id;

    public Board(int n) {
        id = 0;
        setN(n);
        checker_board = new Checker[n][n];
    }

    public void initiateBoard() {

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Checker ch = new Checker();
                if(i == 0 || i == n-1)
                {
                    if(j != 0 && j != n-1)
                    {
                        id++;
                        ch.setCheckerId(id);
                        ch.setColor(Constants.BLACK);
                    }
                    else
                    {
                        ch.setColor(-1);
                    }
                }
                else if(j == 0 || j == n-1)
                {
                    if(i != 0 && i != n-1)
                    {
                        id++;
                        ch.setCheckerId(id);
                        ch.setColor(Constants.WHITE);
                    }
                    else
                    {
                        ch.setColor(-1);
                    }
                }
                else
                {
                    ch.setColor(-1);
                }
                ch.setX_position(i);
                ch.setY_position(j);
                setChecker(ch, i, j);
            }
        }
    }

    public void blankBoard()
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Checker ch = new Checker();
                ch.setColor(-1);
                setChecker(ch, i, j);
            }
        }
    }

    public void copyBoard(Board diff_board)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Checker ch = new Checker();
                Checker diff_ch = diff_board.getChecker(i, j);
                ch.setColor(diff_ch.getColor());
                ch.setX_position(i);
                ch.setY_position(j);
                setChecker(ch, i, j);
            }
        }
    }

    public int getN() {
        return n;
    }

    public void setN(int n) {
        this.n = n;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Checker[][] getChecker_board() {
        return checker_board;
    }

    public void setChecker_board(Checker[][] checker_board) {
        this.checker_board = checker_board;
    }

    public void setChecker(Checker ch, int x, int y)
    {
        checker_board[x][y] = ch;
        ch.setX_position(x);
        ch.setY_position(y);
    }

    public Checker getChecker(int x, int y)
    {
        return checker_board[x][y];
    }

    public void printBoard() {
        System.out.print("  |" + "\t");
        for(int i=0; i<n; i++)
        {
            System.out.print(i + "\t");
        }
        System.out.println();
        System.out.println("-------------------------------------");
        for(int i=0; i<n; i++)
        {
            System.out.print(i + " |" + "\t");
            for(int j=0; j<n; j++)
            {
                System.out.print(checker_board[i][j].getColor() + "\t");
                //System.out.print(checker_board[i][j].getCheckerId() + "\t");
                //System.out.print("(" + checker_board[i][j].getX_position() + "," + checker_board[i][j].getY_position() + ")" + "\t");
            }
            System.out.println();
        }
        System.out.println("-------------------------------------");
        System.out.println();
    }

    public void printBoardwithStr()
    {
        String str = "\n      |     ";
        for(int j = 0; j < n; j++)
        {
            str += j + "          ";
        }
        str += "\n";

        for(int j = 0; j < n; j++)
        {
            str += "------------";
        }
        str += "\n";
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(j == 0) {
                    str += i + "     |     ";
                }
                if(checker_board[i][j].getColor() == Constants.BLACK)
                {
                    str += "black" + "      ";
                }
                else if(checker_board[i][j].getColor() == Constants.WHITE)
                {
                    str += "white" + "      ";
                }
                else
                {
                    str += "#####" + "      ";
                }
            }
            str += "\n";
        }
        System.out.println(str);
    }
}
