import java.util.Comparator;

public class degreeComparator implements Comparator {

    public int compare(Object o1, Object o2) {
        crsVertex u = (crsVertex)o1;
        crsVertex v = (crsVertex)o2;

        if(u.getDegeree() == v.getDegeree())
            return 0;
        else if(u.getDegeree() > v.getDegeree())
            return 1;
        else
            return -1;
    }
}
