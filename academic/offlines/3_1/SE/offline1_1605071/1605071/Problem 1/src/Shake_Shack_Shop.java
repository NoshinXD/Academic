import java.util.LinkedList;
import java.util.Scanner;

public class Shake_Shack_Shop {

    /*public static Shake Order_Shake(char shakeType, char milk, char top)
    {
        int total = 0;
        //Shake sh = null;
        ShakeShack director = new ShakeShack();
        if(shakeType == '1')
        {
            ShakeBuilder choco_shake_Ing = new Chocolate_Shake();
            director.produceShake(choco_shake_Ing, milk, top);
            //Shake choco_sh = choco_shake_Ing.GetShake();
            Shake choco_sh = director.GetShake2();
            return choco_sh;
        }
        else if (shakeType == '2') {
            ShakeBuilder Cof_Shake_Ing = new Coffee_Shake();
            director.produceShake(Cof_Shake_Ing, milk, top);
            //Shake coffee_sh = Cof_Shake_Ing.GetShake();
            Shake coffee_sh = director.GetShake2();

            return coffee_sh;
        }

        else if (shakeType == '3') {
            ShakeBuilder Straw_Shake_Ing = new Strawberry_Shake();
            director.produceShake(Straw_Shake_Ing, milk, top);
            //Shake straw_sh = Straw_Shake_Ing.GetShake();
            Shake straw_sh = director.GetShake2();

            return straw_sh;
        }

        else if (shakeType == '4') {
            ShakeBuilder Van_Shake_Ing = new Vanilla_Shake();
            director.produceShake(Van_Shake_Ing, milk, top);
            //Shake van_sh = Van_Shake_Ing.GetShake();
            Shake van_sh = director.GetShake2();

            return van_sh;
        }

        else if (shakeType == '5') {
            ShakeBuilder Zero_Shake_Ing = new Zero_Shake();
            director.produceShake(Zero_Shake_Ing, milk, top);
            //Shake zero_sh = Zero_Shake_Ing.GetShake();
            Shake zero_sh = director.GetShake2();

            return zero_sh;
        }

        return null;
    }*/

    public static Shake Order_Shake(String shakeType, String milk, String top)
    {
        //int total = 0;
        //Shake sh = null;
        ShakeBuilder shake_Ing;
        //ShakeBuilder com_Ing;
        ShakeShack director = new ShakeShack();
        if(shakeType.equals("1"))
        {
            shake_Ing = new Chocolate_Shake();
            //com_Ing = new Chocolate_Shake();
        }
        else if (shakeType.equals("2")) {
            shake_Ing = new Coffee_Shake();
            //com_Ing = new Coffee_Shake();
        }

        else if (shakeType.equals("3")) {
            shake_Ing = new Strawberry_Shake();
            //com_Ing = new Strawberry_Shake();
        }

        else if (shakeType.equals("4")) {
            shake_Ing = new Vanilla_Shake();
            //com_Ing = new Vanilla_Shake();
        }

        else if (shakeType.equals("5")) {
            shake_Ing = new Zero_Shake();
            //com_Ing = new Zero_Shake();
        }
        else
        {
            shake_Ing = null;
            //com_Ing = null;
        }
        director.produceShake(shake_Ing);
        director.AddMilk(milk);
        director.AddTop(top);
        return director.GetShake2();
        //return shake_Ing.GetShake();
    }

