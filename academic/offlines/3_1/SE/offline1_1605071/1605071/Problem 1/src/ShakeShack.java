public class ShakeShack
{
    ShakeBuilder myIngredient;
    //ShakeBuilder Com;

    public void produceShake(ShakeBuilder ing)
    {
        myIngredient = ing;
        //Com = com_ing;
        myIngredient.GetName();
        myIngredient.GetPrice();
        //myIngredient.AddMilk(milk);
        myIngredient.AddSugar();
        myIngredient.AddOthers();
        //myIngredient.AddTop(top);

        //myIngredient.GetShake();
    }
    public void AddMilk(String milk)
    {
        myIngredient.AddMilk(milk);
    }
    public void AddTop(String top)
    {
        myIngredient.AddTop(top);
    }

    public Shake GetShake2()
    {
        return myIngredient.GetShake();
    }
}
