import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;

public class stochastic_kempe {
    double penalty_init = -1;
    double raw_penalty = -1;
    penalty_count p = new penalty_count();
    int repeat = 0;
    int num_of_iter = 20000; //10000
    int type = 1;

    ArrayList<crsVertex> bfs(crsVertex src, int totalCrs, int color2) //u.getColor() == color1
    {
        int color1 = src.getColor();
        boolean visited[] = new boolean[totalCrs];
        ArrayList<crsVertex> tree = new ArrayList<crsVertex>();

        Queue<crsVertex> q = new LinkedList<>();

        visited[src.getU()-1] = true;
        q.add(src);

        while(!q.isEmpty())
        {
            src = q.element();
            q.remove();

            //System.out.println(src.getU());
            tree.add(src);


            ArrayList<crsVertex> adj = src.getAdj();
            //System.out.print(src.getU() + ": ");

            for(int i=0; i<adj.size(); i++)
            {
                //System.out.print(adj.get(i).getU() + " - ");
                int index = adj.get(i).getU() - 1;
                if(!visited[index])
                {
                    visited[index] = true;
                    if(adj.get(i).getColor() == color1 || adj.get(i).getColor() == color2)
                        q.add(adj.get(i));
                }
            }
            //System.out.println();
        }
        return tree;
    }

    ArrayList<myPair> pair_making(ArrayList<crsVertex> crsList)
    {
        /*for(int i=0; i<crsList.size(); i++)
        {
            System.out.print(crsList.get(i).getU() + " - ");
        }
        System.out.println("--------------");*/

        ArrayList<myPair> pairList = new ArrayList<myPair>();
        Graph g = new Graph();

        for(int i=0; i<crsList.size(); i++)
        {
            for(int j=0; j<crsList.size(); j++)
            {
                if(i != j)
                {
                    if(crsList.get(i).getColor() != crsList.get(j).getColor())
                    //if(g.isEdge(crsList.get(i), crsList.get(j)))
                    {
                        myPair mp = new myPair(crsList.get(i), crsList.get(j));
                        pairList.add(mp);
                    }
                }
            }
        }

        /*for(int i=0; i<pairList.size(); i++)
        {
            System.out.println("(" + pairList.get(i).get_u().getU() + " , " + pairList.get(i).get_v().getU() + ")");
        }*/

        return pairList;
    }

    double crsPair(ArrayList<crsVertex>[] stuList, int totalStu ,ArrayList<crsVertex> crsList)
    {
        double min_penalty = -1;

        penalty_init = p.penaltyCount(stuList, totalStu, type);
        raw_penalty = penalty_init;
        //System.out.println("initial penalty_count: " + penalty_init);

        ArrayList<myPair> pairList = pair_making(crsList);
        //System.out.println("pairList size: " + pairList.size());
        for(int iter=0; iter<num_of_iter; iter++)
        {
            Random rand = new Random();
            int index = rand.nextInt(pairList.size());

            /*System.out.println("index: " + index);
            System.out.println("(" + pairList.get(index).get_u().getU() + " , " + pairList.get(index).get_v().getU() + ")");*/
            crsVertex u = pairList.get(index).get_u();
            crsVertex v = pairList.get(index).get_v();

            //if(g.isEdge(u, v))
            //{
            min_penalty = colorSwap(u, v, stuList, totalStu, crsList);
            //}
        }
        //System.out.println("kempe minimized penalty_count: " + min_penalty);
        return min_penalty;
    }

    double get_rawPenalty()
    {
        return raw_penalty;
    }

    double colorSwap(crsVertex u, crsVertex v, ArrayList<crsVertex>[] stuList, int totalStu, ArrayList<crsVertex> crsList)
    {
        int color1 = u.getColor();
        int color2 = v.getColor();

        ArrayList<crsVertex> tree = bfs(u, crsList.size(), color2);

        for(int i=0; i<tree.size(); i++)
        {
            crsVertex sub = tree.get(i);

            if(sub.getColor() == color1 || sub.getColor() == color2)
            {
                //int index = sub.getU() - 1;
                if(sub.getColor() == color1)
                {
                    //crsList.get(index).setColor(color2);
                    sub.setColor(color2);
                }
                else
                {
                    //crsList.get(index).setColor(color1);
                    sub.setColor(color1);
                }
            }
        }

        double penalty_swap = p.penaltyCount(stuList, totalStu, type);

        if(penalty_swap < penalty_init)
        {
            penalty_init = penalty_swap;
        }
        else
        {
            //repeat++;
            for(int i=0; i<tree.size(); i++)
            {
                crsVertex sub = tree.get(i);

                if(sub.getColor() == color1 || sub.getColor() == color2)
                {
                    //int index = sub.getU() - 1;
                    if(sub.getColor() == color1)
                    {
                        //crsList.get(index).setColor(color2);
                        sub.setColor(color2);
                    }
                    else
                    {
                        //crsList.get(index).setColor(color1);
                        sub.setColor(color1);
                    }
                }
            }
        }

        return penalty_init;
    }
}
