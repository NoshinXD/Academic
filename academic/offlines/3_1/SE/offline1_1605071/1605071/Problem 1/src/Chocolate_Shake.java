public class Chocolate_Shake extends ShakeBuilder {

    @Override
    public String GetName() {
        return shake.Name_for_one("Chocolate-shake");
    }

    @Override
    public int GetPrice()
    {
        return shake.Price_for_one(230);
    }

    @Override
    public void AddSugar() {
        shake.Add("Sugar");
    }

    @Override
    public void AddOthers()
    {
        shake.Add("Chocolate-syrup");
        shake.Add("Chocolate-icecream");
    }
}
