public class Mp4Player implements AdvancedMediaPlayer {
    @Override
    public void playMp4(String fileName, String fileSize, String duration) {
        System.out.println("Playing mp4 file. Name: " + fileName + " , Size : " + fileSize + " , Duration : " + duration);
    }

    @Override
    public void playFlv(String fileName, String fileSize, String duration) {

    }

    @Override
    public void playVlc(String fileName, String fileSize, String duration) {

    }
}
