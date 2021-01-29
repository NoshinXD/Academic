import java.util.List;

public abstract class ExamControllerOffice {
    public abstract void Send(Person per, String msz, int i);
    public abstract void Scrutinize(List<Student> marksheet);
    public abstract boolean ReCheck(String msz, int i, List<Student> stuList);
}
