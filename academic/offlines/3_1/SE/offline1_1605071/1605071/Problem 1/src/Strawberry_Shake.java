public class Strawberry_Shake extends ShakeBuilder {

    @Override
    public String GetName() {
        return shake.Name_for_one("Strawberry-shake");
    }

    @Override
    public int GetPrice()
    {
        return shake.Price_for_one(200);
    }

    @Override
    public void AddSugar() {
        shake.Add("Sugar");
    }

    @Override
    public void AddOthers()
    {
        shake.Add("Strawberry-syrup");
        shake.Add("Strawberry-icecream");
    }

    @Override
    public Shake GetShake() {
        return shake;
    }
}
