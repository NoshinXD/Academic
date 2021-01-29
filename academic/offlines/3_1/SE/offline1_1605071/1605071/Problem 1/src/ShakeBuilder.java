abstract class ShakeBuilder {
    protected Shake shake = new Shake();

    public ShakeBuilder() {
    }

    abstract String GetName();
    abstract int GetPrice();
    public void AddMilk(String milk)
    {
        if(milk.equals("1"))
            shake.Add("Milk");
        else if(milk.equals("2"))
            shake.Add("Almond-milk");
        //shake.Print();
    }
    abstract void AddSugar();
    abstract void AddOthers();
    public void AddTop(String top)
    {
        if(top.equals("1"))
        {
            shake.Add("Candy");
        }
        else if(top.equals("2"))
        {
            shake.Add("Cookie");
        }
        else
        {
            shake.Add("No-topping");
        }
    }
    public Shake GetShake()
    {
        return shake;
    }
}
