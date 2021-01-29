import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class AdapterPatternDemo {
    public static void main(String[] args) {
        List<MusicFile> playList = new ArrayList<MusicFile>();

        while(true)
        {
            System.out.println("1. Add a new playlist");
            System.out.println("2. Add file to current playlist");
            //System.out.println("3. Add multiple files to current playlist");

            Scanner sc = new Scanner(System.in);
            int choice = sc.nextInt();

            if(choice == 1)
            {
                double total_dura = 0;

                for(int i=0; i<playList.size(); i++)
                {
                    //String[] duration = input_duras.get(i).split(":");
                    String[] duration = playList.get(i).duration.split(":");
                    String min = duration[0];
                    double m = Double.parseDouble(min);

                    String sec = duration[1];
                    double s = Double.parseDouble(sec);

                    total_dura = total_dura + ((m*60)+s);
                }
                total_dura = total_dura/60;
                System.out.println("Total duration : " + total_dura);

                System.out.println("Enter elapsed time : (in min:sec format)");
                Scanner scel = new Scanner(System.in);
                String elapsedTime = scel.nextLine();

                String[] elapsed = elapsedTime.split(":");

                String elmin = elapsed[0];
                double elm = Double.parseDouble(elmin);
                String elsec = elapsed[1];
                double els = Double.parseDouble(elsec);

                double eldur = ((elm*60)+els)/60;
                System.out.println("Elapsed time :" + eldur);

                if(eldur <= total_dura)
                {
                    System.out.println("You can not add a playlist now");
                }
                else
                {
                    int count = 0;
                    if(count == 0)
                    {
                        playList = new ArrayList<MusicFile>();
                        total_dura = 0;

                        count++;
                    }
                    while(true)
                    {
                        System.out.println("Enter song name : ");
                        System.out.println("(If you are finished adding, type 'BREAK')");
                        Scanner scname = new Scanner(System.in);
                        String file = scname.nextLine();

                        if(file.equalsIgnoreCase("BREAK"))
                        {
                            for(int i=0; i<playList.size(); i++)
                            {
                                AudioPlayer audioPlayer = new AudioPlayer();
                                audioPlayer.play(playList.get(i).type, playList.get(i).name, playList.get(i).size, playList.get(i).duration);
                            }

                            break;
                        }
                        String[] temp = file.split("\\.");

                        System.out.println("Enter song size : ");
                        Scanner scsize = new Scanner(System.in);
                        String size = scsize.nextLine();

                        System.out.println("Enter duration: ");
                        Scanner scdura = new Scanner(System.in);
                        String dura = scdura.nextLine();

                        MusicFile tempFile = new MusicFile(temp[0], temp[1], size, dura);

                        //System.out.println(tempFile.type);

                        playList.add(tempFile);
                    }
                }
            }
            else if(choice == 2)
            {
                System.out.println("Enter song name : ");
                Scanner scname = new Scanner(System.in);
                String file = scname.nextLine();

                String[] temp = file.split("\\.");

                System.out.println("Enter song size : ");
                Scanner scsize = new Scanner(System.in);
                String size = scsize.nextLine();

                System.out.println("Enter duration: ");
                Scanner scdura = new Scanner(System.in);
                String dura = scdura.nextLine();

                MusicFile tempFile = new MusicFile(temp[0], temp[1], size, dura);
                playList.add(tempFile);

                for(int i=0; i<playList.size(); i++)
                {
                    AudioPlayer audioPlayer = new AudioPlayer();
                    audioPlayer.play(playList.get(i).type, playList.get(i).name, playList.get(i).size, playList.get(i).duration);
                }
            }
            else
            {
                System.out.println("Please press 1 or 2");
                continue;
            }
        }
    }
}
