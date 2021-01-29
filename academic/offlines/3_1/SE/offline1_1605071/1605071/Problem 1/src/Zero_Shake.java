public class Zero_Shake extends ShakeBuilder {

    @Override
    public String GetName() {
        return shake.Name_for_one("Zero-shake");
    }

    @Override
    public int GetPrice()
    {
        return shake.Price_for_one(240);
    }

    @Override
    public void AddSugar() {
        shake.Add("Sweetner");
    }

    @Override
    public void AddOthers()
    {
        shake.Add("Vanilla-flavoring");
        shake.Add("Sugar-free-jello");
    }

    @Override
    public Shake GetShake() {
        return shake;
    }
}
