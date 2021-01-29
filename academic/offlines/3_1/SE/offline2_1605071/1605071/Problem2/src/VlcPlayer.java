public class VlcPlayer implements AdvancedMediaPlayer{
    @Override
    public void playMp4(String fileName, String fileSize, String duration) {

    }

    @Override
    public void playFlv(String fileName, String fileSize, String duration) {

    }

    @Override
    public void playVlc(String fileName, String fileSize, String duration) {
        System.out.println("Playing vlc file. Name: " + fileName + " , Size : " + fileSize + " , Duration : " + duration);
    }
}
