import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Test_main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));

        int n = Integer.parseInt(br.readLine()); 

        //Scanner in = new Scanner(System.in);

        //int n = in.nextInt();



        Matrix goal_matrix = new Matrix();

        String  goal_lines = br.readLine();

        String[] goal_strs = goal_lines.trim().split("\\s+");

        int k=0;
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                int entry = Integer.parseInt(goal_strs[k]);
                goal_matrix.set(i, j, entry);
                if(goal_matrix.get(i, j) == 0) {
                    goal_matrix.setBlankX(i);
                    goal_matrix.setBlankY(j);
                }

                k++;
            }
        }

        /*
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                System.out.print(goal_matrix.get(i, j) + "\t");
            }
            System.out.println();
        }
        System.out.println();

         */


        int test_count = 0;

        for(int it=0; it<n-1; it++)
        {
            test_count++;
            System.out.println();
            System.out.println("TEST :  " + test_count);
            System.out.println();
            Matrix init_matrix = new Matrix();

            String  init_lines = br.readLine();

            String[] init_strs = init_lines.trim().split("\\s+");

            k=0;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    int entry = Integer.parseInt(init_strs[k]);
                    init_matrix.set(i, j, entry);
                    //init_matrix.set(i, j, in.nextInt());
                    if(init_matrix.get(i, j) == 0) {
                        init_matrix.setBlankX(i);
                        init_matrix.setBlankY(j);
                    }
                    k++;
                }
            }

            /*
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    System.out.print(init_matrix.get(i, j) + "\t");
                }
                System.out.println();
            }
            System.out.println();

             */

            boolean init_solvable= IsSolvable.decision(init_matrix);
            //boolean goal_solvable= IsSolvable.decision(goal_matrix);

            //if(init_solvable && goal_solvable) {
            if(init_solvable) {
                System.out.println("Solvable");

                System.out.println("DISPLACEMENT");

                long startTimeMilliSecond_disp = System.currentTimeMillis();

                ArrayList<Matrix> path = AStar_displacement.findPath(init_matrix, goal_matrix);

                long endTimeMilliSecond_disp = System.currentTimeMillis();

                //System.out.println("PATH SIZE_disp: " + path.size());
                int move_disp = path.size() - 1;
                System.out.println("Move in Displacemet heuristic: " + move_disp);
                System.out.println("Path Found:\n");
                for(Matrix matrix : path) {
                    System.out.println(matrix);
                }

                //long endTimeMilliSecond_disp = System.currentTimeMillis();

                System.out.println("Time Taken in Dispalcement heuristic: "+(endTimeMilliSecond_disp - startTimeMilliSecond_disp) + " ms");

                System.out.println("\n\nMANHATTAN");

                long startTimeMilliSecond_manh = System.currentTimeMillis();

                ArrayList<Matrix> path2 = AStar_manhattan.findPath(init_matrix, goal_matrix);

                long endTimeMilliSecond_manh = System.currentTimeMillis();

                //System.out.println("PATH SIZE_manh: " + path.size());
                int move_manh = path2.size() - 1;
                System.out.println("Move in Manhattan heuristic: " + move_manh);
                System.out.println("Path Found:\n");
                for(Matrix matrix : path2) {
                    System.out.println(matrix);
                }

                //long endTimeMilliSecond_manh = System.currentTimeMillis();

                System.out.println("Time Taken in Manhattan heuristic: "+(endTimeMilliSecond_manh - startTimeMilliSecond_manh) + " ms");

            }
            else
            {
                System.out.println("Not Solvable");
            }

        }








        /*
        int k = 1;
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                goal_matrix.set(i, j, k);
                k++;

                if(k == 16)
                    break;
            }
        }
        goal_matrix.setBlankX(3);
        goal_matrix.setBlankY(3);

         */









//        //System.out.println("HERE");
//
//        IsSolvable dec = new IsSolvable();
//        boolean solvable = dec.decision(init_matrix);
//        if(solvable)
//        {
//            System.out.println("The given 15-puzzle problem is solvable\n\n");
//        }
//        else
//        {
//            System.out.println("The given 15-puzzle problem is not solvable\n\n");
//            return ;
//        }
//
//        disp_Solution_Ofpuzzle displacement = new disp_Solution_Ofpuzzle();
//        ArrayList<int[][]> disp_path = new ArrayList<int[][]>();
//        ArrayList<Integer> disp_cost = new ArrayList<Integer>();
//
//        System.out.println("DISPALCEMENT HEURISTIC\n");
//
//        disp_path = displacement.disp_find_path(init_matrix, goal_matrix);
//        disp_cost = displacement.disp_find_cost();
//
//        //System.out.println(disp_path.size());
//        int count1 = 0;
//
//        for(int a=0; a<disp_path.size(); a++)
//        {
//            //System.out.println("HERE");
//            if(a!=0 && a%2 == 0)
//            {
//                System.out.print("COST : ");
//                System.out.println(disp_path.get(a)[0][0] + "\t");
//                count1++;
//            }
//            else
//            {
//                for(int p=0; p<4; p++)
//                {
//                    for(int q=0; q<4; q++)
//                    {
//                        System.out.print(disp_path.get(a)[p][q] + "\t");
//                    }
//                    System.out.println();
//                }
//                System.out.println();
//            }
//
//            System.out.println();
//        }
//        System.out.println("COUNT1 " + count1);
//        System.out.println();

        /*System.out.println("MANHATTAN HEURISTIC\n");

        manh_Solution_Ofpuzzle manhattan = new manh_Solution_Ofpuzzle();//1 2 3 4 5 6 0 8 9 10 7 11 13 14 15 12
        ArrayList<int[][]> manh_path = new ArrayList<int[][]>();

        manh_path = manhattan.manh_find_path(init_matrix, goal_matrix);//0 1 15 14 4 13 12 11 3 10 9 8 2 7 6 5

        //System.out.println(manh_path.size());
        int count2 = 0;

        for(int a=0; a<manh_path.size(); a++)
        {
            //System.out.println("HERE");
            if(a!=0 && a%2 == 0)
            {
                System.out.print("COST : ");
                System.out.println(manh_path.get(a)[0][0] + "\t");
                count2++;
            }
            else
            {
                for(int p=0; p<4; p++)
                {
                    for(int q=0; q<4; q++)
                    {
                        System.out.print(manh_path.get(a)[p][q] + "\t");
                    }
                    System.out.println();
                }
                System.out.println();
            }

            System.out.println();
        }
        System.out.println("COUNT1 " + count1);
        System.out.println("COUNT2 " + count2);
        System.out.println();*/
    }
}
