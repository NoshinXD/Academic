import javax.management.MBeanAttributeInfo;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.PriorityQueue;

public class Matrix implements Comparable<Matrix> {
    int[][] mat;

    int level;
    int cost;
    int type;
    int uniqval;
    int blankX, blankY;

    Matrix() {
        mat = new int[4][4];
    }

    Matrix(int[][] matrix) {
        this.mat = new int[4][4];
        assign(matrix);
    }

    Matrix(Matrix p) {
        this.mat = new int[4][4];
        assign(p.mat);
        this.level = p.level;
        this.cost = p.cost;
        this.blankX = p.blankX;
        this.blankY = p.blankY;
        this.uniqval = p.uniqval;
    }

    public int compareTo(Matrix p) {
        return Integer.valueOf(cost + level).compareTo(p.cost + p.level);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Matrix)) return false;
        Matrix matrix = (Matrix) o;
        return Arrays.equals(getMat(), matrix.getMat());
    }

    @Override
    public int hashCode() {
        return Arrays.hashCode(getMat());
    }

    //    static class MatrixComparator implements Comparator<Matrix> {
//        @Override
//        public int compare(Matrix o1, Matrix o2) {
//            return Integer.valueOf(o1.cost + o1.level).compareTo(Integer.valueOf(o2.cost + o2.level));
//        }
//    }

    public void assign(int[][] matrix) {
        this.mat = new int [4][4];
        for(int i=0; i<4; ++i) {
            for (int j = 0; j < 4; ++j) {
                this.mat[i][j] = matrix[i][j];
                if(this.mat[i][j] == 0) {
                    blankX = i;
                    blankY = j;
                }
            }
        }
    }

    public int getBlankX() {
        return blankX;
    }

    public int getBlankY() {
        return blankY;
    }

    public void setBlankX(int blankX) {
        this.blankX = blankX;
    }

    public void setBlankY(int blankY) {
        this.blankY = blankY;
    }

    void set(int i, int j, int val)
    {
        mat[i][j] = val;
    }

    public int get(int i, int j) {
        return mat[i][j];
    }

    public void setUniqval(int uniqval) {
        this.uniqval = uniqval;
    }

    public int getUniqval() {
        return uniqval;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public void setCost(int cost) {
        this.cost = cost;
    }

    public void setType(int type) {
        this.type = type;
    }

    int[][] getMat()
    {
        return mat;
    }

    public int getLevel() {
        return level;
    }

    public int getCost() {
        return cost;
    }

    public int getType() {
        return type;
    }

    public boolean isEqual(Matrix p) {
        for(int i=0; i<4; ++i) {
            for(int j=0; j<4; ++j) {
                if(mat[i][j] != p.mat[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    @Override
    public String toString() {
        String ret = "";
        for(int i=0; i<4; ++i) {
            for(int j=0; j<4; ++j) {
                ret += mat[i][j] + "\t";
            }
            ret += "\n";
        }
//        ret += "Cost: " + cost + "\n";
//        ret += "Level: " + level + "\n";
        return ret;
    }

//    public static void main(String[] args) {
//        HashMap<Matrix, Matrix> parent = new HashMap<>();
//
//        Matrix p = new Matrix();
//        for(int i=0; i<4; ++i) {
//            for(int j=0; j<4; ++j) {
//                p.set(i, j, i*4+j+1);
//            }
//        }
//        p.setCost(25);
//        p.setLevel(5);
//
//        Matrix q = new Matrix();
//        for(int i=0; i<4; ++i) {
//            for(int j=0; j<4; ++j) {
//                q.set(i, j, 16 - i * 4 + j + 1);
//            }
//        }
//        q.setCost(5);
//        q.setLevel(5);
//
//        System.out.println("P = " + p);
//        System.out.println("Q = " + q);
//
//        // parent of p is q
//        parent.put(p, q);
//
//        Matrix mat = parent.get(p);
//        System.out.println(mat);
//    }
}
