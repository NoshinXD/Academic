import java.util.Scanner;

public class UpdatedObserver {
    public static void main(String[] args) {
        ABCserver abc = new ABCserver();

        PremiumUser pre = null;
        pre = new PremiumUser();
        abc.premium(pre);
        RegularUser reg = null;
        reg = new RegularUser();
        abc.regular(reg);


            Scanner sc = new Scanner(System.in);

            int prev_state = 0;//operational

            while(true)
            {
                /*System.out.println("In which state?");
                System.out.println("0. Operational.");
                System.out.println("1. Partially down.");
                System.out.println("2. Fully down");
                System.out.println("3. Exit");*/

                int cur_state;

                while(true)
                {
                    cur_state = sc.nextInt();
                    if(cur_state >=0 && cur_state <=3)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                if(cur_state == 3)
                {
                    break;
                }

                abc.setPrevstate(prev_state);

                abc.setCurstate(cur_state);

                prev_state = cur_state;
            }
    }
}
