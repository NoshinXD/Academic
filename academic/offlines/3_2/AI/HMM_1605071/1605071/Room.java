public class Room {
    private Cell[][] room;
    private int n;
    private int ghost_Xpos;
    private int ghost_Ypos;

    public Room(int n) {
        this.n = n;

        room = new Cell[n][n];
    }

    public int getN() {
        return n;
    }

    public void setCell(int i, int j)
    {
        Cell cell = new Cell();
        room[i][j] = cell;
    }

    public Cell getCell(int i, int j)
    {
        return room[i][j];
    }

    /*public void setProbability(double val, int i, int j)
    {
        Cell cell = getCell(i, j);
        cell.setProb_distr(val);
    }*/

    public int getGhost_Xpos() {
        return ghost_Xpos;
    }

    public void setGhost_Xpos(int ghost_Xpos) {
        this.ghost_Xpos = ghost_Xpos;
    }

    public int getGhost_Ypos() {
        return ghost_Ypos;
    }

    public void setGhost_Ypos(int ghost_Ypos) {
        this.ghost_Ypos = ghost_Ypos;
    }

    public void printRoom() {
        System.out.print("  |" + "\t");
        for(int i=0; i<n; i++)
        {
            System.out.print(" " + i + "\t\t");
        }
        System.out.println();
        System.out.println("-------------------------------------------------------------------------");
        for(int i=0; i<n; i++)
        {
            System.out.print(i + " |" + "\t");
            for(int j=0; j<n; j++)
            {
                double tempProba = room[i][j].getProb_distr() * 100;
                System.out.print(String.format("%.2f", tempProba) + "\t");
            }
            System.out.println();
        }
        System.out.println("-------------------------------------------------------------------------");
        System.out.println();
    }

    public void printGhost()
    {
        System.out.println("Ghost_position: (" + ghost_Xpos + " , " + ghost_Ypos + ")");
        System.out.println();
    }
}
