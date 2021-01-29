package javagame;
import java.util.ArrayList;
import java.util.Collections;

public class Pair {
    Co_ordinates from_co;
    Co_ordinates to_co;

    public Pair() {
    }

    public Pair(Co_ordinates from_co, Co_ordinates to_co) {
        this.from_co = from_co;
        this.to_co = to_co;
    }

    public Co_ordinates getFrom_co() {
        return from_co;
    }

    public Co_ordinates getTo_co() {
        return to_co;
    }

    public ArrayList<Pair> makePair(ArrayList<Checker> activeCheckerList)
    {
        ArrayList<Pair> pairList = new ArrayList<Pair>();

        for(int i=0; i<activeCheckerList.size(); i++)
        {
            Checker from_ch = activeCheckerList.get(i);

            int from_x = from_ch.getX_position();
            int from_y = from_ch.getY_position();

            Co_ordinates temp_from_co = new Co_ordinates(from_x, from_y);

            ArrayList<Co_ordinates> moveList = from_ch.getMoveList();

            for(int j=0; j<moveList.size(); j++)
            {
                int to_x = moveList.get(j).getX();
                int to_y = moveList.get(j).getY();

                Co_ordinates temp_to_co = new Co_ordinates(to_x, to_y);

                Pair p = new Pair(temp_from_co, temp_to_co);
                pairList.add(p);
            }
        }

        Collections.shuffle(pairList);

        return pairList;
    }
}
