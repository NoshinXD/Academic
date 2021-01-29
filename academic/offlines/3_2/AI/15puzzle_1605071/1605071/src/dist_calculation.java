import java.util.ArrayList;

public class dist_calculation {
    public int displacement_distance(Matrix matrix1, Matrix matrix2)
    {
        int temp_disp_dist = 0;

        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                if(matrix1.get(i, j) != 0 && matrix1.get(i, j) != matrix2.get(i, j))
                {
                    temp_disp_dist++;
                }
            }
        }

        return temp_disp_dist;
    }

    public int manhattan_distance(Matrix matrix1, Matrix matrix2)
    {
        int temp_man_dist = 0;
        boolean found = false;
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                for(int a=0; a<4; a++)
                {
                    for(int b=0; b<4; b++)
                    {
                        //System.out.println("HERE");

                        if(matrix1.get(i, j) != 0 && matrix1.get(i, j) == matrix2.get(a, b))
                        {
                            temp_man_dist = temp_man_dist + Math.abs(i-a) + Math.abs(j-b);
                            found = true;
                        }
                        if(found == true)
                            break;
                    }
                    if(found == true)
                    {
                        found = false;
                        break;
                    }
                }
            }
        }
        //System.out.println("Cost " + temp_man_dist);
        return temp_man_dist;
    }



}
