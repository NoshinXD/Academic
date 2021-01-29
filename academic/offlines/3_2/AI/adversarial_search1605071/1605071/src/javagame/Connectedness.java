package javagame;
import java.util.ArrayList;
import java.util.LinkedList;

public class Connectedness {
    public static int getConnectedCost(Board board, int color)
    {
        Game g = new Game();
        ArrayList<Checker> activeCheckerList = g.getActiveCheckerList(board, color);

        int V = activeCheckerList.size();
        int s = 0;

        boolean visited[] = new boolean[V];
        boolean inTree[] = new boolean[V];

        Boolean allInTree = true;
        int treeCount  = 0;
        while(true)
        {
            treeCount++;

            LinkedList<Checker> queue = new LinkedList<Checker>();
            ArrayList<Checker> connectedList = new ArrayList<Checker>();

            visited[s] = true;
            inTree[s] = true;
            queue.add(activeCheckerList.get(s));
            Checker ch, diff_ch;

            while (queue.size() != 0)
            {
                ch = queue.poll();
                connectedList.add(ch);

                for(int i=0; i<activeCheckerList.size(); i++)
                {
                    int ch_index = activeCheckerList.indexOf(ch);
                    diff_ch = activeCheckerList.get(i);

                    double dist = ch.getDistance(diff_ch);

                    if(i != ch_index && dist < 2)
                    {
                        int n = activeCheckerList.indexOf(diff_ch);

                        if(!visited[n])
                        {
                            visited[n] = true;
                            inTree[n] = true;
                            queue.add(diff_ch);
                        }
                    }
                }
            }

            for(int i=0; i<inTree.length; i++)
            {
                if(inTree[i] == false)
                {
                    s = i;
                    allInTree = false;
                }
            }
            if(allInTree == true)
            {
                break;
            }
        }

        return treeCount;
    }
}
