package javagame;

import org.lwjgl.input.Mouse;
import org.newdawn.slick.*;
import org.newdawn.slick.Color;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.state.*;

import java.util.ArrayList;

public class Play extends BasicGameState {
    String mouse = "no input yet!\n";
    String check = "initial state\n";
    int n = 0;
    int max_y = -1;
    int min_y = -1;

    Game myGame;
    Boolean black;
    public Board board;
    ArrayList<Checker> activeCheckerList_b;
    ArrayList<Checker> activeCheckerList_w;

    public int fromIndex_X = Integer.MIN_VALUE;
    public int fromIndex_Y = Integer.MIN_VALUE;
    public int toIndex_X = Integer.MIN_VALUE;
    public int toIndex_Y = Integer.MIN_VALUE;

    public boolean showLegalMoves = false, endGame = false;

    public int turn = 0;
    String win = "...";
    boolean black_win = false;
    boolean white_win = false;

    public Play(int state, int n) {
        this.n = n;
    }

    public void init(GameContainer gc, StateBasedGame sbg) throws SlickException {
        board = new Board(n);
        board.initiateBoard();

        myGame = new Game();

        black = true;
        max_y = 470;

        if(n == 8) min_y = 70;
        else if(n == 6) min_y = 170;
    }

    public void show_x_y(Graphics g)
    {
        int x = 70;
        int y = 23;

        for(int i=0; i<n; i++)
        {
            g.setColor(Color.white);
            g.drawString(Integer.toString(i), x, y);
            x = x + 50;
        }
        x = 23;
        y = 70;

        for(int i=0; i<n; i++)
        {
            g.setColor(Color.white);
            g.drawString(Integer.toString(i), x, y);
            y = y + 50;
        }
    }

