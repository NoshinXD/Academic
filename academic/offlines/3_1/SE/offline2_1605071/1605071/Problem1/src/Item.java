import java.util.List;

public interface Item {
    public String getName();
    public String getType();
    //public void setDir(String dir);
    public String getDir();
    public void list();
    public void details();
    public void add(Item item);
    public void remove(Item item);
    //public void remove_name(String name);
    public List<Item> getList();
    public List<Item> uradhuraList(List<Item> faltuList);
    //public Item getFolder(int i);
    public Item getFile(int i);
    //public Item getChainFolder(String name);
    //public int getComponent();
    public int getTempCount(int count);//works
}
