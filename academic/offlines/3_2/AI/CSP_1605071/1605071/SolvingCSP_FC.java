import java.awt.image.AreaAveragingScaleFilter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class SolvingCSP_FC {

    public static int nodeCount = 0;
    public static int failCount = 0;

    public static boolean FC(Board board, int type)
    {
        ArrayList<Variable> nonAssignedList = VariableOrdering.getNonAssignedList(board);
        //board.printBoard();
        //System.out.println("unassignedSize: " + nonAssignedList.size());

        if(nonAssignedList.size() == 0)
        {
            //board.printBoard();
            VariableOrdering.checkBoard(board);
            System.out.println("nodeCount: " + nodeCount);
            System.out.println("failCount: " + failCount);
            return true;
        }

        Variable var = null;

        if(type == 1)
        {
            var = VariableOrdering.SDF(board);
        }
        else if(type == 2)
        {
            var = VariableOrdering.domddeg(board);
        }
        else if(type == 3)
        {
            var = VariableOrdering.brelaz(board);
        }

        ArrayList<Integer> varDomain = var.getDomain();

        //if(varDomain.size() > 1) System.out.println("row: " + var.getRow() + " , col: " + var.getCol());

        /*if(var.getRow() == 1 && var.getCol() == 4)
        {
            System.out.println("for er baire");
            var.printDomain();
        }*/

        for(int i=0; i<varDomain.size(); i++)
        {
            int val = varDomain.get(i);
            VariableOrdering.calculateDomainForAll(board);
            /*if(var.getRow() == 1 && var.getCol() == 4)
            {
                System.out.println("for er shurute");
                var.printDomain();
            }*/
            var.setValue(val);
            nodeCount++;

            ArrayList<Integer> singleDomain = new ArrayList<>();
            singleDomain.add(val);
            var.addDomain(singleDomain);

            Boolean consistent = AC3_FC(board, var);

            if(consistent)
            {
                //nodeCount++;

                if(FC(board, type))
                {
                    return true;
                }
            }
            else
            {
                failCount++;
            }
            var.setValue(0);
            VariableOrdering.calculateDomainForAll(board);  //may chnage later
            //if(var.getDomain().size() > 1) System.out.println("row: " + var.getRow() + " , col: " + var.getCol());
            /*if(var.getRow() == 1 && var.getCol() == 4)
            {
                System.out.println("for er sheshe");
                var.printDomain();
            }*/
        }

        //System.out.println("count: " + count);
        return false;
    }

    public static boolean AC3_FC(Board board, Variable var) //var -> Vcv -> Vm
    {
        ArrayList<Variable> nonassignedList = VariableOrdering.getNonAssignedList(board);

        ArrayList<Variable> neighbours = new ArrayList<>(); //neighbours->q

        int varDomain = var.getDomain().get(0);

        for(int i=0; i<nonassignedList.size(); i++)
        {
            Variable tempVar = nonassignedList.get(i);

            int row = tempVar.getRow();
            int col = tempVar.getCol();

            if(row == var.getRow() || col == var.getCol())
            {
                neighbours.add(tempVar);
            }
        }

        for(int i=0; i<neighbours.size(); i++)
        {
            Variable neighVar = neighbours.get(i);

            ArrayList neighDomain = neighVar.getDomain();

            neighDomain.remove(new Integer(varDomain));

            if(neighDomain.size() == 0)
            {
                //System.out.println("size 0 hoise");
                return false;
            }
            else
            {
                //System.out.println("size 0 hoy nai");
            }
        }

        return true;
    }
}