    public void show_board(Graphics g)
    {
        show_x_y(g);

        int x = -1, y = -1;
        int w=50, h=50;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                g.setColor(Color.white);
                x = 50 * (j + 1);
                y = 50 * (i + 1);
                g.drawRect(x, y, 50, 50);
                String temp = "(" + Integer.toString(i) + "," + Integer.toString(j) + ")";
                g.setColor(Color.lightGray);
                g.drawString(temp, x + 2, y + 15);
            }
        }
        //show_checkers(g);
    }

    public void show_checkers(Graphics g)
    {
        int x = -1, y = -1;
        int w=50, h=50;
        activeCheckerList_b = myGame.getActiveCheckerList(board, Constants.BLACK);
        activeCheckerList_w = myGame.getActiveCheckerList(board, Constants.WHITE);

        w=50;
        h=50;

        for(int i=0; i<activeCheckerList_b.size(); i++)
        {
            g.setColor(Color.gray);
            //g.setColor(Color.darkGray);
            Checker ch = activeCheckerList_b.get(i);
            int checker_x = ch.getX_position();
            int checker_y = ch.getY_position();
            x = 50 * (checker_y + 1);
            y = 50 * (checker_x + 1);
            g.fillOval(x, y, w, h);
        }

        w=50;
        h=50;
        for(int i=0; i<activeCheckerList_w.size(); i++)
        {
            g.setColor(Color.white);
            //g.setColor(Color.lightGray);
            Checker ch = activeCheckerList_w.get(i);
            int checker_x = ch.getX_position();
            int checker_y = ch.getY_position();
            x = 50 * (checker_y + 1);
            y = 50 * (checker_x + 1);
            g.fillOval(x, y, w, h);
        }
    }

    public int getX_coord(int mouse_y)
    {
        int x_coord = n - 1 - ((mouse_y-min_y)/50);;
        return x_coord;
    }

    public int getY_coord(int mouse_x)
    {
        int y_coord = (mouse_x/50) - 1;;
        return y_coord;
    }

    public boolean validChecker(int color, int from_x, int from_y)
    {
        ArrayList<Checker> activecheckerList = myGame.getActiveCheckerList(board, color);
        for(int i=0; i<activecheckerList.size(); i++)
        {
            Checker ch = activecheckerList.get(i);
            int x = ch.getX_position();
            int y = ch.getY_position();

            if(x == from_x && y == from_y)
            {
                return true;
            }
        }

        return false;
    }

    public boolean validMove(Checker ch, int to_x, int to_y)
    {
        ArrayList<Co_ordinates> moveList = ch.getMoveList();
        for(int i=0; i<moveList.size(); i++)
        {
            int x = moveList.get(i).getX();
            int y = moveList.get(i).getY();

            if(x == to_x && y == to_y)
            {
                return true;
            }
        }

        return false;
    }

    public void setShowLegalMoves(Graphics g, Checker ch)
    {
        int from_x, from_y, to_x, to_y;
        from_x = ch.getX_position();
        from_y = ch.getY_position();

        ArrayList<Co_ordinates> moveList = ch.getMoveList();

        for(int i=0; i<moveList.size(); i++)
        {
            to_x = moveList.get(i).getX();
            to_y = moveList.get(i).getY();

            g.setColor(Color.orange);

            int temp_from_x = 50 * (from_y + 1);
            int temp_from_y = 50 * (from_x + 1);
            int temp_to_x = 50 * (to_y + 1);
            int temp_to_y = 50 * (to_x + 1);

            g.drawLine(temp_from_x + 25, temp_from_y + 25, temp_to_x + 25, temp_to_y + 25);
        }
    }

    public void render(GameContainer gc, StateBasedGame sbg, Graphics g) throws SlickException {
        g.drawString(mouse, 55, 2);

        //myGame = new Game();
        show_board(g);
        show_checkers(g);

        int color = turn;

        myGame.moves(board, color);

        if(showLegalMoves) {
            Checker ch = board.getChecker(fromIndex_X, fromIndex_Y);

            //show_moves(color, gc, g);

            setShowLegalMoves(g, ch);

            boolean tempIsValidChecker = validChecker(color, fromIndex_X, fromIndex_Y);
            if(tempIsValidChecker)
            {
                //noMove = true;
                if(ch.getMoveList().size() == 0)
                {
                    g.setColor(Color.red);
                    g.drawString("No legal Move!", 200, 470);
                }
            }

            if(toIndex_X != Integer.MIN_VALUE && toIndex_Y != Integer.MIN_VALUE)
            {
                boolean isValidChecker = validChecker(color, fromIndex_X, fromIndex_Y);
                boolean isValidMove = validMove(ch, toIndex_X, toIndex_Y);

                //System.out.println("isValidChecker: " + isValidChecker);
                //System.out.println("isValidMove: " + isValidMove);

                if(isValidChecker && isValidMove)
                {
                    board.getChecker(fromIndex_X, fromIndex_Y).setColor(-1);
                    board.getChecker(toIndex_X, toIndex_Y).setColor(color);

                    ArrayList<Checker> newActiveCheckerList = myGame.getActiveCheckerList(board, color);

                    show_checkers(g);

                    boolean isConnected = EndGame.isConnected(newActiveCheckerList);

                    if(isConnected)
                    {
                        if(color == 0)
                        {
                            String win = "BLACK has won!";
                            black_win = true;
                            System.out.println(win);
                        }
                        else
                        {
                            String win = "WHITE has won!";
                            white_win = true;
                            System.out.println(win);
                        }
                        endGame = true;
                    }

                    ArrayList<Checker> newOppositeActiveCheckerList = myGame.getActiveCheckerList(board, 1-color);

                    boolean isOppositeConnected = EndGame.isConnected(newOppositeActiveCheckerList);

                    if(endGame == false && isOppositeConnected)
                    {
                        if(1-color == 1)
                        {
                            String win = "WHITE has won!";
                            white_win = true;
                            System.out.println(win);
                        }
                        else
                        {
                            String win = "BLACK has won!";
                            black_win = true;
                            System.out.println(win);
                        }
                        endGame = true;
                    }
                    turn = 1 - turn;
                }
                toIndex_X = Integer.MIN_VALUE;
                toIndex_Y = Integer.MIN_VALUE;
                showLegalMoves = false;
            }
        }
        g.setColor(Color.red);
        g.drawString(win, 200, 500);
    }

    public void update(GameContainer gc, StateBasedGame sbg, int delta) throws SlickException {

        Input input = gc.getInput();
        int xpos = Mouse.getX();
        int ypos = Mouse.getY();

        if(input.isMouseButtonDown(0))
        {
            if(!endGame)
            {
                //System.out.println("showLegalMoves: " + showLegalMoves);
                if(showLegalMoves)
                {
                    if(toIndex_X == Integer.MIN_VALUE && toIndex_Y == Integer.MIN_VALUE)
                    {
                        toIndex_X = getX_coord(ypos);
                        toIndex_Y = getY_coord(xpos);

                        //System.out.println("toIndex_X: " + toIndex_X);
                        //System.out.println("toIndex_Y: " + toIndex_Y);

                        mouse = "Position: " + xpos + ", " + ypos + " => index: (" + toIndex_X + ", " + toIndex_Y + ")";
                    }
                }
                if(toIndex_X == Integer.MIN_VALUE && toIndex_Y == Integer.MIN_VALUE)
                {
                    fromIndex_X = getX_coord(ypos);
                    fromIndex_Y = getY_coord(xpos);
                    showLegalMoves = true;

                    //System.out.println("fromIndex_X: " + fromIndex_X);
                    //System.out.println("fromIndex_Y: " + fromIndex_Y);

                    mouse = "Position: " + xpos + ", " + ypos + " => index: (" + fromIndex_X + ", " + fromIndex_Y + ")";
                }
            }
        }

        if(endGame)
        {
            if(black_win) win = "BLACK has won!";
            if(white_win) win = "WHITE has won!";
        }
    }

    public int getID() {
        return 1;
    }
}
