import java.util.ArrayList;

public class SolvingCSP_MAC {
    public static int nodeCountMAC = 0;
    public static int failCountMAC = 0;

    public static boolean MAC(Board board, int type)
    {
        ArrayList<Variable> nonAssignedList = VariableOrdering.getNonAssignedList(board);
        //board.printBoard();
        //System.out.println("unassignedSize: " + nonAssignedList.size());

        if(nonAssignedList.size() == 0)
        {
            //board.printBoard();
            VariableOrdering.checkBoard(board);
            System.out.println("nodeCount: " + nodeCountMAC);
            System.out.println("failCount: " + failCountMAC);
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

        //System.out.println("row: " + var.getRow() + " , col: " + var.getCol());
        //var.printDomain();

        ArrayList<Integer> varDomain = var.getDomain();

        for(int i=0; i<varDomain.size(); i++)
        {
            int val = varDomain.get(i);
            VariableOrdering.calculateDomainForAll(board);
            var.setValue(val);
            nodeCountMAC++;

            ArrayList<Integer> singleDomain = new ArrayList<>();
            singleDomain.add(val);
            var.addDomain(singleDomain);

            Boolean consistent = AC3_MAC(board, var);

            if(consistent)
            {
                //nodeCountMAC++;

                if(MAC(board, type))
                {
                    return true;
                }
            }
            else
            {
                failCountMAC++;
            }
            var.setValue(0);
            VariableOrdering.calculateDomainForAll(board);  //may change later
        }

        return false;
    }

    public static boolean AC3_MAC(Board board, Variable Vcv)
    {
        ArrayList<Variable> nonassignedList = VariableOrdering.getNonAssignedList(board);

        int n = board.getN();

        ArrayList<Variable> neighbours = new ArrayList<>(); //neighbours->q

        for(int i=0; i<nonassignedList.size(); i++) //finding neighbours
        {
            Variable tempVar = nonassignedList.get(i);

            int row = tempVar.getRow();
            int col = tempVar.getCol();

            if(row == Vcv.getRow() || col == Vcv.getCol())
            {
                neighbours.add(tempVar);
            }
        }

        ArrayList<ArcPair> arcList = new ArrayList<>();

        for(int i=0; i<neighbours.size(); i++)
        {
            Variable tempVar = neighbours.get(i);
            ArrayList<Integer> domain = tempVar.getDomain();

            if(domain.size() != 0)
            {
                ArcPair ac = new ArcPair(tempVar, Vcv);
                arcList.add(ac);
            }
            else
            {
                return false;
            }
        }

        boolean consistent = true;

        while(!arcList.isEmpty() && consistent)
        {
            Variable Vk = arcList.get(0).V1;
            Variable Vm = arcList.get(0).V2;
            arcList.remove(0);
            Boolean delete = REVISE(board, Vk, Vm);

            if(delete)
            {
                consistent = !(Vk.getDomain().isEmpty());

                ArrayList<Variable> neighboursOfNeigh = new ArrayList<>(); //Vk er neighboursList

                for(int i=0; i<nonassignedList.size(); i++)
                {
                    Variable Vi = nonassignedList.get(i);

                    if(Vk.getRow() == Vi.getRow() && Vk.getCol() == Vi.getCol()) //ok
                    {
                        //do nothing
                    }
                    else if(Vm.getRow() == Vi.getRow() && Vm.getCol() == Vi.getCol()) //ok
                    {
                        //do nothing
                    }
                    else
                    {
                        if(Vk.getRow() == Vi.getRow() || Vk.getCol() == Vi.getCol())
                        {
                            neighboursOfNeigh.add(Vi);
                        }
                    }
                }

                for(int i=0; i<neighboursOfNeigh.size(); i++)
                {
                    Variable Vi = neighboursOfNeigh.get(i);

                    ArrayList<Integer> ViDomain = Vi.getDomain();

                    if(ViDomain.size() != 0)
                    {
                        //System.out.println("here");
                        ArcPair tempAc = new ArcPair(Vi, Vk);
                        arcList.add(tempAc);
                    }
                }
            }
        }

        return consistent;
    }

    public static boolean REVISE(Board board, Variable Vi, Variable Vj) // Vj er neighbour Vi
    {
        boolean delete = false;
        boolean inconsistent = true;

        //int n = board.getN();

        ArrayList<Integer> Di = Vi.getDomain();
        ArrayList<Integer> Dj = Vj.getDomain();
        //System.out.println("DomainSize.Vj: " + Dj.size());

        for(int i=0; i<Di.size(); i++)
        {
            int x = Di.get(i);

            for(int j=0; j<Dj.size(); j++)
            {
                int y = Dj.get(j);
                if(x != y)
                {
                    inconsistent = false;
                }
            }

            if(inconsistent)
            {
                Di.remove(new Integer(x));
                delete = true;
            }
        }

        return delete;
    }
}
