public class ComputerFactory {
    public Computer getComuter(String compType)
    {
        if(compType == null)
        {
            return null;
        }
        if(compType.equals("A"))
        {
            return new ComputerA();
        }
        else if(compType.equals("B"))
        {
            return new ComputerB();
        }
        else if(compType.equals("C"))
        {
            return new ComputerC();
        }
        return null;
    }
}
