import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class graphColoring {
    //ArrayList<Integer> setColor(ArrayList<crsVertex> crsList) {
    int setColor(ArrayList<crsVertex> crsList) {
        ArrayList<Integer> colorList = new ArrayList<Integer>();
        ArrayList<Boolean> availColor = new ArrayList<Boolean>();

        Queue<crsVertex> q = new LinkedList<>();

        for(int i=0; i<crsList.size(); i++)
        {
            q.add(crsList.get(i));
            colorList.add(0);
            availColor.add(Boolean.TRUE);
        }

        colorList.set(0, colorList.get(0) + 1);
        q.element().setColor(0);
        q.remove();

        int i=0;
        while(!q.isEmpty())
        {
            crsVertex head = q.element();
            ArrayList<crsVertex> adj = head.getAdj();

            /*if(i==3)
            {
                System.out.println(head.getU());
                System.out.println();
                for(int j=0; j<adj.size(); j++)
                {
                    System.out.println(adj.get(j).getU());
                }
                System.out.println();
                //System.out.println(colorList.size());
                //System.out.println(availColor.size());
                //System.out.println();
            }*/

            for(int j=0; j<adj.size(); j++)
            {
                /*if(i==3)
                {
                    if(adj.get(j).getColor() != -1)
                    {
                        System.out.println(adj.get(j).getU());
                    }
                }*/

                if(adj.get(j).getColor() != -1)
                {
                    availColor.set(adj.get(j).getColor(), Boolean.FALSE);
                }
            }
            //System.out.println();

            for(int j=0; j<availColor.size(); j++)
            {
                if(availColor.get(j).equals(true))
                {
                    colorList.set(j, colorList.get(j)+1);
                    q.element().setColor(j);
                    break;
                }
            }

            /*if(i==3)
            {
                //System.out.println(availColor.size());
                for(int j=0; j<availColor.size(); j++)
                {
                    System.out.println(availColor.get(j));
                }
                System.out.println();

                //System.out.println(colorList.size());
                for(int j=0; j<colorList.size(); j++)
                {
                    System.out.println(colorList.get(j));
                }
                System.out.println();
            }*/

            q.remove();

            int listlen = availColor.size();
            availColor.clear();
            for(int j=0; j<listlen; j++)
            {
                availColor.add(Boolean.TRUE);
            }

            i++;
        }

        int count = 0;
        for(int j=0; j<colorList.size(); j++)
        {
            if(colorList.get(j) != 0)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        //System.out.println("min slot: " + count);

        //return colorList;
        return count;
    }
}
