package javagame;
public class Co_ordinates {
    private int x;
    private int y;

    public Co_ordinates(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public boolean isEqual(int diff_x, int diff_y)
    {
        if(x == diff_x && y == diff_y)
        {
            return true;
        }
        return false;
    }

    public void print()
    {
        System.out.println("(" + x + " , " + y + ")");
    }
}
