import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

//http -v 127.0.0.1:6789

public class myServer {
    static final int PORT = 6789;
    //static Vector<myWorkerV3> array= new Vector<myWorkerV3>();

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        ServerSocket welcomeSocket = new ServerSocket(PORT);
        System.out.println("Server started.\nListening for connections on port : " + PORT + " ...\n");

        File file = new File("myLog.txt");
        if(file.exists()) file.delete();

        while(true) {
            Socket socket = welcomeSocket.accept();

            // open thread
            Thread myworker = new ServerWorker(socket);
            myworker.start();
        }

    }
}
