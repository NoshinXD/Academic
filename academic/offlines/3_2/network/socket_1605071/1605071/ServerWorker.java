import java.io.*;
import java.net.Socket;
import java.nio.file.Files;
import java.util.Date;
import java.util.List;

public class ServerWorker extends Thread {
    Socket socket;
    OutputStream out;
    InputStream in;

    //FileWriter myWriter = null ;
    //PrintWriter myWriter = new PrintWriter("myLog.txt");
    PrintWriter myWriter = new PrintWriter(new FileWriter("myLog.txt", true));

    //String myLink = "localhost:6789/";
    //String myLink = "";

    public ServerWorker(Socket socket) throws IOException {
        this.socket = socket;

        this.out = this.socket.getOutputStream();
        this.in = this.socket.getInputStream();
    }

    public static String readFileData(File file, int fileLength) throws IOException {
        FileInputStream fileIn = null;
        byte[] fileData = new byte[fileLength];

        try {
            fileIn = new FileInputStream(file);
            fileIn.read(fileData);
        } finally {
            if (fileIn != null)
                fileIn.close();
        }

        return String.valueOf(fileData);
    }

    public void run()
    {
        //DataOutputStream ds= new DataOutputStream(this.out);
        //if(inputWithFileName == null)
        //{
            //File f = new File("myLog.txt");

            BufferedReader inbr = new BufferedReader(new InputStreamReader(this.in));
            if(inbr == null) System.out.println("HERE");
            PrintWriter pr = null;
            try {
                //f.createNewFile();
                //myWriter = new FileWriter("myLog.txt");
                pr = new PrintWriter(socket.getOutputStream());
            } catch (IOException e) {
                e.printStackTrace();
            }

            try {
                String input = inbr.readLine();
                //System.out.println("input : " + input);
                //myWriter.append(input);


                //if(input == null) System.out.println("No request found");
                //else
                if(input != null)
                {
                    myWriter.println("HTTP request : " + input);
                    myWriter.println("HTTP response : ");
                    StringBuilder sb = new StringBuilder();

                    //String line;
                    String tempStr = "";
                    myWriter.append("");

                    if(input.startsWith("GET"))
                    {
                        String startcontent = "<html> \n";

                        String middlecontent = "";

                        sb.append(startcontent);
                        sb.append( "<head> \n");
                        sb.append( "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"> \n");
                        sb.append( "<link rel=\"icon\" href=\"data:,\">\n" );
                        sb.append( "</head> \n" );
                        sb.append( "<body> \n" );

                        //middlecontent = middlecontent + "<h1> Welcome to CSE 322 Offline 1</h1>\n";


                        String[] splitStr = input.split(" ");

                        String tempFile = splitStr[1].substring(1);
                        File fileCheck = new File(tempFile);

                        //String[] filecheck = splitStr[1].split("[.]");
                        //int len = filecheck.length;

                        if(fileCheck.exists() && fileCheck.isFile())
                        {
                            pr.write("HTTP/1.1 200 OK\r\n");
                            pr.write("Server: Java HTTP Server: 1.0\r\n");
                            pr.write("Date: " + new Date() + "\r\n");
                            //pr.write("Content-Type: text/html\r\n");
                            //pr.write("Content-Length: " + fileCheck.length() + "\r\n");
                            pr.write("Content-type: application/x-force-download" + "\r\n");
                            pr.write("Content-Length: " + fileCheck.length() + "\r\n");
                            pr.write("\r\n");
                            pr.flush();

                            /*myWriter.append("HTTP/1.1 200 OK\n");
                            myWriter.append("Server: Java HTTP Server: 1.0\r\n");
                            myWriter.append("Date: " + new Date() + "\r\n");
                            myWriter.append("Content-Type: text/html\r\n");
                            myWriter.append("Content-Length: " + fileCheck.length() + "\r\n");
                            myWriter.append("Content-Length: " + fileCheck.length() + "\r\n");
                            myWriter.append("\r\n");*/

                            myWriter.println("HTTP/1.1 200 OK\n");
                            myWriter.println("Server: Java HTTP Server: 1.0\r\n");
                            myWriter.println("Date: " + new Date() + "\r\n");
                            //myWriter.println("Content-Type: text/html\r\n");
                            String mymimeType = Files.probeContentType(fileCheck.toPath());
                            //System.out.println("mimeType : " + mymimeType);
                            myWriter.println("Content-type: " + mymimeType + "\r\n");
                            //myWriter.println("Content-type: application/x-force-download" + "\r\n");
                            myWriter.println("Content-Length: " + fileCheck.length() + "\r\n");
                            myWriter.println("\r\n");

                            byte[] myChunk = new byte[1024];
                            int count = 0;

                            BufferedInputStream newin = new BufferedInputStream(new FileInputStream(fileCheck));

                            while((count = newin.read(myChunk)) > 0)
                            {
                                out.write(myChunk, 0, count);
                                out.flush();
                            }
                        }
                        else if(splitStr[1].equals("/") || (fileCheck.exists() && fileCheck.isDirectory()))
                        {
                            File file;
                            if(splitStr[1].equals("/"))
                            {
                                //found = true;
                                file = new File("root");
                            }
                            else
                            {
                                //found = true;
                                //System.out.println("HERE");
                                String dir = splitStr[1].substring(1);
                                //System.out.println("dir " + dir);
                                file = new File(dir);
                                //System.out.println("File name: " + file.getName());
                            }

                            File[] flist = file.listFiles();
                            middlecontent = middlecontent + "<ul>\n";

                            if(flist!= null)
                            {
                                for(int i=0; i<flist.length; i++)
                                {
                                    if(flist[i].exists())
                                    {
                                        File parent = flist[i].getParentFile();
                                        String dirLink = parent.getName() + "/" + flist[i].getName();
                                        middlecontent = middlecontent + "<li> ";

                                        if(flist[i].isDirectory())
                                        {
                                            middlecontent = middlecontent + "<a style=\"font-weight:bold\" href = " + dirLink + "> " + flist[i].getName() + " </a>";
                                        }
                                        else if(flist[i].isFile())
                                        {
                                            middlecontent = middlecontent + "<a href = " + dirLink + "> " + flist[i].getName() + " </a>";
                                        }

                                        middlecontent = middlecontent + " </li>\n";
                                    }
                                    else
                                    {

                                    }
                                }
                                middlecontent = middlecontent + "</ul>\n";
                                sb.append( middlecontent );

                                String endcontent = "</body> \n";
                                sb.append( endcontent );
                                sb.append( "</html>\n\n" );

                                String content = sb.toString();
                                //System.out.println(content);

                                pr.write("HTTP/1.1 200 OK\r\n");
                                pr.write("Server: Java HTTP Server: 1.0\r\n");
                                pr.write("Date: " + new Date() + "\r\n");
                                pr.write("Content-Type: text/html\r\n");
                                pr.write("Content-Length: " + content.length() + "\r\n");
                                pr.write("\r\n");
                                pr.write(content);
                                pr.flush();

                                /*myWriter.append("HTTP/1.1 200 OK\r\n");
                                myWriter.append("Server: Java HTTP Server: 1.0\r\n");
                                myWriter.append("Date: " + new Date() + "\r\n");
                                myWriter.append("Content-Type: text/html\r\n");
                                myWriter.append("Content-Length: " + content.length() + "\r\n");
                                myWriter.append("\r\n");
                                myWriter.append(content);*/

                                myWriter.println("HTTP/1.1 200 OK\r\n");
                                myWriter.println("Server: Java HTTP Server: 1.0\r\n");
                                myWriter.println("Date: " + new Date() + "\r\n");
                                myWriter.println("Content-Type: text/html\r\n");
                                myWriter.println("Content-Length: " + content.length() + "\r\n");
                                myWriter.println("\r\n");
                                myWriter.println(content);

                                /*tempStr = tempStr + "HTTP/1.1 200 OK\r\n";
                                tempStr = tempStr + "Server: Java HTTP Server: 1.0\r\n";
                                tempStr = tempStr + "Date: " + new Date() + "\r\n";
                                tempStr = tempStr + "Content-Type: text/html\r\n";
                                tempStr = tempStr + "Content-Length: " + content.length() + "\r\n";
                                tempStr = tempStr + "\r\n";
                                tempStr = tempStr + content;*/
                            }
                            else
                            {
                                System.out.println("The list is null");
                            }
                        }
                        else
                        {
                            middlecontent = "";

                            middlecontent = middlecontent + "<h1> 404: Page not found</h1>\n";
                            sb.append(middlecontent);

                            String endcontent = "</body> \n";
                            sb.append( endcontent );
                            sb.append( "</html>\n\n" );

                            String content = sb.toString();

                            System.out.println("HTTP/1.1 404 NOT FOUND\n");
                            pr.write("HTTP/1.1 404 NOT FOUND\r\n");
                            pr.write("Server: Java HTTP Server: 1.0\r\n");
                            pr.write("Date: " + new Date() + "\r\n");
                            pr.write("\r\n");
                            pr.write(content);
                            pr.flush();

                            /*myWriter.append("HTTP/1.1 404 Page not found\r\n");
                            myWriter.append("Server: Java HTTP Server: 1.0\r\n");
                            myWriter.append("Date: " + new Date() + "\r\n");
                            myWriter.append("\r\n");*/

                            myWriter.println("HTTP/1.1 404 NOT FOUND\r\n");
                            myWriter.println("Server: Java HTTP Server: 1.0\r\n");
                            myWriter.println("Date: " + new Date() + "\r\n");
                            myWriter.println("\r\n");
                            myWriter.println(content);

                            /*tempStr = tempStr + "HTTP/1.1 404 Page not found\r\n";
                            tempStr = tempStr + "Server: Java HTTP Server: 1.0\r\n";
                            tempStr = tempStr + "Date: " + new Date() + "\r\n";
                            tempStr = tempStr + "\r\n";*/
                        }
                        //myWriter.close();
                        //logStr(tempStr);
                        myWriter.flush();
                        myWriter.close();
                        socket.close();
                    }

                    else if(input.startsWith("UPLOAD"))
                    {
                        pr.write("OK");
                        pr.write("\r\n");
                        pr.flush();
                        //System.out.println("HERE");

                        String[] splitStr = input.split(" ");
                        String fileName = splitStr[1];

                        //File file = new File("root\\" + fileName);

                        String workingDir = System.getProperty("user.dir");
                        String absoluteFilePath = workingDir + "/root/" + fileName;
                        File file = new File(absoluteFilePath);


                        byte[] myChunk = new byte[1024];
                        int count = 0;

                        //System.out.println("HERE");

                        //InputStream stream = socket.getInputStream();
                        FileOutputStream fos = new FileOutputStream(file);
                        //BufferedInputStream newin = new BufferedInputStream(new FileInputStream(file));

                        while((count = in.read(myChunk)) > 0)
                        {
                            //System.out.println("START");
                            fos.write(myChunk, 0, count);
                            fos.flush();
                        }
                        //System.out.println("END");
                        fos.close();
                        in.close();

                        socket.close();

                    }
                    else if(input.startsWith("NO"))
                    {
                        String[] splitStr = input.split(" ");
                        String fileName = splitStr[1];
                        System.out.println(fileName + " NOT FOUND");
                        socket.close();
                    }

                }

            } catch (IOException e) {
                e.printStackTrace();
            }

        //}
        /*else
        {
            if(inputWithFileName.startsWith("UPLOAD"))
            {
                String[] splitStr = inputWithFileName.split(" ");
                String fileName = splitStr[1];
            }
        }*/

    }
}