import java.util.List;
import java.util.Random;

public class Examiner extends Person {
    //private int ID;

    public int getID() {
        return ID;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public Examiner(ExamControllerOffice mediator, int ID)
    {
        super(mediator);
        this.ID = ID;
    }

    public void MarkSent(List<Student> stuList)
    {
        System.out.println("Examiner prompt: Scripts and marks of student id 1,2,3,4,5 have been sent to exam controller office.\n");
        mediator.Scrutinize(stuList);
    }

    public void Send(List<Student> Marksheet, String msz, int i)
    {
        //System.out.println("HERE " + this.getID());

        mediator.Send(this, msz, i);
        //mediator.Scrutinize(Marksheet);
    }

    public void Notify(String msz, int i)
    {
        if(msz.equalsIgnoreCase("Re-examine"))
        {
            System.out.println("Examiner is notified : Exam script of student id " + i + " is sent from exam controller office for re-examine.\n");
        }
    }

    public void updatedNotify(List<Student> stuList)
    {
        System.out.print("Examiner prompt: Exam script of student id ");
        int count = 0;
        for(int i=0; i<stuList.size(); i++)
        {
            if(stuList.get(i).isRecheck() == true)
            {
                if(count !=0) System.out.print(" , ");
                System.out.print(stuList.get(i).getID());
                count++;
            }
        }
        System.out.println(" received for re-examine. ");
    }

    //public int ReExamine(List<Student> stuList, int prevmark, int i)
    public int ReExamine(int prevmark, int i)
    {
        int newmark = prevmark;
        boolean error = false;

        Random random = new Random();

        if(random.nextBoolean() == true)
        {
            int tempid = i+1;
            System.out.print("Marks of student id " + tempid + " changed.");

            Random rand1 = new Random();
            int exten = rand1.nextInt(5) + 1;

            Random rand2 = new Random();
            if(rand2.nextBoolean() == true)
                newmark = prevmark + exten;
            else
                newmark = prevmark - exten;

            System.out.println(" Previous marks were " + prevmark + ", now the corrected marks are " + newmark);
        }
        else
        {
            int tempid = i+1;
            System.out.println("Marks of student id " + tempid + " unchanged.");
            newmark = prevmark;
        }

        return newmark;
    }
}
