import java.util.ArrayList;

public class Variable {
    private int value;
    private int row;
    private int col;
    private int degree;
    private ArrayList<Integer> domain;

    /*public Variable(int n) {
        this.value = -1;
        this.row = -1;
        this.col = -1;
        this.degree = 0;

        domain = new ArrayList<Integer>();
        for(int i=0; i<n; i++)
        {
            domain.add(i+1);
        }
    }*/

    public Variable(int value, int row, int col, int n) {
        this.value = value;
        this.row = row;
        this.col = col;
        this.degree = 0;

        /*domain = new ArrayList<Boolean>();
        for(int i=0; i<n; i++)
        {
            domain.add(true);
        }*/
        domain = new ArrayList<Integer>();
        /*for(int i=0; i<n; i++)
        {
            domain.add(i+1);
        }*/
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public int getRow() {
        return row;
    }

    public void setRow(int row) {
        this.row = row;
    }

    public int getCol() {
        return col;
    }

    public void setCol(int col) {
        this.col = col;
    }

    public int getDegree() {
        return degree;
    }

    public void setDegree(int degree) {
        this.degree = degree;
    }

    public ArrayList<Integer> getDomain() {
        return domain;
    }

    public void addDomain(ArrayList<Integer> diff_domain)
    {
        this.domain.clear();
        for(int i=0; i<diff_domain.size(); i++)
        {
            this.domain.add(diff_domain.get(i));
        }
    }

    public void removeFromDomain(int i)
    {
        domain.remove(new Integer(i));
    }

    public void printDomain()
    {
        System.out.println("domain: ");
        for(int i=0; i<domain.size(); i++)
        {
            System.out.println(domain.get(i));
        }
    }
}
