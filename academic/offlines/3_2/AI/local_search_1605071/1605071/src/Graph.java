import java.util.ArrayList;

public class Graph {
    void addEdge(crsVertex u, crsVertex v)
    {
        //System.out.println("ashche");
        u.addAdj(v);
        v.addAdj(u);

        int u_deg = u.getDegeree() + 1;
        u.setDegeree(u_deg);

        int v_deg = v.getDegeree() + 1;
        v.setDegeree(v_deg);
    }

    boolean isEdge(crsVertex u, crsVertex v)
    {
        ArrayList<crsVertex> adj = u.getAdj();

        for(int i=0; i<adj.size(); i++)
        {
            if(adj.get(i).getU() == v.getU())
            {
                return true;
            }
        }
        return false;
    }
}
