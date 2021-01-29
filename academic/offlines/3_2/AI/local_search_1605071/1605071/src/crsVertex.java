import java.util.ArrayList;

public class crsVertex implements Comparable<crsVertex> {
    private int u, color, degeree, sat_point;
    private boolean marker;
    private ArrayList<crsVertex> adj;
    private ArrayList<Integer> adjColor;

    public crsVertex(int u) {
        this.u = u;
        this.color = -1;
        this.degeree = 0;
        this.sat_point = 0;

        adj = new ArrayList<crsVertex>();
        adjColor = new ArrayList<Integer>();
    }

    public int getU() {
        return u;
    }

    public void setU(int u) {
        this.u = u;
    }

    public int getColor() {
        return color;
    }

    public void setColor(int color) {
        this.color = color;
    }

    public int getDegeree() {
        return degeree;
    }

    public void setDegeree(int degeree) {
        this.degeree = degeree;
    }

    public int getSat_point() {
        return sat_point;
    }

    public void setSat_point(int sat_point) {
        this.sat_point = sat_point;
    }

    public boolean isMarker() {
        return marker;
    }

    public void setMarker(boolean marker) {
        this.marker = marker;
    }

    public ArrayList<crsVertex> getAdj() {
        //System.out.println("here");
        //System.out.println(adj.size());
        /*for(int i=0; i<adj.size(); i++)
        {
            //System.out.println("here");
            System.out.println(adj.get(i).u);
        }*/
        return adj;
    }

    public void setAdj(ArrayList<crsVertex> adj) {
        for(int i=0; i<adj.size(); i++) {
            this.adj.add(adj.get(i));
        }
    }

    public void addAdj(crsVertex adjCrs) {
        //System.out.println("ashche");
        adj.add(adjCrs);
    }

    public ArrayList<Integer> getAdjColor() {
        return adjColor;
    }

    public void addAdjColor(int clr) {
        adjColor.add(clr);
    }

    @Override
    public int compareTo(crsVertex o) {
        return this.degeree - o.degeree;
    }
}
