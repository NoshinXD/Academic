import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Drive implements Item {
    private String name, type, dir;
    //private int count, tempCount = 0;

    public Drive(String name, String type, String dir) {
        this.name = name;
        this.type = type;
        this.dir = dir;
    }

    List<Item> items = new ArrayList<Item>();
    //List<Item> faltuList = new ArrayList<Item>();

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getType() {
        type = "Drive";
        return type;
    }

    /*@Override
    public void setDir(String dir) {
        this.dir = dir;
    }*/

    @Override
    public String getDir() {
        return dir;
    }

    @Override
    public void list() {
        System.out.println(getName() + " Begin =============");
        //System.out.println("Name = " + getName());
        //System.out.println("Type = " + getType());
        //System.out.println("Directory = " + getDir());

        for(int i=0; i<items.size(); i++)
        {
            System.out.println("Name = " + items.get(i).getName());
            System.out.println("Type = " + items.get(i).getType());
            //if(items.get(i).getType().equalsIgnoreCase("File")) count++;
            System.out.println("Directory = " + items.get(i).getDir());
            items.get(i).list();
        }
        System.out.println("============= " + getName() + " end");
    }

    @Override
    public List<Item> uradhuraList(List<Item> faltuList) {

        for(int i=0; i<items.size(); i++)
        {
            faltuList.add(items.get(i));
            items.get(i).uradhuraList(faltuList);
        }

        return faltuList;
    }

    @Override
    public void details() {
        System.out.println("=============");
        System.out.println("Name = " + getName());
        System.out.println("Type = " + getType());
        System.out.println("Directory = " + getDir());
        System.out.println("=============");

    }

    @Override
    public void add(Item item) {
        items.add(item);
    }

    @Override
    public void remove(Item item) {
        int index = -1;

        for(int i=0; i<items.size(); i++)
        {
            if(items.get(i).getName().equalsIgnoreCase(item.getName())
                    && items.get(i).getType().equalsIgnoreCase(item.getType())
                    && items.get(i).getDir().equalsIgnoreCase(item.getDir()))
            {
                index = i;
                break;
            }
        }
        if(index != -1)
        {
            for(int j=index; j<items.size(); j++)
            {
                Item temp = items.get(j);
                items.remove(temp);
            }
        }
        else
        {
            System.out.println("Required item not found");
        }

    }

    /*@Override
    public void remove_name(String name) {
        int index = 0;
        for(int i=0; i<items.size(); i++)
        {
            String tempName = items.get(i).getName();
            if(tempName.equalsIgnoreCase(name))
            {
                index = items.indexOf(items.get(i));
            }
            else
            {
                index = -1;
            }
        }
        if(index != -1)
        {
            for(int j=index; j<items.size(); j++)
            {
                items.remove(j);
            }
        }
        else
        {
            System.out.println("Not found");
        }
    }*/

    /*@Override
    public Item getFolder(int i) {
        return items.get(i);
    }*/

    /*@Override
    public Item getChainFolder(String name) {
        Item tempFolder = null;
        for(int i=0; i<items.size(); i++)
        {
            if(items.get(i).getName().equalsIgnoreCase(name))
            {
                tempFolder = items.get(i);
                break;
            }
            else
            {
                items.get(i).getChainFolder(name);
            }
        }
        if(tempFolder == null)
        {
            System.out.println("Folder not found");
        }
        return tempFolder;
    }*/

    @Override
    public Item getFile(int i) {
        if(items.get(i).getType().equalsIgnoreCase("File"))
            return items.get(i);
        else
        {
            return null;
        }
    }

    @Override
    public List<Item> getList() {
        return items;
    }

    /*@Override
    public int getComponent() {
        for(int i=0; i<items.size(); i++)
        {
            if(items.get(i).getType().equalsIgnoreCase("File"))
            {
                //count++;
            }
            else
            {
                //tempCount = tempCount + items.get(i).getComponent();
                //count = tempCount;
                //tempCount = 0;
                System.out.println(items.get(i).getName());
                System.out.println(items.get(i).getComponent());
                //count = count + items.get(i).getComponent();
            }
            //count = count + items.get(i).getComponent();
        }

        //return count;
        return 0;
    }*/

    @Override
    public int getTempCount(int count) {
        for(int i=0; i<items.size(); i++)
        {
            if(items.get(i).getType().equalsIgnoreCase("File")) count++;
            else
            {
                int tempCount = 0;
                count = count + items.get(i).getTempCount(tempCount);
            }
        }
        return count;
    }
}
