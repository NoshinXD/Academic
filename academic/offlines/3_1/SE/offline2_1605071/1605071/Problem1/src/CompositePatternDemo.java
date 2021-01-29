import java.util.*;

public class CompositePatternDemo {
    public static void main(String[] args) {
        List<Item> drives = new ArrayList<Item>();
        List<Item> folders = new ArrayList<Item>();
        while (true) {
            System.out.println("1. Create drive");
            System.out.println("2. Add a folder");
            System.out.println("3. Add a file");
            System.out.println("4. Remove a folder");
            System.out.println("5. Remove a file");
            System.out.println("6. Show details of an item");
            System.out.println("7. Show list under an item");


            Scanner sc = new Scanner(System.in);
            int choice = sc.nextInt();

            if (choice == 1)
            {
                System.out.println("Enter name : ");
                Scanner scname = new Scanner(System.in);
                String name = scname.nextLine();
                String type = "Drive";
                String dir = name;

                Item drive = new Drive(name, type, dir);
                drives.add(drive);
            }
            else if (choice == 2) {
                System.out.println("Enter name : ");
                Scanner scname = new Scanner(System.in);
                String name = scname.nextLine();
                String type = "Folder";

                System.out.println("Enter directory : ");
                Scanner scdir = new Scanner(System.in);
                String dir = scdir.nextLine();

                Item folder = new Folder(name, type, dir);

                //String[] arrOfStr = dir.split(">");
                String[] arrOfStr = dir.split("\\\\");

                int len = arrOfStr.length;

                String temp = arrOfStr[len - 2];

                int index = -1;

                if (len - 2 == 0)//folder is under drive
                {
                    for (int i = 0; i < drives.size(); i++) {
                        if (drives.get(i).getName().equalsIgnoreCase(temp)) {
                            index = i;
                        }
                    }


                    if (index != -1) {
                        drives.get(index).add(folder);
                        folders.add(folder);
                    }
                    else {
                        System.out.println("Drive not found");
                    }
                } else//folder is under folder
                {
                    for (int i = 0; i < folders.size(); i++) {
                        if (folders.get(i).getName().equalsIgnoreCase(temp)) {
                            index = i;
                        }
                    }

                    /*int missing_check = 0;

                    for(int j=1; j<arrOfStr.length-1; j++)
                    {
                        for(int i=0; i<folders.size(); i++){
                            if(folders.get(i).getName().equalsIgnoreCase(arrOfStr[j]))
                            {
                                missing_check++;
                            }
                        }
                    }*/


                    //if (index != -1 && missing_check == arrOfStr.length-2) {
                    if (index != -1) {
                        folders.get(index).add(folder);
                        folders.add(folder);
                    }
                    else {
                        System.out.println("Folder not found");
                    }
                }

            } else if (choice == 3) {
                System.out.println("Enter name : ");
                Scanner scname = new Scanner(System.in);
                String name = scname.nextLine();
                String type = "File";

                System.out.println("Enter directory : ");
                Scanner scdir = new Scanner(System.in);
                String dir = scdir.nextLine();

                Item file = new File(name, type, dir);

                //String[] arrOfStr = dir.split(">");
                String[] arrOfStr = dir.split("\\\\");

                int len = arrOfStr.length;

                String temp = arrOfStr[len - 2];//ok

                int index = -1;

                if (len - 2 == 0) {//drive parent
                    for (int i = 0; i < drives.size(); i++) {
                        if (drives.get(i).getName().equalsIgnoreCase(temp)) {
                            index = i;
                        }
                    }

                    if (index != -1) {
                        drives.get(index).add(file);
                    }
                    else {
                        System.out.println("Drive not found");
                    }
                }//ok
                else {//folder parent
                    for (int i = 0; i < folders.size(); i++) {
                        if (folders.get(i).getName().equalsIgnoreCase(temp)) {
                            index = i;
                        }
                    }

                    /*int missing_check = 0;

                    for(int j=1; j<arrOfStr.length-1; j++)
                    {
                        for(int i=0; i<folders.size(); i++){
                            if(folders.get(i).getName().equalsIgnoreCase(arrOfStr[j]))
                            {
                                missing_check++;
                            }
                        }
                    }*/


                    //if (index != -1 && missing_check == arrOfStr.length-2) {
                    if (index != -1) {
                        folders.get(index).add(file);
                    } else {
                        System.out.println("Folder not found");
                    }
                }
            } else if (choice == 4) {
                /*for(int i=0; i<folders.size(); i++)
                {
                    System.out.println(folders.get(i).getName());
                }*/

                System.out.println("Enter name : ");
                Scanner scname = new Scanner(System.in);
                String name = scname.nextLine();

                String type = "Folder";

                System.out.println("Enter directory : ");
                Scanner scdir = new Scanner(System.in);
                String dir = scdir.nextLine();

                Item folder = new Folder(name, type, dir);

                //String[] arrOfStr = dir.split(">");
                String[] arrOfStr = dir.split("\\\\");

                int len = arrOfStr.length;

                String parentName = arrOfStr[len-2];

                int index = -1;
                Item parent = null;

                int ind = -1;
                Item self = null;

                if(len-2 == 0)//parent drive
                {
                    for (int i = 0; i < drives.size(); i++) {
                        if (drives.get(i).getName().equalsIgnoreCase(parentName)) {
                            index = i;
                            parent = drives.get(i);
                            break;
                        }
                    }
                    if (index != -1) {
                        parent.remove(folder);
                        //folders.get(index+1).remove(folder);
                        folders.remove(index+1);
                    } else {
                        System.out.println("Parent Drive not found");
                    }
                }
                else//parent folder
                {
                    for(int i=0; i<folders.size(); i++)
                    {
                        if(folders.get(i).getName().equalsIgnoreCase(parentName))
                        {
                            index = i;//indexe ache parent
                            parent = folders.get(i);
                            break;
                        }
                    }

                    for(int i=0; i<folders.size(); i++)
                    {
                        if(folders.get(i).getName().equalsIgnoreCase(name))
                        {
                            ind = i;//indexe ache delete kora lagbe je take
                            self = folders.get(i);
                            break;
                        }
                    }

                    if(index != -1)
                    {
                        //System.out.println("HERE1");
                        List<Item> faltuList = new ArrayList<Item>();
                        List<Item> tempFolders = folders.get(ind).uradhuraList(faltuList);
                        parent.remove(folder);
                        //System.out.println(folder.getName());
                        //folders.remove(index+1);
                        for(int i=0; i<tempFolders.size(); i++)
                        {
                            for(int j=0; j<folders.size(); j++)
                            {
                                if(tempFolders.get(i).getName().equalsIgnoreCase(folders.get(j).getName()))
                                {
                                    //System.out.println(folders.get(j).getName());
                                    folders.remove(j);
                                }
                            }
                        }

                        //System.out.println(folders.get(ind).getName());
                        folders.remove(ind);

                        /*System.out.println("Remaining");

                        for(int i=0; i<folders.size(); i++)
                        {
                            System.out.println(folders.get(i).getName());
                        }*/

                        //System.out.println("HERE2");
                        /*for(int i=0; i<tempFolders.size(); i++)
                        {
                            //System.out.println("HERE3");
                            System.out.println(tempFolders.get(i).getName());
                        }*/
                    }
                    else
                    {
                        System.out.println("Parent Folder not found");
                    }
                }
            }
            else if(choice == 5)
            {
                System.out.println("Enter name : ");
                Scanner scname = new Scanner(System.in);
                String name = scname.nextLine();

                String type = "File";

                System.out.println("Enter directory : ");
                Scanner scdir = new Scanner(System.in);
                String dir = scdir.nextLine();

                Item file = new File(name, type, dir);

                //String[] arrOfStr = dir.split(">");
                String[] arrOfStr = dir.split("\\\\");

                int len = arrOfStr.length;

                String parentName = arrOfStr[len-2];

                int index = -1;
                Item parent = null;

                if(len-2 == 0)//parent drive
                {
                    for (int i = 0; i < drives.size(); i++) {
                        if (drives.get(i).getName().equalsIgnoreCase(parentName)) {
                            index = i;
                            parent = drives.get(i);
                            break;
                        }
                    }
                    if (index != -1) {
                        parent.remove(file);
                    } else {
                        System.out.println("Parent Drive not found");
                    }
                }
                else//parent folder
                {
                    for(int i=0; i<folders.size(); i++)
                    {
                        if(folders.get(i).getName().equalsIgnoreCase(parentName))
                        {
                            index = i;
                            parent = folders.get(i);
                            break;
                        }
                    }
                    if(index != -1)
                    {
                        parent.remove(file);
                    }
                    else
                    {
                        System.out.println("Parent Folder not found");
                    }
                }
            }
            else if(choice == 6)
            {
                System.out.println("Enter name : ");
                Scanner scname = new Scanner(System.in);
                String name = scname.nextLine();

                System.out.println("Enter type : ");
                Scanner sctype = new Scanner(System.in);
                String type = sctype.nextLine();

                Item item = null;
                int index = -1;

                if(type.equalsIgnoreCase("Drive"))
                {
                    for (int i = 0; i < drives.size(); i++) {
                        if (drives.get(i).getName().equalsIgnoreCase(name)) {
                            index = i;
                        }
                    }
                    if(index != -1)
                    {
                        drives.get(index).details();
                    }
                    else
                    {
                        System.out.println("Drive not found");
                    }
                    int count = 0;
                    System.out.println("Component count : " + drives.get(index).getTempCount(count));
                }
                else if(type.equalsIgnoreCase("Folder"))
                {
                    for (int i = 0; i < folders.size(); i++) {
                        if (folders.get(i).getName().equalsIgnoreCase(name)) {
                            index = i;
                        }
                    }
                    if(index != -1)
                    {
                        folders.get(index).details();
                    }
                    else
                    {
                        System.out.println("Folder not found");
                    }
                    int count = 0;
                    System.out.println("Component count : " + folders.get(index).getTempCount(count));
                }
                else if(type.equalsIgnoreCase("File"))
                {

                }
            }
            else if (choice == 7) {
                System.out.println("Enter name : ");
                Scanner scname = new Scanner(System.in);
                String name = scname.nextLine();

                System.out.println("Enter type : ");
                Scanner sctype = new Scanner(System.in);
                String type = sctype.nextLine();

                Item item = null;
                int index = -1;

                if (type.equalsIgnoreCase("Drive")) {
                    for (int i = 0; i < drives.size(); i++) {
                        if (drives.get(i).getName().equalsIgnoreCase(name)) {
                            index = i;
                        }
                    }
                    if (index != -1) {
                        System.out.println("Name = " + drives.get(index).getName());
                        System.out.println("Type = " + drives.get(index).getType());
                        System.out.println("directory = " + drives.get(index).getDir());
                        drives.get(index).list();
                        //System.out.println("Component count : " + drives.get(index).getComponent());
                        int count = 0;
                        System.out.println("Component count : " + drives.get(index).getTempCount(count));
                    } else {
                        System.out.println("Drive not found");
                    }
                } else if (type.equalsIgnoreCase("Folder")) {
                    for (int i = 0; i < folders.size(); i++) {
                        if (folders.get(i).getName().equalsIgnoreCase(name)) {
                            index = i;
                        }
                    }
                    if (index != -1) {
                        System.out.println("Name = " + folders.get(index).getName());
                        System.out.println("Type = " + folders.get(index).getType());
                        System.out.println("directory = " + folders.get(index).getDir());
                        folders.get(index).list();
                        //System.out.println("Component count : " + drives.get(index).getComponent());
                        int count = 0;
                        System.out.println("Component count : " + folders.get(index).getTempCount(count));
                    } else {
                        System.out.println("Folder not found");
                    }
                }
            }
            else
            {
                System.out.println("Press between 1-7");
            }
        }
    }
}
