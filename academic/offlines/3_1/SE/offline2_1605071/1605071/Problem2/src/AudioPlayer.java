public class AudioPlayer implements MediaPlayer{
    MediaAdapter mediaAdapter;

    @Override
    public void play(String audioType, String fileName, String fileSize, String duration) {
        if(audioType.equalsIgnoreCase("mp3"))
        {
            System.out.println("Playing mp3 file. Name: " + fileName + " , Size : " + fileSize + " , Duration : " + duration);
        }
        else if(audioType.equalsIgnoreCase("mp4") || audioType.equalsIgnoreCase("flv") || audioType.equalsIgnoreCase("vlc"))
        {
            mediaAdapter = new MediaAdapter((audioType));
            mediaAdapter.play(audioType, fileName, fileSize, duration);
        }
        else
        {
            System.out.println("invalid media. " + audioType + " format not supported");
        }
    }
}
