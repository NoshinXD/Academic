import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.Map;
import java.util.Random;

//Work needed
public class Client {

    public static void main(String[] args) throws InterruptedException {
        NetworkUtility networkUtility = new NetworkUtility("127.0.0.1", 4444);
        System.out.println("Connected to server");
        /**
         * Tasks
         */
        
        /*
        1. Receive EndDevice configuration from server
        2. Receive active client list from server
        3. for(int i=0;i<100;i++)
        4. {
        5.      Generate a random message
        6.      Assign a random receiver from active client list
        7.      if(i==20)
        8.      {
        9.            Send the message and recipient IP address to server and a special request "SHOW_ROUTE"
        10.           Display routing path, hop count and routing table of each router [You need to receive
                            all the required info from the server in response to "SHOW_ROUTE" request]
        11.     }
        12.     else
        13.     {
        14.           Simply send the message and recipient IP address to server.
        15.     }
        16.     If server can successfully send the message, client will get an acknowledgement along with hop count
                    Otherwise, client will get a failure message [dropped packet]
        17. }
        18. Report average number of hops and drop rate
        */
        int clientCount = (int) networkUtility.read();
        System.out.println(clientCount);
        EndDevice endDevice = (EndDevice) networkUtility.read(); // EndDevice configuration
        System.out.println("Device : " + endDevice.getIpAddress() + "::::" + endDevice.getGateway());

        //ArrayList<EndDevice> endDevices = (ArrayList<EndDevice>) networkUtility.read(); //active client list

        Random random = new Random();
        String alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789";

        int length = 4;
        int dropCount = 0;
        int deliverCount = 0;
        int totalHopCount = 0;
        for(int i=0;i<100;i++)
        {
            StringBuilder sb = new StringBuilder();
            for(int j = 0; j < length; j++) {
                int index = random.nextInt(alphabet.length());
                char randomChar = alphabet.charAt(index);
                sb.append(randomChar);
            }
            String msg = sb.toString(); //random msg
            //System.out.println(msg);

            //int receiverIndex = random.nextInt(endDevices.size()); //random receiver
            //IPAddress srcIp = endDevice.getIpAddress();

            if(i == 20)
            {
                String specialRequ = "SHOW_ROUTE";
                Packet p = new Packet(msg, specialRequ, null, null);
                networkUtility.write(p);

                int srcRId_get = (int) networkUtility.read();
                int destRId_get = (int) networkUtility.read();
                System.out.println("SRC: " + srcRId_get);
                System.out.println("DEST: " + destRId_get);
                ArrayList<Integer> route = (ArrayList<Integer>) networkUtility.read();

                Map<Integer, ArrayList<RoutingTableEntry>> routingTableMap = (Map<Integer, ArrayList<RoutingTableEntry>>) networkUtility.read();

                for(int a=0; a<route.size(); a++)
                {
                    System.out.println("---------------------------------");
                    System.out.println("RouterId: " + route.get(a));
                    ArrayList<RoutingTableEntry> tempRoutingTable = routingTableMap.get(route.get(a));

                    System.out.println("Routing table: ");
                    for(int b=0; b<tempRoutingTable.size(); b++)
                    {
                        System.out.println(tempRoutingTable.get(b).getRouterId() + " ; " + tempRoutingTable.get(b).getDistance() + " ; " + tempRoutingTable.get(b).getGatewayRouterId());
                    }
                    System.out.println("---------------------------------");
                }
            }
            else
            {
                Packet p = new Packet(msg, "", null, null);
                networkUtility.write(p);
            }
            String confirmMsg = (String) networkUtility.read();
            int hopCount = (int) networkUtility.read();
            if(confirmMsg.equals("delivered"))
            {
                System.out.print(confirmMsg + " " + i);
                System.out.println(" ; Hop_count: " + hopCount);
                //deliverCount++;
                totalHopCount = totalHopCount + hopCount;
            }
            else
            {
                dropCount++;
                System.out.println(confirmMsg + " " + i);
            }
        }
        System.out.println();
        System.out.println("packet pathano shesh");
        System.out.println("Drop count: " + dropCount);
        deliverCount = 100 - dropCount;
        double avgHopCount = 0.0;
        if(deliverCount > 0) avgHopCount = (totalHopCount * 1.0) / deliverCount;
        System.out.println("Deliver count: " + deliverCount);
        System.out.println("avg hop count: " + avgHopCount);

        /*if(clientCount == 2)
        {
            while (true);
        }*/

        //networkUtility.write("byebye");
    }
}
