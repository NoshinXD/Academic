import java.util.LinkedList;

public class Shake
{
    private LinkedList<String> elements;
    private int One_Shake_Price;
    private String Shake_Name;

    public Shake()
    {
        elements = new LinkedList<String>();
        One_Shake_Price = 0;
    }

    public void Add(String element)
    {
        elements.addLast(element);
    }

    public int Price_for_one(int p)
    {
        One_Shake_Price = p;
        return One_Shake_Price;
    }

    public String Name_for_one(String name)
    {
        Shake_Name = name;
        return Shake_Name;
    }

    public void Print()
    {
        System.out.println(Shake_Name + " : ");
        System.out.println("Base Price : " + One_Shake_Price + "/-");
        for(int i = 0; i<elements.size(); i++)
        {
            String temp = elements.get(i);
            if(temp.equalsIgnoreCase("Almond-milk"))
            {
                System.out.println(elements.get(i) + "(Lactose-free): 60/-(added)");
                One_Shake_Price = One_Shake_Price + 60;
            }

            else if(temp.equalsIgnoreCase("candy"))
            {
                System.out.println(elements.get(i) + ": 50/-(added)");
                One_Shake_Price = One_Shake_Price + 50;
            }

            else if(temp.equalsIgnoreCase("cookie"))
            {
                System.out.println(elements.get(i) + ": 40/-(added)");
                One_Shake_Price = One_Shake_Price + 40;
            }
            /*else if(temp.equalsIgnoreCase("milk") && nm.equalsIgnoreCase("almond-milk"))
            {

            }*/
            else if(temp.equalsIgnoreCase("No-topping"))
            {

            }
            else
            {
                System.out.println(elements.get(i));
            }
        }

        System.out.println("Price : " + One_Shake_Price + "/-");
    }

    public int GetOneShakePrice()
    {
        //System.out.println("Inside shake cls : " + One_Shake_Price);
        return One_Shake_Price;
    }
}
