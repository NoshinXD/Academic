public class IsSolvable {
    public static boolean decision(Matrix test_matrix)
    {
        int inversion = 0, temp = 0;
        boolean solvable = false;

        int[] temp_arr = new int[16];

        int index = 0;

        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                temp_arr[index] = test_matrix.get(i, j);
                index++;
            }
        }
        
        /*for(int i=0; i<16; i++)
        {

            System.out.print(temp_arr[i] + "\t");
        }*/

        for(int i=0; i<16; i++)
        {
            for(int j=i+1; j<16; j++)
            {
                if(temp_arr[i] != 0 && temp_arr[j] != 0 && (temp_arr[i] > temp_arr[j]))
                {
                    inversion++;
                    //System.out.println(temp_arr[i] + "\t" +temp_arr[j]);
                }
                /*else if(temp_arr[i] == 0)
                {
                    temp = 16 - (i + 1);
                }*/
            }
        }

        //n-i+1
        int blank_row_bottom = -1;

        for(int i=3; i>=0; i--)
        {
            for(int j=3; j>=0; j--)
            {
                if(test_matrix.get(i,j) == 0)
                {
                    blank_row_bottom = 3-i;
                    break;
                }
            }
        }

        if((inversion % 2 != 0 && blank_row_bottom % 2 != 0) || (inversion % 2 == 0 && blank_row_bottom % 2 == 0))
        {
            solvable = true;
        }


        //System.out.println("Inv inversion " + inversion);
        //System.out.println("Blank row from bottom " + blank_row_bottom);
        //System.out.println("Temp " + temp);
        //inversion = inversion + temp;
        //System.out.println("inversion " + inversion);
        return solvable;
    }

    /*

    public static boolean decision(Matrix test_matrix)
    {
        int x = 0;
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                if(test_matrix.get(i, j) == 0)
                {
                    if((i+j) % 2 != 0)
                    {
                        x = 1;
                    }
                }
            }
        }

        int cl = inversion(test_matrix);

        if((cl + x) % 2 == 0)
            return true;
        else
            return false;
    }

     */
}
