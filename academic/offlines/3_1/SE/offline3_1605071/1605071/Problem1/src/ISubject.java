public interface ISubject {
    void premium(IObserver o);
    void regular(IObserver o);
    void notifyObservers(String cls, int i, int j);
}
