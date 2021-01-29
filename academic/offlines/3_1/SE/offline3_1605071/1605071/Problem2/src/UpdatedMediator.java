import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class UpdatedMediator {
    public static void main(String[] args) {
        ConcreteMediator office = new ConcreteMediator();

        List<Student> stuList = new ArrayList<Student>();

        Examiner teach = new Examiner(office, 0);
        office.setExaminer(teach);

        Student stu1 = new Student(office, 1);
        stuList.add(stu1);
        stu1.setMark(59);

        Student stu2 = new Student(office, 2);
        stuList.add(stu2);
        stu2.setMark(53);

        Student stu3 = new Student(office, 3);
        stuList.add(stu3);
        stu3.setMark(65);

        Student stu4 = new Student(office, 4);
        stuList.add(stu4);
        stu4.setMark(49);

        Student stu5 = new Student(office, 5);
        stuList.add(stu5);
        stu5.setMark(57);

        Scanner sc = new Scanner(System.in);

        teach.MarkSent(stuList);
        System.out.println();
        for(int i=0; i<5; i++)
        {
            office.setStudent(stuList.get(i));
            teach.Send(stuList,"sent", 0);
        }
        System.out.println();

        /*System.out.println("Students are printing their marks...");
        for(int i=0; i<5; i++)
        {
            stuList.get(i).MyMark();
        }
        System.out.println();*/

        for(int i=0; i<5; i++)
        {
            stuList.get(i).ReExamineReq();
        }
        office.updatedRecheck(stuList);

        /*System.out.println("Do you want to recheck?");
        System.out.println("1. Yes  2. No");

        int choice = sc.nextInt();

        if(choice == 1)
        {
            System.out.println("For recheck : ");
            boolean error = false;

            boolean check = false;
            for(int i = 0; i<5; i++)
            {
                System.out.println("Enter Student ID : ");
                System.out.println("If time limit extends, press 6");
                int sid = sc.nextInt();

                if(sid >= 1 && sid <= 5)
                {
                    office.setStudent(stuList.get(sid-1));
                    stuList.get(sid-1).Send("Re-examine", stuList.get(sid-1).getID(), stuList);
                }
                else if(sid == 6)
                {
                    break;
                }
                else
                {
                    System.out.println("Wrong input");
                }
            }
        }
        else
        {
            System.out.println(":)");
        }*/
    }
}