    public static void main(String[] args) {
        System.out.println("    SHAKE-SHACK    ");

        while(true)
        {
            int open = 0, candy = 0, cookie = 0, track = 0;
            boolean running = false;
            System.out.println("For placing order press O");

            Scanner sc = new Scanner(System.in);
            String ch = sc.nextLine();
            String shakeType, milk, con, top = null;
            int cur;

            if(ch.equals("O"))
            {
                LinkedList<Shake> shakes = new LinkedList<Shake>();

                cur = 1;
                int total_order_price = 0;
                while(true)
                {
                    top = "0";
                    System.out.println("   Shake-Type             Base Price");
                    System.out.println("1. Chocolate-Shake  :     230/-");
                    System.out.println("2. Coffee-Shake     :     230/-");
                    System.out.println("3. Strawberry-Shake :     200/-");
                    System.out.println("4. Vanilla-Shake    :     190/-");
                    System.out.println("5. Zero-Shake       :     240/-");
                    if(cur != 1)
                        System.out.println("Press E if you want to close the order");

                    System.out.println("Shake no." + cur);

                    System.out.println("Your choice : ");

                    Scanner shs = new Scanner(System.in);
                    shakeType = shs.nextLine();

                    if(cur == 1 && shakeType.equals("E"))
                    {
                        System.out.println("Please place at least one order");
                        continue;
                    }
                    else if(cur != 1 && shakeType.equals("E"))
                    {
                        for(int i = 0; i<shakes.size(); i++)
                        {
                            int j = i+1;
                            System.out.println("Shake # " + j);
                            shakes.get(i).Print();
                            total_order_price = total_order_price + shakes.get(i).GetOneShakePrice();
                        }
                        System.out.println("Total price of this order = " + total_order_price + "/-");
                        break;
                    }
                    else if(!(shakeType.equals("1") || shakeType.equals("2") || shakeType.equals("3") || shakeType.equals("4") || shakeType.equals("5"))) {
                        System.out.println("Press 1-5");
                        continue;
                    }

                    System.out.println("What kind of milk do you want?");
                    System.out.println("1. Regular Milk");
                    System.out.println("2. Almond-milk (Lactoz-free) (will add 60/- to the base price)");

                    while(true)
                    {
                        System.out.println("Your choice : ");
                        Scanner sm = new Scanner(System.in);
                        milk = sm.nextLine();

                        if(milk.equals("1") || milk.equals("2"))
                            break;
                        else
                        {
                            System.out.println("please press 1 or 2");
                            continue;
                        }
                    }

                    while (true)
                    {
                        System.out.println("   Added-Topping                             :Price");
                        System.out.println("1. Candy                                     :50/-");
                        System.out.println("2. Cookie                                    :40/-");

                        System.out.println("Do you want any topping?");
                        System.out.println("1. Yes 2. No");
                        System.out.println("Your choice: ");
                        Scanner scon = new Scanner(System.in);
                        con = scon.nextLine();

                        if(con.equals("1"))
                        {
                            while(true)
                            {
                                System.out.println("Your topping choice : (press 1 for candy or press 2 for cookie)");
                                Scanner ts = new Scanner(System.in);
                                top = ts.nextLine();

                                if(top.equals("1") || top.equals("2"))
                                {
                                    break;
                                }
                                else
                                {
                                    //System.out.println("Do you want to include something with previous order?");
                                    System.out.println("Press 1 or 2");
                                    continue;
                                }
                            }
                            break;
                        }
                        else if(con.equals("2"))
                        {
                            break;
                        }
                        else
                        {
                            System.out.println("Do you want to include something with previous order?");
                            //System.out.println("Press 1 or 2");
                            continue;
                        }
                    }
                    Shake tempsh = Order_Shake(shakeType, milk, top);
                    shakes.addLast(tempsh);
                    System.out.println("Do you want more shake?");
                    System.out.println("If NO, press E for closing the order");
                    System.out.println("If YES, press any key other than E");

                    Scanner snch = new Scanner(System.in);
                    ch = snch.nextLine();
                    if(ch.equals("E"))
                    {
                        for(int i = 0; i<shakes.size(); i++)
                        {
                            int j = i+1;
                            System.out.println("Shake # " + j);
                            shakes.get(i).Print();
                            total_order_price = total_order_price + shakes.get(i).GetOneShakePrice();
                        }
                        System.out.println("Total price of this order = " + total_order_price + "/-");
                        break;
                    }
                    else
                    {
                        System.out.println("Do you want to include something with previous order?");
                        //System.out.println("Press E if you want to close the order");
                        cur++;
                        continue;
                    }
                }
            }

        }

    }
}
