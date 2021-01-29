import java.util.Comparator;

public class colorComparator implements Comparator {

    public int compare(Object o1, Object o2) {
        crsVertex u = (crsVertex)o1;
        crsVertex v = (crsVertex)o2;

        if(u.getColor() == v.getColor())
            return 0;
        else if(u.getColor() > v.getColor())
            return 1;
        else
            return -1;
    }
}
