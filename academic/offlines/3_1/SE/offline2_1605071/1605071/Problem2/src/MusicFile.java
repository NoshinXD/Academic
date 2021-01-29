public class MusicFile {
    String name;
    String type;
    String size;
    String duration;

    public MusicFile(String name, String type, String size, String duration) {
        this.name = name;
        this.type = type;
        this.size = size;
        this.duration = duration;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setSize(String size) {
        this.size = size;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public String getName() {
        return name;
    }

    public String getType() {
        return type;
    }

    public String getSize() {
        return size;
    }

    public String getDuration() {
        return duration;
    }
}
