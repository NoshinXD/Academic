import java.util.ArrayList;

public class VariableOrdering {

    public static ArrayList<Variable> getNonAssignedList(Board board)
    {
        int n = board.getN();
        ArrayList<Variable> nonAssignedList = new ArrayList<Variable>();

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(board.getVariable(i, j).getValue() == 0)
                {
                    Variable var = board.getVariable(i, j);
                    nonAssignedList.add(var);
                }
            }
        }

        return nonAssignedList;
    }

    public static void calculateDomainForAll(Board board)
    {
        int n = board.getN();

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Variable var = board.getVariable(i, j);
                if(var.getValue() == 0)
                {
                    ArrayList<Integer> domain = getDomainList(board, var);
                    var.addDomain(domain);
                }
            }
        }
    }

    public static ArrayList<Integer> getDomainList(Board board, Variable var)
    {
        ArrayList<Integer> domain = new ArrayList<Integer>();

        int n = board.getN();

        int row = var.getRow();
        int col = var.getCol();

        for(int j=0; j<n; j++)
        {
           domain.add(j+1);
        }

        for(int c=0; c<n; c++)
        {
            int checkVal = board.getVariable(row, c).getValue();
            if(checkVal != 0)
            {
                domain.remove(new Integer(checkVal));
            }
        }

        for(int r=0; r<n; r++)
        {
            int checkVal = board.getVariable(r, col).getValue();
            if(checkVal != 0)
            {
                domain.remove(new Integer(checkVal));
            }
        }

        return domain;
    }

    public static int getDegree(Board board, Variable var)
    {
        int degree = 0;
        int n = board.getN();

        int row = var.getRow();
        int col = var.getCol();

        for(int c=0; c<n; c++)
        {
            int checkVal = board.getVariable(row, c).getValue();
            int tempCol = board.getVariable(row, c).getCol();
            if(tempCol != col && checkVal == 0)
            {
                degree++;
            }
        }

        for(int r=0; r<n; r++)
        {
            int checkVal = board.getVariable(r, col).getValue();
            int tempRow = board.getVariable(r, col).getRow();
            if(tempRow != row && checkVal == 0)
            {
                degree++;
            }
        }

        return degree;
    }

    public static Variable SDF(Board board)
    {
        //System.out.println("inside SDF");
        int n = board.getN();
        ArrayList<Variable> nonAssignedList = getNonAssignedList(board);

        int minDomainSize = 1000;
        Variable smallDomainVar = null;

        ArrayList<Integer> smallDomain = new ArrayList<Integer>();

        for(int i=0; i<nonAssignedList.size(); i++){

            smallDomain.clear();

            Variable var = nonAssignedList.get(i);

            smallDomain = getDomainList(board, var);

            int domainSize = smallDomain.size();

            if(domainSize < minDomainSize)
            {
                smallDomainVar = var;
                minDomainSize = domainSize;
                var.addDomain(smallDomain);
            }
        }

        return smallDomainVar;
    }

    public static Variable maxDynamicDeg(Board board)
    {
        int n = board.getN();
        ArrayList<Variable> nonAssignedList = getNonAssignedList(board);

        int maxDeg = -1000;

        Variable maxDegVar = null;

        ArrayList<Integer> maxDegDomain = new ArrayList<Integer>();

        for(int i=0; i<nonAssignedList.size(); i++)
        {
            maxDegDomain.clear();

            Variable var = nonAssignedList.get(i);

            int checkDeg = getDegree(board, var);

            if(checkDeg > maxDeg)
            {
                maxDeg = checkDeg;
                maxDegVar = var;

                maxDegDomain = getDomainList(board, var);
                var.addDomain(maxDegDomain);
            }
        }

        return maxDegVar;
    }

    public static Variable domddeg(Board board)
    {
        //System.out.println("in domddeg:");
        int n = board.getN();
        ArrayList<Variable> nonAssignedList = getNonAssignedList(board);

        double minRatio = 1000.0;

        Variable minRatioVar = null;

        ArrayList<Integer> minRatioDomain = new ArrayList<Integer>();

        for(int i=0; i<nonAssignedList.size(); i++)
        {
            minRatioDomain.clear();

            Variable var = nonAssignedList.get(i);

            minRatioDomain = getDomainList(board, var);

            double domainSize = minRatioDomain.size() * 1.0;

            double checkDeg = getDegree(board, var);

            if(checkDeg == 0)
            {
                //System.out.println("here");
                minRatioVar = var;
                var.addDomain(minRatioDomain);
                return minRatioVar;
            }

            double ratio = domainSize / checkDeg;

            if(ratio < minRatio)
            {
                minRatio = ratio;
                minRatioVar = var;
                var.addDomain(minRatioDomain);
            }
        }

        return minRatioVar;
    }

    public static Variable brelaz(Board board)
    {
        //System.out.println("in brelaz:");
        int n = board.getN();
        ArrayList<Variable> nonAssignedList = getNonAssignedList(board);

        int minDomainSize = 1000;
        Variable brelazVar = null;

        ArrayList<Integer> smallDomain = new ArrayList<Integer>();

        for(int i=0; i<nonAssignedList.size(); i++){

            smallDomain.clear();

            Variable var = nonAssignedList.get(i);

            smallDomain = getDomainList(board, var);

            int domainSize = smallDomain.size();

            if(domainSize < minDomainSize)
            {
                brelazVar = var;
                minDomainSize = domainSize;
                var.addDomain(smallDomain);
            }
            else if(domainSize == minDomainSize)
            {
                int deg = getDegree(board, var);
                int minDeg = getDegree(board, brelazVar);

                if(deg > minDeg)
                {
                    brelazVar = var;
                    var.addDomain(smallDomain);
                }
            }
        }

        return brelazVar;
    }

    public static void checkBoard(Board board)
    {
        boolean consistent = true;
        int n = board.getN();
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Variable var = board.getVariable(i, j);

                int value = var.getValue();

                int row = var.getRow();
                int col = var.getCol();

                for(int p=0; p<n; p++)
                {
                    if(p != col)
                    {
                        Variable tempVar = board.getVariable(row, p);

                        if(tempVar.getValue() == 0)
                        {
                            System.out.println("0 pacche");
                            consistent = false;
                            System.out.println("Current node: row: " + i + " , col: " + j);
                            System.out.println("0 in: row: " + row + " , col: " + p);
                        }

                        if(tempVar.getValue() == value)
                        {
                            System.out.println("repeat pacche");
                            consistent = false;
                            System.out.println("Current node: row: " + i + " , col: " + j);
                            System.out.println("repeat in: row: " + row + " , col: " + p);
                        }
                    }
                }

                for(int p=0; p<n; p++)
                {
                    if(p != row)
                    {
                        Variable tempVar = board.getVariable(p, col);

                        if(tempVar.getValue() == 0)
                        {
                            System.out.println("0 pacche");
                            consistent = false;
                            System.out.println("Current node: row: " + i + " , col: " + j);
                            System.out.println("0 In : row: " + p + " , col: " + col);
                        }

                        if(tempVar.getValue() == value)
                        {
                            System.out.println("repeat pacche");
                            consistent = false;
                            System.out.println("Current node: row: " + i + " , col: " + j);
                            System.out.println("repeat In : row: " + p + " , col: " + col);
                        }
                    }
                }
            }
        }

        if(consistent)
        {
            System.out.println("bingo");
        }
        else
        {
            System.out.println("problem!!!!!!!!!!!");
        }
    }
}
