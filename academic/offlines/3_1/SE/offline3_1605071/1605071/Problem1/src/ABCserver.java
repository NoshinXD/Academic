import java.util.ArrayList;
import java.util.List;

public class ABCserver implements ISubject {
    private int prevstate, Curstate;

    public int getPrevstate() {
        return prevstate;
    }

    public void setPrevstate(int prevstate) {
        this.prevstate = prevstate;
    }

    public int getCurstate() {
        return Curstate;
    }

    public void setCurstate(int Curstate) {
        //System.out.println("HERE3");
        this.Curstate = Curstate;
        notifyObservers(this.getClass().getSimpleName(), prevstate, Curstate);
    }

    //IObserver observer;
    List<IObserver> observerList = new ArrayList<IObserver>();

    @Override
    public void premium(IObserver o) {
        observerList.add(o);
    }

    @Override
    public void regular(IObserver o) {
        observerList.add(o);
    }

    @Override
    public void notifyObservers(String cls, int prevValue, int updatedValue) {
        //System.out.println("HERE4");
        //return observer.update(this.getClass().getSimpleName(), s, prevValue, updatedValue);
        //setOp(s);
        for(int i=0; i<observerList.size(); i++)
        {
            observerList.get(i).update(this.getClass().getSimpleName(), prevValue, updatedValue);
        }
    }

}
