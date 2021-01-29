public class Vanilla_Shake extends ShakeBuilder {

    @Override
    public String GetName() {
        return shake.Name_for_one("Vanilla-shake");
    }

    @Override
    public int GetPrice()
    {
        return shake.Price_for_one(190);
    }

    @Override
    public void AddSugar() {
        shake.Add("Sugar");
    }

    @Override
    public void AddOthers()
    {
        shake.Add("Vanilla-flavoring");
        shake.Add("Jello");
    }

    @Override
    public Shake GetShake() {
        return shake;
    }
}
