import java.io.IOException;

public class QSP {
    public static void main(String[] args) throws IOException {
        //Board board = fileWork.makeBoard("test.txt");
        /*String filename = fileWork.getFileName(0);
        Board board = fileWork.makeBoard(filename);
        VariableOrdering.calculateDomainForAll(board);*/

        System.out.println("MAC + SDF: ");
        for(int i=0; i<5; i++)
        {
            SolvingCSP_MAC.nodeCountMAC = 0;
            SolvingCSP_MAC.failCountMAC = 0;
            String filename = fileWork.getFileName(i);
            System.out.println("\nfile: " + filename + "\n");
            Board board = fileWork.makeBoard(filename);
            VariableOrdering.calculateDomainForAll(board);
            //System.out.println("MAC: ");
            int type = 1;
            SolvingCSP_MAC.MAC(board, type);
        }

        System.out.println("-----------------------------");

        System.out.println("FC + domddeg: ");
        for(int i=0; i<5; i++)
        {
            SolvingCSP_FC.nodeCount = 0;
            SolvingCSP_FC.failCount = 0;
            String filename = fileWork.getFileName(i);
            System.out.println("\nfile: " + filename + "\n");
            Board board = fileWork.makeBoard(filename);
            VariableOrdering.calculateDomainForAll(board);

            int type = 2;
            SolvingCSP_FC.FC(board, type);
        }

        System.out.println("-----------------------------");

        System.out.println("FC + brelaz: ");
        for(int i=0; i<5; i++)
        {
            SolvingCSP_FC.nodeCount = 0;
            SolvingCSP_FC.failCount = 0;
            String filename = fileWork.getFileName(i);
            System.out.println("\nfile: " + filename + "\n");
            Board board = fileWork.makeBoard(filename);
            VariableOrdering.calculateDomainForAll(board);

            int type = 3;
            SolvingCSP_FC.FC(board, type);
        }

    }
}
