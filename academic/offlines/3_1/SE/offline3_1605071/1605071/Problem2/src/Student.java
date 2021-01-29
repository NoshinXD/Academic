import java.util.List;
import java.util.Scanner;

public class Student extends Person {
    //private int ID;
    private int mark, newmark;
    private boolean recheck;

    public int getID() {
        return ID;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public int getMark() {
        return mark;
    }

    public void setMark(int mark) {
        this.mark = mark;
    }

    public int getNewmark() {
        return newmark;
    }

    public void setNewmark(int newmark) {
        this.newmark = newmark;
    }

    public boolean isRecheck() {
        return recheck;
    }

    public void setRecheck(boolean recheck) {
        this.recheck = recheck;
    }

    public Student(ExamControllerOffice mediator, int ID)
    {
        super(mediator);
        this.ID = ID;
    }

    public void Send(String msz, int i, List<Student> stuList)
    {
        if(msz.equalsIgnoreCase("Re-examine"))
        {
            System.out.println("(From student) Re-examine request sent from student id : " + ID);
            mediator.ReCheck(msz, i, stuList);
        }
        else
        {
            mediator.Send(this, msz, i);
        }
    }

    public void Notify(String msz, int i)
    {
        if(msz.equalsIgnoreCase("sent"))
        {
            //System.out.println("Student id " + ID + " notified : " + "Scirpts and marks sent to office");
        }
        else if(msz.equalsIgnoreCase("Updated"))
        {
            System.out.println("Student " + ID + " prompt : " + "Marks were previously : " + mark + ". Now the corrected marks are " + newmark);
        }
        else if(msz.equalsIgnoreCase("Unchanged"))
        {
            System.out.println("Stduent " + ID + " prompt : " + "Marks unchanged.");
        }
        else if(msz.equalsIgnoreCase("Re-examine"))
        {
            System.out.println("(From " + this.getClass().getSimpleName() + ") StudentID : " + ID + " , Marks : " + mark);
        }
    }

    public void ReExamineReq()
    {
        System.out.println("Student " + ID + " prompt: Result published. Got marks " + mark);
        System.out.println("Do you want to apply for re-examine?");
        System.out.println("1.Yes");
        System.out.println("2.No");

        Scanner sc = new Scanner(System.in);
        int choice = sc.nextInt();

        if(choice == 1)
        {
            System.out.println("Re-examine request sent.\n");
            setRecheck(true);
        }
        else
        {
            setRecheck(false);
        }
        //return ID;
    }

    public void MyMark()
    {
        System.out.println("Student id : " + ID + " , Mark : " + mark);
    }
}
