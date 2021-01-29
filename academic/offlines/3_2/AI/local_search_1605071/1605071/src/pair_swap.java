import java.util.ArrayList;
import java.util.Random;

public class pair_swap {
    double penalty_init = -1;
    int num_of_iter = 10000;
    int type = 1;

    penalty_count p = new penalty_count();

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
                    if(g.isEdge(crsList.get(i), crsList.get(j)) == false)
                    {
                        if(crsList.get(i).getColor() != crsList.get(j).getColor())
                        {
                            myPair mp = new myPair(crsList.get(i), crsList.get(j));
                            pairList.add(mp);
                        }
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

    double do_pairSwap(ArrayList<crsVertex>[] stuList, int totalStu , ArrayList<crsVertex> crsList) {
        double min_penalty = -1;

        //Graph g = new Graph();

        /*for(int i=0; i<crsList.size(); i++)
        {
            System.out.println(crsList.get(i).getU() + " (" + crsList.get(i).getColor() + ")");
        }*/

        penalty_init = p.penaltyCount(stuList, totalStu, type);

        ArrayList<myPair> pairList = pair_making(crsList);

        for(int iter=0; iter<num_of_iter; iter++)
        {
            Random rand = new Random();
            int index = rand.nextInt(pairList.size());

            crsVertex u = pairList.get(index).get_u();
            crsVertex v = pairList.get(index).get_v();

            //uncomment from
            boolean swap = colorSwap(u, v);

            if(swap)
            {
                min_penalty = calculate_penalty(u, v, stuList, totalStu, crsList);
            }
            //to here
        }

        /*for(int i=0; i<crsList.size()-1; i++)
        {
            for(int j=i+1; j<crsList.size(); j++)
            {
                if(g.isEdge(crsList.get(i), crsList.get(j)) == false)
                {
                    //uncomment from
                    boolean swap = colorSwap(crsList.get(i), crsList.get(j));

                    if(swap)
                    {
                        min_penalty = calculate_penalty(crsList.get(i), crsList.get(j), stuList, totalStu, crsList);
                    }
                    //to here
                }
            }
        }*/

        /*if(g.isEdge(crsList.get(4), crsList.get(7)) == false)
        {
            System.out.println("[" + crsList.get(4).getU() + " , " + crsList.get(7).getU() + "]");

            boolean swap = colorSwap(crsList.get(4), crsList.get(7));

            if(swap)
            {
                System.out.println("here");
                min_penalty = calculate_penalty(crsList.get(4), crsList.get(7), stuList, totalStu, crsList);
            }
        }*/

        //System.out.println("pair_swap minimized penalty_count: " + min_penalty);
        return min_penalty;
    }

    boolean colorSwap(crsVertex u, crsVertex v) {
        int color1 = u.getColor();
        int color2 = v.getColor();

        //boolean isExist_u = false;
        //boolean isExist_v = false;

        boolean swapped = false;

        /*System.out.print(u.getU() + ": ");
        for(int i=0; i<u.getAdj().size(); i++)
        {
            System.out.print(u.getAdj().get(i).getU() + "(" + u.getAdj().get(i).getColor() + ") - ");
        }
        System.out.println();
        System.out.print(v.getU() + ": ");
        for(int i=0; i<v.getAdj().size(); i++)
        {
            System.out.print(v.getAdj().get(i).getU() + "(" + v.getAdj().get(i).getColor() + ") - ");
        }*/

        for(int i=0; i<u.getAdj().size(); i++)
        {
            if(u.getAdj().get(i).getColor() == color2)
            {
                //isExist_u = true;
                return swapped;
            }
        }

        for(int i=0; i<v.getAdj().size(); i++)
        {
            if(v.getAdj().get(i).getColor() == color1)
            {
                //isExist_v = true;
                return swapped;
            }
        }

        u.setColor(color2);
        v.setColor(color1);
        swapped = true;

        //double penalty_swap = p.penaltyCount(stuList, totalStu);

        return swapped;
    }

    double calculate_penalty(crsVertex u, crsVertex v, ArrayList<crsVertex>[] stuList, int totalStu, ArrayList<crsVertex> crsList) {
        double penalty_swap = p.penaltyCount(stuList, totalStu, type);

        if(penalty_swap < penalty_init)
        {
            penalty_init = penalty_swap;
        }
        else
        {
            int color1 = u.getColor();
            int color2 = v.getColor();

            u.setColor(color2);
            v.setColor(color1);
        }

        return penalty_init;
    }
}
