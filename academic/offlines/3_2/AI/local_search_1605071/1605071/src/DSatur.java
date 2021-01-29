import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class DSatur {
    int setColor(ArrayList<crsVertex> crsList) {
        ArrayList<Integer> colorList = new ArrayList<Integer>();
        ArrayList<Boolean> availColor = new ArrayList<Boolean>();

        ArrayList<crsVertex> q = new ArrayList<crsVertex>();

        /*for(int i=0; i<crsList.size(); i++)
        {
            System.out.println(crsList.get(i).getU() + " - " + crsList.get(i).getDegeree());
        }*/
        for(int i=0; i<crsList.size(); i++)
        {
            q.add(crsList.get(i));
            colorList.add(0);
            availColor.add(Boolean.TRUE);
        }

        crsVertex max_sat = q.get(0);
        //System.out.println(max_sat.getU());
        colorList.set(0, colorList.get(0) + 1);
        max_sat.setColor(0);
        q.remove(0);
        //uncolored = uncolored - 1;
        /*for(int i=0; i<q.size(); i++)
        {
            System.out.println(q.get(i).getU());
        }*/

        while(!q.isEmpty())
        {
            //if(q.size() == 4) System.out.println(max_sat.getU());
            for(int i=0; i<max_sat.getAdj().size(); i++)
            {
                ArrayList<Integer> adjColor = max_sat.getAdj().get(i).getAdjColor();

                boolean isExist = false;

                for(int j=0; j<adjColor.size(); j++)
                {
                    if(max_sat.getColor() == adjColor.get(j)) {
                        isExist = true;
                        break;
                    }
                }

                if(isExist == false)
                {
                    int prev_satpoint = max_sat.getAdj().get(i).getSat_point();
                    max_sat.getAdj().get(i).setSat_point(prev_satpoint + 1);
                    max_sat.getAdj().get(i).addAdjColor(max_sat.getColor()
                    );
                }
            }

            /*if(q.size() == 1)
            {
                for(int i=0; i<q.size(); i++)
                {
                    System.out.println(q.get(i).getU() + " - " + q.get(i).getDegeree() + " - " + q.get(i).getSat_point());
                }
                //break;
            }*/

            //System.out.println("------------");
            sortClass sc = new sortClass();
            //sc.crs_sortedby_satPoint(crsList);
            sc.crs_sortedby_satPoint(q);

            /*if(q.size() == 4)
            {
                for(int i=0; i<q.size(); i++)
                {
                    System.out.println(q.get(i).getU() + " - " + q.get(i).getDegeree() + " - " + q.get(i).getSat_point());
                }
                //break;
            }*/
            //System.out.println("---------");
            int max_satPoint = q.get(0).getSat_point();
            //if(q.size() == 8) System.out.println(max_satPoint);
            ArrayList<crsVertex> subList = new ArrayList<crsVertex>();

            for(int i=0; i<q.size(); i++)
            {
                if((q.get(i).getSat_point() == max_satPoint) && (q.get(i).getColor())== -1)
                {
                    subList.add(q.get(i));
                }
                else
                {
                    break;
                }
            }

            /*if(q.size() == 4)
            {
                for(int i=0; i<subList.size(); i++)
                {
                    System.out.println(subList.get(i).getU() + " - " + subList.get(i).getDegeree() + " - " + subList.get(i).getSat_point());
                }
            }*/

            sc.crs_sortedby_deg(subList);

            //System.out.println("-------");

            /*if(q.size() == 4)
            {
                for(int i=0; i<subList.size(); i++)
                {
                    System.out.println(subList.get(i).getU() + " - " + subList.get(i).getDegeree() + " - " + subList.get(i).getSat_point());
                }
            }*/

            max_sat = subList.get(0);
            //if(q.size() == 1) System.out.println(max_sat.getU());


            int index = -1;
            for(int i=0; i<q.size(); i++)
            {
                if(q.get(i).getU() == max_sat.getU())
                {
                    index = i;
                    break;
                }
            }

            //if(q.size() == 8) System.out.println(index);

            for(int i=0; i<max_sat.getAdj().size(); i++)
            {
                if(max_sat.getAdj().get(i).getColor() != -1)
                {
                    //if(uncolored == 8) System.out.println(max_sat.getAdj().get(i).getU());
                    availColor.set(max_sat.getAdj().get(i).getColor(), Boolean.FALSE);
                }
            }

            /*if(q.size() == 1)
            {
                for(int i=0; i<availColor.size(); i++)
                {
                    System.out.println(availColor.get(i));
                }
            }*/

            for(int i=0; i<availColor.size(); i++)
            {
                if(availColor.get(i).equals(true))
                {
                    colorList.set(i, colorList.get(i)+1);
                    max_sat.setColor(i);
                    break;
                }
            }
            /*if(q.size() == 2)
            {
                for(int i=0; i<availColor.size(); i++)
                {
                    System.out.println(colorList.get(i));
                }
            }*/
            //uncolored = uncolored - 1;
            q.remove(index);
            //q.remove(0);
            int listlen = availColor.size();
            availColor.clear();
            for(int i=0; i<listlen; i++)
            {
                availColor.add(Boolean.TRUE);
            }
            //System.out.println(q.size());
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
        return count;
    }
}
