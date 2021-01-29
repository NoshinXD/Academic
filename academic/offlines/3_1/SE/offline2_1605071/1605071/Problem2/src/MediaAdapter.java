public class MediaAdapter implements MediaPlayer{
    AdvancedMediaPlayer advancedMusicPlayer;

    public MediaAdapter(String audioType)
    {
        if(audioType.equalsIgnoreCase("mp4"))
        {
            advancedMusicPlayer = new Mp4Player();
        }
        else if(audioType.equalsIgnoreCase("flv"))
        {
            advancedMusicPlayer = new FlvPlayer();
        }
        else if(audioType.equalsIgnoreCase("vlc"))
        {
            advancedMusicPlayer = new VlcPlayer();
        }
    }

    @Override
    public void play(String audioType, String fileName, String fileSize, String duration) {
        if(audioType.equalsIgnoreCase("mp4"))
        {
            advancedMusicPlayer.playMp4(fileName, fileSize, duration);
        }
        else if(audioType.equalsIgnoreCase("flv"))
        {
            advancedMusicPlayer.playFlv(fileName, fileSize, duration);
        }
        if(audioType.equalsIgnoreCase("vlc"))
        {
            advancedMusicPlayer.playVlc(fileName, fileSize, duration);
        }
    }
}
