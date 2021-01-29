import java.util.Random;

public class UpdateProbability {

    public static Room initialStateOfRoom()
    {
        int n = Contstants.n;

        Room room = new Room(n);

        double inti_prob_distr = (1*1.0) / (n*n);


        //placing cells in room
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                room.setCell(i, j);
            }
        }

        //sets intial probability
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Cell cell = room.getCell(i, j);
                cell.setProb_distr(inti_prob_distr);
            }
        }

        //sets more_proba, less_proba
        for(int i=0; i<n; i++) {
            for (int j = 0; j < n; j++)
            {
                double more_proba = 0.0;
                double less_proba = 0.0;
                Cell cell = room.getCell(i, j);

                if((i==0 && j==0) || (i==0 && j==n-1) || (i==n-1 && j==0) || (i==n-1 && j==n-1))
                {

                    more_proba = 0.48;
                    less_proba = 0.02;
                }

                else if(i==0 || i==n-1 || j==0 || j==n-1)
                {
                    more_proba = 0.32;
                    less_proba = 0.0133;
                }
                else
                {
                    more_proba = 0.24;
                    less_proba = 0.008;
                }
                cell.setMore_proba(more_proba);
                cell.setLess_proba(less_proba);
            }
        }

        //setting ghost randomly
        Random rand = new Random();

        int rand_int1 = rand.nextInt(n);
        int rand_int2 = rand.nextInt(n);

        Cell tempCell = room.getCell(rand_int1, rand_int2);

        room.setGhost_Xpos(rand_int1);
        room.setGhost_Ypos(rand_int2);

        return room;
    }

    public static int findColor(Room room, int user_i, int user_j)
    {
        int color;

        int n = room.getN();

        int x = room.getGhost_Xpos();
        int y = room.getGhost_Ypos();

        color = getColor_from_ManhattanDistance(n, x, y, user_i, user_j);

        return color;
    }

    public static Room copyRoom(Room prevRoom)
    {
        int n = prevRoom.getN();
        Room newRoom = new Room(n);

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                newRoom.setCell(i, j);
            }
        }

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Cell cell = newRoom.getCell(i, j);
                Double proba = prevRoom.getCell(i, j).getProb_distr();
                cell.setProb_distr(proba);
            }
        }

        int ghost_Xpos = prevRoom.getGhost_Xpos();
        int ghsot_Ypos = prevRoom.getGhost_Ypos();

        Cell tempCell = newRoom.getCell(ghost_Xpos, ghsot_Ypos);

        newRoom.setGhost_Xpos(ghost_Xpos);
        newRoom.setGhost_Ypos(ghsot_Ypos);

        return newRoom;
    }

    public static int getColor_from_ManhattanDistance(int n, int i, int j, int t1, int t2)
    {
        double maxDist = 2 * (n-1);
        double dist = 0.0;
        int color;

        dist = Math.abs(i-t1) + Math.abs(j-t2);

        if(dist >= 0 && dist <= 2) color = Contstants.RED;
        else if(dist > 2 && dist <= 6) color = Contstants.ORANGE;
        else color = Contstants.GREEN;

        /*dist = (dist * 1.0) / maxDist;

        if(dist <= 0.33) color = Contstants.RED;
        else if(dist > 0.33 && dist <= 0.67) color = Contstants.ORANGE;
        else color = Contstants.GREEN;*/

        return color;
    }

    public static void nextMoveGhost(Room room)
    {
        int n = room.getN();
        int prev_ghost_X = room.getGhost_Xpos();
        int prev_ghost_Y = room.getGhost_Ypos();
        int cur_ghost_X, cur_ghost_Y;

        boolean isLeft = true, isRight = true, isUp = true, isBottom = true;

        if(prev_ghost_X == 0) isUp = false;
        if(prev_ghost_X == n-1) isBottom = false;
        if(prev_ghost_Y == 0) isLeft = false;
        if(prev_ghost_Y == n-1) isRight = false;

        if(isUp == false && isLeft == false) //(0,0)
        {
            Random rand = new Random();
            double proba = rand.nextDouble();

            if(proba >= 0 && proba <= 0.47)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else if(proba > 0.47 && proba <= 0.95)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.95 && proba <= 0.97)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y;
            }

            room.setGhost_Xpos(cur_ghost_X);
            room.setGhost_Ypos(cur_ghost_Y);
            return;
        }

        if(isUp == false && isRight == false) //(0,8)
        {
            Random rand = new Random();
            double proba = rand.nextDouble();

            if(proba >= 0 && proba <= 0.47)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else if(proba > 0.47 && proba <= 0.95)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.95 && proba <= 0.97)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y;
            }

            room.setGhost_Xpos(cur_ghost_X);
            room.setGhost_Ypos(cur_ghost_Y);
            return;
        }

        if(isLeft == false && isBottom == false) //(8,0)
        {
            Random rand = new Random();
            double proba = rand.nextDouble();

            if(proba >= 0 && proba <= 0.47)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else if(proba > 0.47 && proba < 0.95)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.95 && proba <= 0.97)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y;
            }

            room.setGhost_Xpos(cur_ghost_X);
            room.setGhost_Ypos(cur_ghost_Y);
            return;
        }

        if(isBottom == false && isRight == false) //(8,8)
        {
            Random rand = new Random();
            double proba = rand.nextDouble();

            if(proba >= 0 && proba <= 0.47)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else if(proba > 0.47 && proba <= 0.95)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.95 && proba <= 0.97)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y;
            }

            room.setGhost_Xpos(cur_ghost_X);
            room.setGhost_Ypos(cur_ghost_Y);
            return;
        }

        if(isUp == false) //(0, smth)
        {
            Random rand = new Random();
            double proba = rand.nextDouble();

            if(proba >= 0 && proba <= 0.31)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else if(proba > 0.31 && proba <= 0.63)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else if(proba > 0.63 && proba <= 0.95)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.95 && proba <= 0.963)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else if(proba > 0.963 && proba <= 0.967)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y;
            }

            room.setGhost_Xpos(cur_ghost_X);
            room.setGhost_Ypos(cur_ghost_Y);
            return;
        }

        if(isBottom == false) //(8, smth)
        {
            Random rand = new Random();
            double proba = rand.nextDouble();

            if(proba >= 0 && proba <= 0.31)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else if(proba > 0.31 && proba <= 0.63)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else if(proba > 0.63 && proba <= 0.95)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.95 && proba <= 0.963)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else if(proba > 0.963 && proba <= 0.967)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y;
            }

            room.setGhost_Xpos(cur_ghost_X);
            room.setGhost_Ypos(cur_ghost_Y);
            return;
        }

        if(isLeft == false) //(smth, 0)
        {
            Random rand = new Random();
            double proba = rand.nextDouble();

            if(proba >= 0 && proba <= 0.31)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.31 && proba <= 0.63)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.63 && proba <= 0.95)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else if(proba > 0.95 && proba <= 0.963)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else if(proba > 0.963 && proba <= 0.967)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y + 1;
            }
            else
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y;
            }

            room.setGhost_Xpos(cur_ghost_X);
            room.setGhost_Ypos(cur_ghost_Y);
            return;
        }

        if(isRight == false) //(smth, 8)
        {
            Random rand = new Random();
            double proba = rand.nextDouble();

            if(proba >= 0 && proba <= 0.31)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.31 && proba <= 0.63)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y;
            }
            else if(proba > 0.63 && proba <= 0.95)
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else if(proba > 0.95 && proba <= 0.963)
            {
                cur_ghost_X = prev_ghost_X - 1;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else if(proba > 0.963 && proba <= 0.967)
            {
                cur_ghost_X = prev_ghost_X + 1;
                cur_ghost_Y = prev_ghost_Y - 1;
            }
            else
            {
                cur_ghost_X = prev_ghost_X;
                cur_ghost_Y = prev_ghost_Y;
            }

            room.setGhost_Xpos(cur_ghost_X);
            room.setGhost_Ypos(cur_ghost_Y);
            return;
        }

        Random rand = new Random();
        double proba = rand.nextDouble();

        if(proba >=0 && proba <= 0.23)
        {
            cur_ghost_X = prev_ghost_X;
            cur_ghost_Y = prev_ghost_Y - 1;
        }
        else if(proba > 0.23 && proba <= 0.47)
        {
            cur_ghost_X = prev_ghost_X;
            cur_ghost_Y = prev_ghost_Y + 1;
        }
        else if(proba > 0.47 && proba <= 0.71)
        {
            cur_ghost_X = prev_ghost_X - 1;
            cur_ghost_Y = prev_ghost_Y;
        }
        else if(proba > 0.71 && proba <= 0.95)
        {
            cur_ghost_X = prev_ghost_X + 1;
            cur_ghost_Y = prev_ghost_Y;
        }
        else if(proba > 0.95 && proba <= 0.96)
        {
            cur_ghost_X = prev_ghost_X - 1;
            cur_ghost_Y = prev_ghost_Y - 1;
        }
        else if(proba > 0.96 && proba <= 0.97)
        {
            cur_ghost_X = prev_ghost_X + 1;
            cur_ghost_Y = prev_ghost_Y + 1;
        }
        else if(proba > 0.97 && proba <= 0.98)
        {
            cur_ghost_X = prev_ghost_X - 1;
            cur_ghost_Y = prev_ghost_Y + 1;
        }
        else if(proba > 0.98 && proba <= 0.99)
        {
            cur_ghost_X = prev_ghost_X + 1;
            cur_ghost_Y = prev_ghost_Y - 1;
        }
        else
        {
            cur_ghost_X = prev_ghost_X;
            cur_ghost_Y = prev_ghost_Y;
        }

        room.setGhost_Xpos(cur_ghost_X);
        room.setGhost_Ypos(cur_ghost_Y);
        return;
    }

    public static void getCellProba(Room originalRoom, Room tempRoom, int i, int j)
    {
        int n = tempRoom.getN();

        double total_proba = 0.0;

        if(i-1 >= 0) //up neighbour
        {
            double neigh_proba = tempRoom.getCell(i-1, j).getProb_distr();
            double more_prob = originalRoom.getCell(i-1, j).getMore_proba();
            total_proba = total_proba + neigh_proba * more_prob;
            //if(i == 0 && j == 0) System.out.println("more proba: " + more_prob);
        }

        if(i+1 <= n-1) //down neighbour
        {
            double neigh_proba = tempRoom.getCell(i+1, j).getProb_distr();
            double more_prob = originalRoom.getCell(i+1, j).getMore_proba();
            total_proba = total_proba + neigh_proba * more_prob;
            //if(i == 0 && j == 0) System.out.println("more proba: " + more_prob);
        }

        if(j-1 >= 0) //left neighbour
        {
            double neigh_proba = tempRoom.getCell(i, j-1).getProb_distr();
            double more_prob = originalRoom.getCell(i, j-1).getMore_proba();
            total_proba = total_proba + neigh_proba * more_prob;
            //if(i == 0 && j == 0) System.out.println("more proba: " + more_prob);
        }

        if(j+1 <= n-1) //right neighbour
        {
            double neigh_proba = tempRoom.getCell(i, j+1).getProb_distr();
            double more_prob = originalRoom.getCell(i, j+1).getMore_proba();
            total_proba = total_proba + neigh_proba * more_prob;
            //if(i == 0 && j == 0) System.out.println("more proba: " + more_prob);
        }

        if(i-1 >=0 && j-1 >= 0) //upper left neighbour
        {
            double neigh_proba = tempRoom.getCell(i-1, j-1).getProb_distr();
            double less_prob = originalRoom.getCell(i-1, j-1).getLess_proba();
            total_proba = total_proba + neigh_proba * less_prob;
            //if(i == 0 && j == 0) System.out.println("less proba: " + less_prob);
        }

        if(i-1 >= 0 && j+1 <= n-1) //upper right neighbour
        {
            double neigh_proba = tempRoom.getCell(i-1, j+1).getProb_distr();
            double less_prob = originalRoom.getCell(i-1, j+1).getLess_proba();
            total_proba = total_proba + neigh_proba * less_prob;
            //if(i == 0 && j == 0) System.out.println("less proba: " + less_prob);
        }

        if(i+1 <= n-1 && j-1 >= 0) //bottom left neighbour
        {
            double neigh_proba = tempRoom.getCell(i+1, j-1).getProb_distr();
            double less_prob = originalRoom.getCell(i+1, j-1).getLess_proba();
            total_proba = total_proba + neigh_proba * less_prob;
            //if(i == 0 && j == 0) System.out.println("less proba: " + less_prob);
        }

        if(i+1 <= n-1 && j+1 <= n-1) // bootm right neighbour
        {
            double neigh_proba = tempRoom.getCell(i+1, j+1).getProb_distr();
            double less_prob = originalRoom.getCell(i+1, j+1).getLess_proba();
            total_proba = total_proba + neigh_proba * less_prob;
            //if(i == 0 && j == 0) System.out.println("less proba: " + less_prob);
        }

        //self
        double own_proba = tempRoom.getCell(i, j).getProb_distr();
        double less_prob = originalRoom.getCell(i, j).getLess_proba();
        total_proba = total_proba + own_proba * less_prob;
        //if(i == 0 && j == 0) System.out.println("less proba: " + less_prob);

        originalRoom.getCell(i, j).setProb_distr(total_proba);
    }

    public static Room updateProba_afterTimeAdvanced(Room originalRoom)
    {
        int n = originalRoom.getN();

        Room tempRoom = copyRoom(originalRoom);

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                getCellProba(originalRoom, tempRoom, i, j);
            }
        }

        return originalRoom;
    }

    public static void getCellProba_wrtColor(Room originalRoom, int i, int j, int t_i, int t_j)
    {
        int n = originalRoom.getN();

        double prev_proba = originalRoom.getCell(i, j).getProb_distr();

        int sensedColor = findColor(originalRoom, t_i, t_j);

        int probaColor = getColor_from_ManhattanDistance(n, i, j, t_i, t_j);

        double flag;

        if(sensedColor == probaColor) flag = 0.99;
        else flag = 0.01;

        double new_proba = prev_proba * flag;

        originalRoom.getCell(i, j).setProb_distr(new_proba);
    }

    public static Room updateProba_afterSesor(Room originalRoom, int user_i, int user_j)
    {
        int n = originalRoom.getN();

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                getCellProba_wrtColor(originalRoom, i, j, user_i, user_j);
            }
        }

        double totalProba = 0.0;

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                totalProba = totalProba + originalRoom.getCell(i, j).getProb_distr();
            }
        }

        //normalizing_prob_distr
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                double proba = originalRoom.getCell(i, j).getProb_distr();
                proba = proba / totalProba;
                originalRoom.getCell(i, j).setProb_distr(proba);
            }
        }

        return originalRoom;
    }
}
