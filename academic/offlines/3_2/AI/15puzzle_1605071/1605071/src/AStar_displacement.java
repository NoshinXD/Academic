import java.util.*;

public class AStar_displacement {
    //static int push_count = 0;
    static int pop_count = 0;

    public static ArrayList<Matrix> constructPath(HashMap<Matrix, Matrix> parent, Matrix src, Matrix goal) {
//        System.out.println("PARENT MAP --------------------------- ");
//        if(parent.isEmpty()) {
//            System.out.println("DAFAQ");
//            return new ArrayList<>();
//        }
//        else {
//            for(Map.Entry<Matrix, Matrix> entry : parent.entrySet()) {
//                Matrix key = entry.getKey();
//                Matrix value = entry.getValue();
//
//                System.out.println("PARENT OF -------------------------------------\n" + key + "IS------------------------\n" + value + "\n");
//            }
//        }

        ArrayList<Matrix> path = new ArrayList<>();
        Matrix current = goal;

        while(true) {
            path.add(current);
            if(current.isEqual(src)) {
                break;
            }
            current = parent.get(current);
        }

        Collections.reverse(path);

        System.out.println("Expanded node count in Displacement heuristic " + (pop_count - 1));
        //push_count = 0;
        pop_count = 0;
        return path;
    }

    public static ArrayList<Matrix> findPath(Matrix src, Matrix goal) {
        ArrayList<Matrix> pathList = new ArrayList<Matrix>();
        // heuristic: displacement
        dist_calculation h = new dist_calculation();



        src.setCost(h.displacement_distance(src, goal));
        src.setLevel(0);
        src.setType(-1);

        // parent of a matrix
        HashMap<Matrix, Matrix> parent = new HashMap<>();
        // distance of a state/matrix
        HashMap<Matrix, Integer> dist = new HashMap<>();

        dist.put(src, 0);
        parent.put(src, src);

        PriorityQueue<Matrix> pq = new PriorityQueue<>();
        pq.add(src);
        //push_count++;

        while(!pq.isEmpty()) {
            Matrix current = pq.peek();
            pq.remove();
            pop_count++;

            if(current.isEqual(goal)) {
                return constructPath(parent, src, current);
            }

            int dist_cur = dist.get(current);

            // left, right, up, down moves here
            // push in priority queue if not already
            if(current.getType() != Move_matrix.UP && current.getBlankX() < 3)
            {
                /// MOVE DOWN
                Matrix goDown = Move_matrix.fromDown(current);
                if(!dist.containsKey(goDown) || dist.get(goDown) > dist_cur + 1) {
                    dist.put(goDown, dist_cur + 1);
                    parent.put(goDown, current);
//                    System.out.println("Parent of \n" + goDown + "is\n" + current);

                    goDown.setCost(h.displacement_distance(goDown, goal));
                    goDown.setLevel(dist_cur + 1);

                    pq.add(goDown);
                    //push_count++;
                }
            }
            if(current.getType() != Move_matrix.DOWN && current.getBlankX() > 0)
            {
                /// MOVE UP
                Matrix goUp = Move_matrix.fromUp(current);

                if(!dist.containsKey(goUp) || dist.get(goUp) > dist_cur + 1)
                {
                    dist.put(goUp, dist_cur + 1);
                    parent.put(goUp, current);
//                    System.out.println("Parent of \n" + goUp + "is\n" + current);

                    goUp.setCost(h.displacement_distance(goUp, goal));
                    goUp.setLevel(dist_cur + 1);

                    pq.add(goUp);
                    //push_count++;
                }
            }

            if(current.getType() != Move_matrix.LEFT && current.getBlankY() < 3)
            {
                Matrix goRight = Move_matrix.fromRight(current);

                if(!dist.containsKey(goRight) || dist.get(goRight) > dist_cur + 1)
                {
                    dist.put(goRight, dist_cur + 1);
                    parent.put(goRight, current);
//                    System.out.println("Parent of \n" + goRight + "is\n" + current);

                    goRight.setCost(h.displacement_distance(goRight, goal));
                    goRight.setLevel(dist_cur + 1);

                    pq.add(goRight);
                    //push_count++;
                }
            }

            if(current.getType() != Move_matrix.RIGHT && current.getBlankY() > 0)
            {
                Matrix goLeft = Move_matrix.fromLeft(current);

                if(!dist.containsKey(goLeft) || dist.get(goLeft) > dist_cur + 1)
                {
                    dist.put(goLeft, dist_cur + 1);
                    parent.put(goLeft, current);
//                    System.out.println("Parent of \n" + goLeft + "is\n" + current);

                    goLeft.setCost(h.displacement_distance(goLeft, goal));
                    goLeft.setLevel(dist_cur + 1);

                    pq.add(goLeft);
                    //push_count++;
                }
            }
        }

        return new ArrayList<>();
    }
}
