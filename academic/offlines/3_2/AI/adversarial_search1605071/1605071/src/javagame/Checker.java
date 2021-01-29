package javagame;
import java.util.ArrayList;
import java.util.Map;

public class Checker {
    //color, position, neighbourlist
    private int checkerId;
    private int color;
    private  int x_position;
    private int y_position;
    private ArrayList<Co_ordinates> moveList;

    public Checker() {
        checkerId = -1;
        x_position = -1;
        y_position = -1;
        moveList = new ArrayList<Co_ordinates>();
    }

    public Checker(int color) {
        this.color = color;
    }

    public int getCheckerId() {
        return checkerId;
    }

    public void setCheckerId(int checkerId) {
        this.checkerId = checkerId;
    }

    public int getColor() {
        return color;
    }

    public void setColor(int color) {
        this.color = color;
    }

    public int getX_position() {
        return x_position;
    }

    public void setX_position(int x_position) {
        this.x_position = x_position;
    }

    public int getY_position() {
        return y_position;
    }

    public void setY_position(int y_position) {
        this.y_position = y_position;
    }

    public ArrayList<Co_ordinates> getMoveList() {
        return moveList;
    }

    public void addToMoveList(Co_ordinates co)
    {
        this.moveList.add(co);
    }

    public void clearMoveList()
    {
        this.moveList.clear();
    }

    public void printCheckerCoOrdinates()
    {
        System.out.print("(" + x_position + "," + y_position + ")" + "\t");
    }

    public boolean isEqualCoOrdinates(int diff_x, int diff_y)
    {
        if(x_position == diff_x && y_position == diff_y)
        {
            return true;
        }
        return false;
    }

    public double getDistance(Checker diff_ch)
    {
        int diff_x = diff_ch.getX_position();
        int diff_y = diff_ch.getY_position();
        double dist = -1;

        double x_dist = Math.abs(x_position - diff_x);
        double y_dist = Math.abs(y_position - diff_y);

        dist = Math.sqrt((x_dist*x_dist) + (y_dist*y_dist));
        //System.out.println(dist);

        return dist;
    }
}
