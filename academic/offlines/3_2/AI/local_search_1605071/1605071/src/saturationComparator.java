import java.util.Comparator;

public class saturationComparator implements Comparator {
    public int compare(Object o1, Object o2) {
        crsVertex u = (crsVertex)o1;
        crsVertex v = (crsVertex)o2;

        if(u.getSat_point() == v.getSat_point())
            return 0;
        else if(u.getSat_point() > v.getSat_point())
            return 1;
        else
            return -1;
    }
}
