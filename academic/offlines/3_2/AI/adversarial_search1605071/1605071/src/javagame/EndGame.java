package javagame;
import java.util.ArrayList;
import java.util.LinkedList;

public class EndGame {
    //working with this one
    public static boolean isConnected(ArrayList<Checker> activeCheckerList)
    {
        int V = activeCheckerList.size();
        int s = 0;

        boolean visited[] = new boolean[V];
        LinkedList<Checker> queue = new LinkedList<Checker>();
        ArrayList<Checker> connectedList = new ArrayList<Checker>();

        visited[s] = true;
        queue.add(activeCheckerList.get(s));
        Checker ch, diff_ch;
        while(queue.size() != 0)
        {
            ch = queue.poll();
            //ch.printCheckerCoOrdinates();
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
                        queue.add(diff_ch);
                    }
                }
            }

        }

        int color = activeCheckerList.get(0).getColor();


        if(activeCheckerList.size() == connectedList.size())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
