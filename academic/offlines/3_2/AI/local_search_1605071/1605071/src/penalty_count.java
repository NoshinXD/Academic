import java.util.ArrayList;

public class penalty_count {
    //w0=16, w1=8, w2=4, w3=2 and w4=1

    double penaltyCount(ArrayList<crsVertex>[] stuList, int totalStu, int type) {
        int[] w = new int[]{ 16, 8, 4, 2, 1 };

        int total_penalty = 0;

        for(int i=1; i<totalStu+1; i++)
        {
            /*System.out.print(i + " : ");
            for(int j=0; j<stuList[i].size(); j++)
            {
                System.out.print(stuList[i].get(j).getU() + "(" + stuList[i].get(j).getColor() + ") - ");
            }
            System.out.println();

            System.out.println("---");*/
            if(type == 1)
            {
                sortClass sc = new sortClass();
                sc.crs_sortedby_color(stuList[i]);

                int gap = 0;
                int ind_penalty = 0;
                /*System.out.print(i + " : ");
                for(int j=0; j<stuList[i].size(); j++)
                {
                    System.out.print(stuList[i].get(j).getU() + "(" + stuList[i].get(j).getColor() + ") - ");
                }*/
                for(int j=0; j<stuList[i].size()-1; j++)
                {
                    gap = stuList[i].get(j+1).getColor() - stuList[i].get(j).getColor() - 1;

                    if(gap >=0 && gap <=4)
                    {
                        ind_penalty = ind_penalty + w[gap];
                    }
                }
                //System.out.print("penalty_count " + i + " : " + ind_penalty);
                //System.out.println();
                total_penalty = total_penalty + ind_penalty;
            }
            else if (type == 2)
            {
                /*System.out.print("\n" + i + " : ");
                for(int j=0; j<stuList[i].size(); j++)
                {
                    System.out.print(stuList[i].get(j).getU() + "(" + stuList[i].get(j).getColor() + ") - ");
                }
                System.out.println();*/
                //System.out.println("here");
                int gap = 0;
                int ind_penalty = 0;

                for(int j=0; j<stuList[i].size()-1; j++)
                {
                    for(int k=j+1; k<stuList[i].size(); k++)
                    {
                        //System.out.println();
                        //System.out.print("(" + stuList[i].get(j).getU() + " , " + stuList[i].get(k).getU() + ") - ");
                        int temp = stuList[i].get(j).getColor() - stuList[i].get(k).getColor();
                        gap = Math.abs(temp) - 1;

                        if(gap >=0 && gap <=4)
                        {
                            ind_penalty = ind_penalty + w[gap];
                        }
                    }
                    //System.out.println();
                }
                //System.out.println(i + ": " + ind_penalty);
                total_penalty = total_penalty + ind_penalty;
            }
        }
        //System.out.println("total penalty_count: " + total_penalty);

        double mean_penalty = (total_penalty * 1.0) / totalStu;

        return mean_penalty;
    }


}
