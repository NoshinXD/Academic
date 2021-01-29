import java.util.ArrayList;
import java.util.List;

public class File implements Item {
    private String name, type, dir;

    public File(String name, String type, String dir) {
        this.name = name;
        this.type = type;
        this.dir = dir;
    }

    //List<Item> items = new ArrayList<Item>();

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getType() {
        type = "File";
        //count++;
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
        //lagbe na
    }

    @Override
    public void details() {
        System.out.println("===========");
        System.out.println("Name : " + getName());
        System.out.println("Type : " + getType());
        System.out.println("Directory : " + getDir());
        System.out.println("===========");
    }

    @Override
    public List<Item> uradhuraList(List<Item> faltuList) {
        //lagbe na
        return null;
    }

    @Override
    public void add(Item item) {
        //lagbe na
    }

    @Override
    public void remove(Item item) {
        //lagbe na
    }

    /*@Override
    public void remove_name(String name) {
        //lagbe na
    }*/

    /*@Override
    public Item getFolder(int i) {
        //lagbe na
        return null;
    }*/

    /*@Override
    public Item getChainFolder(String name) {
        //lagbe na
        return null;
    }*/

    @Override
    public Item getFile(int i) {
        //lagbe na
        return null;
    }

    @Override
    public List<Item> getList() {
        return null;
    }

    /*@Override
    public int getComponent() {
        //count++;
        return count;
    }*/

    @Override
    public int getTempCount(int count) {
        //lagbe na
        return 0;
    }
}
