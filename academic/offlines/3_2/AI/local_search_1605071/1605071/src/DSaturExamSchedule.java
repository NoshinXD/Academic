import java.io.*;
import java.util.ArrayList;

public class DSaturExamSchedule  {
    public static void main(String[] args) throws IOException {
        //File file = new File("input.txt");
        File file = new File("car-s-91.stu");
        //File file2 = new File("crs.txt");

        BufferedReader br = new BufferedReader(new FileReader(file));
        //BufferedReader br2 = new BufferedReader(new FileReader(file2));

        //FileReader       stu_input = new FileReader("input.txt");
        FileReader       stu_input = new FileReader("car-s-91.stu");
        LineNumberReader stuCount = new LineNumberReader(stu_input);
        while (stuCount.skip(Long.MAX_VALUE) > 0)
        {
            // Loop just in case the file is > Long.MAX_VALUE or skip() decides to not read the entire file
        }

        int totalStu = stuCount.getLineNumber() + 1;
        //System.out.println("Total Student: " + totalStu);

        //FileReader       input = new FileReader("crs.txt");
        FileReader       input = new FileReader("car-s-91.crs");
        LineNumberReader count = new LineNumberReader(input);

        while (count.skip(Long.MAX_VALUE) > 0)
        {
            // Loop just in case the file is > Long.MAX_VALUE or skip() decides to not read the entire file
        }

        int totalCrs = count.getLineNumber() + 1;

        //System.out.println("Total Course: " + totalCrs);

        String st;

        ArrayList<crsVertex>[] stuList = new ArrayList[totalStu + 1];

        for (int i = 1; i < totalStu+1; i++) { //1-indexing
            stuList[i] = new ArrayList<crsVertex>();
        }

        ArrayList<crsVertex> crsList = new ArrayList<crsVertex>();

        for(int i=0; i<totalCrs; i++)
        {
            crsVertex u = new crsVertex(i+1);
            crsList.add(u);
        }

        //System.out.println(crsList.size());
        int check = 0;
        int stuId = 0;
        while ((st = br.readLine()) != null)
        {
            stuId++;
            //System.out.println(st);
            String[] crs_strs = st.trim().split("\\s+");
            //System.out.println(crs_strs.length);
            for(int i=0; i<crs_strs.length; i++)
            {
                int u = Integer.parseInt(crs_strs[i]);
                crsVertex u_ver = crsList.get(u-1);
                stuList[stuId].add(u_ver);
            }

            if(crs_strs.length > 1)
            {
                for(int i=0; i<crs_strs.length-1; i++)
                {
                    int u = Integer.parseInt(crs_strs[i]);

                    crsVertex u_ver = crsList.get(u-1);

                    for(int j=i+1; j<crs_strs.length; j++)
                    {
                        int v = Integer.parseInt(crs_strs[j]);

                        crsVertex v_ver = crsList.get(v-1);

                        Graph g = new Graph();

                        if(g.isEdge(u_ver, v_ver) == false)
                        {
                            g.addEdge(u_ver, v_ver);
                        }
                    }
                }
            }
            /*else
            {
                int u = Integer.parseInt(crs_strs[0]);

                crsVertex u_ver = crsList.get(u-1);
                stuList[stuId].add(u_ver);
            }*/
        }

        /*ArrayList<crsVertex> temp = crsList.get(7).getAdj();
        System.out.println("vertex: " + crsList.get(7).getU());
        for(int i=0; i<temp.size(); i++)
        {
            System.out.println(temp.get(i).getU());
        }*/

        /*ArrayList<crsVertex> test = crsList.get(1).getAdj();
        for(int i=0; i<test.size(); i++)
        {
            System.out.println(test.get(i).getU());
        }*/
        /*for(int i=0; i<crsList.size(); i++)
        {
            System.out.println(crsList.get(i).getU());
        }*/
        //Graph g = new Graph();
        //System.out.println(g.isEdge(crsList.get(0), crsList.get(4)));

        //crsVertex n = new crsVertex(0);
        //n.getAdj();
        /*for(int i=1; i<totalStu+1; i++)
        {
            System.out.print(i + " : ");
            for(int j=0; j<stuList[i].size(); j++)
            {
                System.out.print(stuList[i].get(j).getU() + " - ");
            }
            System.out.println();
        }*/

        /*sortDegree sd = new sortDegree();
        ArrayList<crsVertex> test = sd.crs_sortedby_deg(crsList);*/
        /*for(int i=0; i<crsList.size(); i++)
        {
            System.out.println(crsList.get(i).getU()+ " " + crsList.get(i).getDegeree());
        }*/

        sortClass sc = new sortClass();
        sc.crs_sortedby_deg(crsList);


        /*for(int i=0; i<crsList.size(); i++)
        {
            System.out.println(crsList.get(i).getU()+ " " + crsList.get(i).getDegeree());
        }*/
        /*ArrayList<crsVertex> withAdjCrs = new ArrayList<crsVertex>();
        for(int i=0; i<crsList.size(); i++)
        {
            if(crsList.get(i).getDegeree() != 0)
            {
                withAdjCrs.add(crsList.get(i));
            }
            else
            {
                break;
            }
        }*/

        DSatur ds = new DSatur();
        int minSlot = ds.setColor(crsList);


        /*System.out.println("Colors:");
        for(int i=1; i<totalStu+1; i++)
        {
            System.out.print(i + " : ");
            for(int j=0; j<stuList[i].size(); j++)
            {
                System.out.print(stuList[i].get(j).getU() + "(" + stuList[i].get(j).getColor() + ") - ");
            }
            System.out.println();
        }*/
        /*System.out.println("from main");
        copyArray c = new copyArray();
        c.assign(stuList, totalStu, crsList);
        c.get_tempCrsList(crsList);
        System.out.println("from main");*/


        /*penalty_count p = new penalty_count();
        double mean_penalty = p.penaltyCount(stuList, totalStu);
        System.out.println("mean penalty_count: " + mean_penalty);*/

        /*random_kempe rk = new random_kempe();
        rk.crsPair(stuList, totalStu, crsList);*/

        //stochastic_hill_climbing
        /*stochastic_kempe sk = new stochastic_kempe();
        sk.crsPair(stuList, totalStu, crsList);*/

        stochastic_kempe bkc = new stochastic_kempe();
        double min_penalty = bkc.crsPair(stuList, totalStu, crsList);

        //normal_hill_climbing
        /*kempeChain kc = new kempeChain();
        kc.crsPair(stuList, totalStu, crsList);*/ //uncomment it

        //kc.colorSwap(stuList, crsList);
        pair_swap ps = new pair_swap();
        double pair_swap_minPenalty = ps.do_pairSwap(stuList, totalStu, crsList);

        FileWriter myWriter = new FileWriter("sol.txt");

        for(int i=0; i<crsList.size(); i++)
        {
            //System.out.println(crsList.get(i).getU() + " - " + crsList.get(i).getColor());
            //System.out.println("here");
            myWriter.write(crsList.get(i).getU() + " " + crsList.get(i).getColor() + "\n");
        }
        myWriter.close();

        String result = Integer.toString(minSlot) + " ; " + Double.toString(min_penalty) + " ; " + Double.toString(pair_swap_minPenalty);
        System.out.println(result);
    }
}
