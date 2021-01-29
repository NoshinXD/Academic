import java.io.*;
import java.net.Socket;

public class ClientWorker extends Thread {
    Socket socket;
    OutputStream out;
    InputStream in;
    String fileName;

    public ClientWorker(Socket socket, String fileName) throws IOException {
        this.socket = socket;
        this.fileName = fileName;

        this.out = this.socket.getOutputStream();
        this.in = this.socket.getInputStream();
    }

    public void run()
    {
        PrintWriter pr = null;

        try {
            pr = new PrintWriter(socket.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }

        try
        {
            File file = new File(fileName);

            if(file.exists())
            {
                String input = "UPLOAD " + fileName;
                pr.write(input);
                pr.write("\r\n");
                pr.flush();

                BufferedReader inbr = new BufferedReader(new InputStreamReader(this.in));

                String gotit = null;
                if(inbr == null) System.out.println("HERE");
                else
                {
                    gotit = inbr.readLine();
                    //System.out.println("Server said: " + gotit);
                }

                if(gotit.equals("OK"))
                {
                    byte[] myChunk = new byte[1024];
                    int count = 0;

                    BufferedInputStream newin = new BufferedInputStream(new FileInputStream(file));
                    //FileInputStream fis = new FileInputStream(file);

                    while((count = newin.read(myChunk)) > 0)
                    {
                        //System.out.println("START");
                        out.write(myChunk, 0, count);
                        out.flush();
                    }
                    //System.out.println("END");
                    newin.close();
                    out.close();
                    socket.close();
                }
            }
            else
            {
                System.out.println(fileName + " NOT FOUND");
                String input = "NO " + fileName;
                pr.write(input);
                pr.write("\r\n");
                pr.flush();
                socket.close();
            }

        }catch (IOException e) {
            e.printStackTrace();
        }

    }

}
