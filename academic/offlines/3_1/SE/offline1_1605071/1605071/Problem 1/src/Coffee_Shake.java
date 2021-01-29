public class Coffee_Shake extends ShakeBuilder {

    @Override
    public String GetName() {
        return shake.Name_for_one("Coffee-shake");
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
        shake.Add("Coffee");
        shake.Add("Jello");
    }

    @Override
    public Shake GetShake() {
        return shake;
    }
}
