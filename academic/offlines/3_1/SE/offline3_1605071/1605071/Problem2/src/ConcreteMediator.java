import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class ConcreteMediator extends ExamControllerOffice {
    private Examiner examiner;
    private Student student;

    //private ControllerOffice office;

    public void setExaminer(Examiner examiner) {
        this.examiner = examiner;
    }

    public void setStudent(Student student) {
        this.student = student;
    }

    public void Send(Person per, String msz, int i) {
        if(per == examiner)
        {
            student.Notify(msz, i);
        }
        else if(per == student)
        {
            /*if(msz.equalsIgnoreCase("Re-examine"))
            {
                System.out.print("(From exam-controller office)Re-examine request got from student id ");
                System.out.println(i);
            }*/
            examiner.Notify(msz, i);
        }
    }

    public void Scrutinize(List<Student> stuList)
    {
        System.out.println("Exam controller prompt: Scripts and marks of student id 1,2,3,4,5 have been received.");

        for(int i=0; i<stuList.size(); i++)
        {
            System.out.println("Student id : " + stuList.get(i).getID() + " , Marks : " + stuList.get(i).getMark());
        }
        System.out.println("Scrutinization has been done.");
        boolean scrut = false;

        for(int i=0; i<stuList.size(); i++)
        {
            Random random = new Random();

            if(i == 4 && scrut == false)
            {
                while(true)
                {
                    if(random.nextBoolean() == true)
                    {
                        int mark = stuList.get(i).getMark() + 5;
                        System.out.println("Marks of student id " + stuList.get(i).getID() + " were incorrect.");
                        System.out.println("Previous marks : " + stuList.get(i).getMark() + " , Corrected marks : " + mark + "\n");
                        stuList.get(i).setMark(mark);
                        scrut = true;
                        break;
                    }
                }
            }
            else
            {
                if(random.nextBoolean() == true)
                {
                    int mark = stuList.get(i).getMark() + 5;
                    System.out.println("Marks of student id : " + stuList.get(i).getID() + " were incorrect.");
                    System.out.println("Previous marks : " + stuList.get(i).getMark() + " , Corrected marks : " + mark + "\n");
                    stuList.get(i).setMark(mark);
                    scrut = true;
                }
            }
        }
        System.out.println("Result has been published to the students.");

        //System.out.println("(From exam controller office) Marksheet : ");
        /*for(int i=0; i<stuList.size(); i++)
        {
            System.out.println("Student id : " + stuList.get(i).getID() + " , Mark : " + stuList.get(i).getMark());
        }*/
    }

    public boolean ReCheck(String msz, int i, List<Student> stuList)
    {
        boolean error = false;
        if(msz.equalsIgnoreCase("Re-examine"))
        {
            System.out.println("(From exam-controller office) Re-examine request got from student id : " + i);
            examiner.Notify(msz, i);

            int prevmark = stuList.get(i-1).getMark();

            //error = examiner.ReExamine(stuList, prevmark, i);
            int newmark = examiner.ReExamine(prevmark, i);

            if(newmark == prevmark)
            {
                stuList.get(i-1).Notify("unchanged", prevmark);
                error = false;
            }
            else
            {
                stuList.get(i-1).setMark(newmark);
                stuList.get(i-1).Notify("Updated", prevmark);
                error = true;
            }

            /*for(int j=0; j<stuList.size(); j++)
            {
                stuList.get(j).Notify(msz, j+1);
            }*/
        }
        return error;
    }

    public void updatedRecheck(List<Student> stuList)
    {
        System.out.print("Exam controller prompt: Re-examine request got from student id ");
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
        System.out.println();

        System.out.print("Exam script of student id ");
        count = 0;
        for(int i=0; i<stuList.size(); i++)
        {
            if(stuList.get(i).isRecheck() == true)
            {
                if(count !=0) System.out.print(" , ");
                System.out.print(stuList.get(i).getID());
                count++;
            }
        }
        System.out.println(" sent to the examiner.\n");//ok

        //examiner.Notify("Re-examine", 0);
        examiner.updatedNotify(stuList);

        for(int i=0; i<stuList.size(); i++)
        {
            if(stuList.get(i).isRecheck() == true)
            {
                int prevmark = stuList.get(i).getMark();

                //error = examiner.ReExamine(stuList, prevmark, i);
                int newmark = examiner.ReExamine(prevmark, i);

                if(newmark == prevmark)
                {
                    stuList.get(i).setNewmark(stuList.get(i).getMark());
                }
                else
                {
                    stuList.get(i).setNewmark(newmark);
                }
            }
            else
            {
                stuList.get(i).setNewmark(stuList.get(i).getMark());
            }
        }
        System.out.println("\nExam controller prompt: ");

        for(int i=0; i<stuList.size(); i++)
        {
            //System.out.println(stuList.get(i).getMark() + " --" + stuList.get(i).getNewmark());
            if(stuList.get(i).isRecheck() == true)
            {
                if(stuList.get(i).getMark() == stuList.get(i).getNewmark())
                {
                    System.out.println("Marks of student id " + stuList.get(i).getID() + " unchanged.");
                }
                else
                {
                    System.out.println("Marks of student id " + stuList.get(i).getID() + " updated from " + stuList.get(i).getMark() + " to " + stuList.get(i).getNewmark() + ".");
                }
            }
        }
        System.out.println();

        for(int i=0; i<stuList.size(); i++)
        {
            //System.out.println(stuList.get(i).getMark() + " --" + stuList.get(i).getNewmark());
            if(stuList.get(i).isRecheck() == true)
            {
                if(stuList.get(i).getMark() == stuList.get(i).getNewmark())
                {
                    System.out.println("Student id " + stuList.get(i).getID() + " has been informed about no change in marks.");
                }
                else
                {
                    System.out.println("Updated marks have been sent to student id " + stuList.get(i).getID() + ".");
                }
            }
        }
        System.out.println();

        for(int i=0; i<stuList.size(); i++)
        {
            if(stuList.get(i).isRecheck() == true)
            {
                if(stuList.get(i).getMark() == stuList.get(i).getNewmark())
                {
                    stuList.get(i).Notify("unchanged", stuList.get(i).getMark());
                }
                else
                {
                    stuList.get(i).Notify("Updated", stuList.get(i).getMark());
                }
            }
        }

        /*for(int i=0; i<stuList.size(); i++)
        {
            System.out.println(stuList.get(i).getMark() + "--" + stuList.get(i).getNewmark());
        }*/
    }
}
