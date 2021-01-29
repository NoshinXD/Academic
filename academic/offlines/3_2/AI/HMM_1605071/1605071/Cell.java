public class Cell {
    private double prob_distr;
    private double more_proba;
    private double less_proba;

    public Cell() {

    }

    public double getProb_distr() {
        return prob_distr;
    }

    public void setProb_distr(double prob_distr) {
        this.prob_distr = prob_distr;
    }

    public double getMore_proba() {
        return more_proba;
    }

    public void setMore_proba(double more_proba) {
        this.more_proba = more_proba;
    }

    public double getLess_proba() {
        return less_proba;
    }

    public void setLess_proba(double less_proba) {
        this.less_proba = less_proba;
    }
}
