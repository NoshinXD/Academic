import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class fileWork {
    public static Board makeBoard(String filename) throws IOException
    {
        BufferedReader br = new BufferedReader(new FileReader(filename));

        String lineFor_n = br.readLine();
        lineFor_n = lineFor_n.replaceAll("[^\\d]", " ");
        lineFor_n = lineFor_n.trim();
        lineFor_n = lineFor_n.replaceAll(" +", " ");
        int n = Integer.parseInt(lineFor_n);
        //int n = Integer.parseInt(br.readLine());
        //System.out.println("N: " + n);

        br.readLine();
        br.readLine();

        Board board = new Board(n);

        for(int i=0; i<n; i++)
        {
            String  init_lines = br.readLine();

            //String[] init_val = init_lines.trim().split("\\s+");
            String[] init_val = init_lines.trim().split(", ");

            for(int j=0; j<init_val.length; j++)
            {
                if(j == init_val.length - 1)
                {
                    init_val[j] = init_val[j].replaceAll("[^\\d]", " ");
                    init_val[j] = init_val[j].trim();
                    init_val[j] = init_val[j].replaceAll(" +", " ");
                }

                int entry = Integer.parseInt(init_val[j]);
                board.setVariable(entry, i, j);
            }
        }

        return board;
    }

    public static String getFileName(int index)
    {
        String[] dataset = {"d-10-01", "d-10-06", "d-10-07", "d-10-08", "d-10-09", "d-15-01"};

        return dataset[index] + ".txt.txt";
    }
}
