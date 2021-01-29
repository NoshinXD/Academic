import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class myClient {
    static final int PORT = 6789;

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        //int tid = 0;
        int socketid = 0;
        while(true) {
            //socketid++;
            //tid++;
            //System.out.println("Socket id: " + socketid);
            Socket socket = new Socket("localhost", PORT);
            //System.out.println("Connection established");

            System.out.println("Please enter a file name : ");
            Scanner sc = new Scanner(System.in);
            String fileName = sc.next();

            // open thread
            //tid++;
            //System.out.println("tid: " + tid);
            Thread clientworker = new ClientWorker(socket, fileName);
            clientworker.start();
        }

    }
}
