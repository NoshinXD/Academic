import java.util.*;

public class sortClass {
    ArrayList<crsVertex> crs_sortedby_deg(ArrayList<crsVertex> crsList) {
        Collections.sort(crsList, new degreeComparator().reversed());
        Iterator itr = crsList.iterator();
        while (itr.hasNext()) {
            crsVertex st = (crsVertex) itr.next();
        }

        return crsList;
    }

    ArrayList<crsVertex> crs_sortedby_color(ArrayList<crsVertex> crsList) {
        Collections.sort(crsList, new colorComparator());
        Iterator itr = crsList.iterator();
        while (itr.hasNext()) {
            crsVertex st = (crsVertex) itr.next();
        }

        return crsList;
    }

    ArrayList<crsVertex> crs_sortedby_satPoint(ArrayList<crsVertex> crsList) {
        Collections.sort(crsList, new saturationComparator().reversed());
        Iterator itr = crsList.iterator();
        while (itr.hasNext()) {
            crsVertex st = (crsVertex) itr.next();
        }

        return crsList;
    }
    /*Queue<crsVertex> crs_sortedby_satPoint(Queue<crsVertex> crsList) {
        Collections.sort(crsList, new saturationComparator().reversed());
        Iterator itr = crsList.iterator();
        while (itr.hasNext()) {
            crsVertex st = (crsVertex) itr.next();
        }

        return crsList;
    }*/
}
