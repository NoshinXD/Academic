

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class ServerThread implements Runnable {
    //int count = 1;
    NetworkUtility networkUtility;
    EndDevice endDevice;
    int srcRId_send = -1;
    int destRId_send = -1;

    //ArrayList<ArrayList<RoutingTableEntry> > routingTableList = new ArrayList<ArrayList<RoutingTableEntry> >();
    ArrayList<Integer> globalRoute;
    Map<Integer, ArrayList<RoutingTableEntry>> routingTableMap = new HashMap<>();
    Boolean enableRoutingTableList = false;

    ServerThread(NetworkUtility networkUtility, EndDevice endDevice) {
        this.networkUtility = networkUtility;
        this.endDevice = endDevice;
        System.out.println("Server Ready for client " + NetworkLayerServer.clientCount);
        NetworkLayerServer.clientCount++;
        new Thread(this).start();
    }

    @Override
    public void run() {
        /**
         * Synchronize actions with client.
         */

        /*
        Tasks:
        1. Upon receiving a packet and recipient, call deliverPacket(packet)
        2. If the packet contains "SHOW_ROUTE" request, then fetch the required information
                and send back to client
        3. Either send acknowledgement with number of hops or send failure message back to client
        */
        networkUtility.write(NetworkLayerServer.clientCount);
        networkUtility.write(endDevice);

        IPAddress srcIP = endDevice.getIpAddress();

        //networkUtility.write(NetworkLayerServer.endDevices);

        Random random = new Random();

        for(int i=0; i<100; i++)
        {
            Packet p = (Packet) networkUtility.read();

            IPAddress destIP;
            while(true)
            {
                int receiverIndex = random.nextInt(NetworkLayerServer.endDevices.size());

                destIP = NetworkLayerServer.endDevices.get(receiverIndex).getIpAddress();

                if(destIP.equals(srcIP) == false)
                {
                    break;
                }
            }
            //System.out.println("while loop break");
            p.setSourceIP(srcIP);
            p.setDestinationIP(destIP);
            //System.out.println("packet: " + p.getMessage() + " -- " + p.getSpecialMessage() + " -- " + p.getSourceIP() + " -- " + p.getDestinationIP());
            if(p.getSpecialMessage().equals("SHOW_ROUTE"))
            {
                enableRoutingTableList = true;
            }

            Boolean isDelivered = deliverPacket(p);

            if(p.getSpecialMessage().equals("SHOW_ROUTE"))
            {
                networkUtility.write(srcRId_send);
                networkUtility.write(destRId_send);
                networkUtility.write(globalRoute);
                networkUtility.write(routingTableMap);
            }

            String confirmMsg = "";
            int hopCount = -1;
            if(isDelivered == true)
            {
                confirmMsg = "delivered";
                hopCount = globalRoute.size();

            }
            else
            {
                confirmMsg = "dropped packet";
            }
            networkUtility.write(confirmMsg);
            networkUtility.write(hopCount);

            //System.out.println("isDelivered set " + i);
        }


        /*String byemsg = (String) networkUtility.read();
        if(byemsg.equals("byebye"))
        {
            IPAddress ip = endDevice.getIpAddress();

            EndDevice removing_device = NetworkLayerServer.endDeviceMap.get(ip);
            NetworkLayerServer.endDeviceMap.remove(ip);
            NetworkLayerServer.endDevices.remove(removing_device);
        }*/
    }

    public void makeTempRoutingTableMap(int reqRId)
    {
        ArrayList<RoutingTableEntry> tempRoutingTable = NetworkLayerServer.routerMap.get(reqRId).getRoutingTable();

        ArrayList<RoutingTableEntry> pushRoutingTable = new ArrayList<RoutingTableEntry>();

        for(int i=0; i<tempRoutingTable.size(); i++)
        {
            int tempRId = tempRoutingTable.get(i).getRouterId();
            double tempDist = tempRoutingTable.get(i).getDistance();
            int tempGateway = tempRoutingTable.get(i).getGatewayRouterId();

            RoutingTableEntry tempEntry = new RoutingTableEntry(tempRId, tempDist, tempGateway);

            pushRoutingTable.add(tempEntry);
        }

        routingTableMap.put(reqRId, pushRoutingTable);
    }

    /*public ArrayList<Integer> getRoute(int srcRId, int destRId) //works
    {
        Router srcRouter = NetworkLayerServer.routerMap.get(srcRId);

        ArrayList<Integer> route = new ArrayList<Integer>();
        route.add(srcRId);
        makeTempRoutingTableMap(srcRId);
        ArrayList<RoutingTableEntry> routingTable = srcRouter.getRoutingTable();

        while(true)
        {
            int nextHop = routingTable.get(destRId-1).getGatewayRouterId();
            if(nextHop == -1)
            {
                break;
            }
            Router tempRouter = NetworkLayerServer.routerMap.get(nextHop);
            route.add(nextHop);
            makeTempRoutingTableMap(nextHop);
            routingTable = tempRouter.getRoutingTable();
            if(nextHop == destRId)
            {
                break;
            }

            //Router tempRouter = NetworkLayerServer.routerMap.get(nextHop);
            //routingTable = tempRouter.getRoutingTable();
            srcRId = nextHop;
        }

        return route;
    }*/

    public ArrayList<Integer> getRoute_withState(int srcRId, int destRId)
    {
        Router srcRouter = NetworkLayerServer.routerMap.get(srcRId);

        ArrayList<Integer> route = new ArrayList<Integer>();

        if(srcRouter.getState() == false)
        {
            return route;
        }

        route.add(srcRId);

        if(enableRoutingTableList == true)
        {
            makeTempRoutingTableMap(srcRId);
        }

        if(srcRId == destRId)
        {
            return route;
        }

        ArrayList<RoutingTableEntry> routingTable = srcRouter.getRoutingTable();
        int count = 0;
        while(true)
        {
            count++;
            if(routingTable.size() == 0)
            {
                break;
            }

            int nextHop = routingTable.get(destRId-1).getGatewayRouterId(); //routingTable => r er routingTable
            double tempDist = routingTable.get(destRId-1).getDistance();
            //System.out.println("next hop: " + nextHop);

            if(nextHop == -1 || tempDist >= Constants.INFINITY)
            {
                break;
            }

            Router tempRouter = NetworkLayerServer.routerMap.get(nextHop);

            if(tempRouter.getState() == false) //x.state == false
            {
                routingTable.get(nextHop-1).setDistance(Constants.INFINITY);
                RouterStateChanger.islocked = true;
                //NetworkLayerServer.DVR(srcRId);
                NetworkLayerServer.simpleDVR(srcRId);
                RouterStateChanger.islocked = false;
                synchronized ((RouterStateChanger.msg))
                {
                    RouterStateChanger.msg.notifyAll();
                }

                break;
            }

            route.add(nextHop);

            if(enableRoutingTableList == true)
            {
                makeTempRoutingTableMap(nextHop);
            }

            routingTable = tempRouter.getRoutingTable(); //nextHop er routing table

            if(routingTable.get(srcRId-1).getDistance() >= Constants.INFINITY)
            {
                routingTable.get(srcRId-1).setDistance(1);
                RouterStateChanger.islocked = true;
                //NetworkLayerServer.DVR(nextHop);
                NetworkLayerServer.simpleDVR(nextHop);
                RouterStateChanger.islocked = false;
                synchronized ((RouterStateChanger.msg))
                {
                    RouterStateChanger.msg.notifyAll();
                }
            }

            if(nextHop == destRId)
            {
                break;
            }

            srcRId = nextHop;

            if(count == Constants.INFINITY)
            {
                break;
            }
        }
        //System.out.println("count: " + count);
        return route;
    }

    /*public int findRouter(IPAddress reqIP, EndDevice reqDevice)
    {
        //Short reqIPtobytes[] = reqIP.getBytes();
        //int reqRId = -1;

        IPAddress checkIP = reqDevice.getGateway();
        //Short checkIPtobytes[] = checkIP.getBytes();

        //int compareVal = Short.compare(checkIPtobytes[2], reqIPtobytes[2]);

        //if(compareVal == 0)
        //{
        int reqRId = NetworkLayerServer.interfacetoRouterID.get(checkIP);
        //}

        return reqRId;
    }*/


    public Boolean deliverPacket(Packet p) {

        
        /*
        1. Find the router s which has an interface
                such that the interface and source end device have same network address.
        2. Find the router d which has an interface
                such that the interface and destination end device have same network address.
        3. Implement forwarding, i.e., s forwards to its gateway router x considering d as the destination.
                similarly, x forwards to the next gateway router y considering d as the destination,
                and eventually the packet reaches to destination router d.

            3(a) If, while forwarding, any gateway x, found from routingTable of router r is in down state[x.state==FALSE]
                    (i) Drop packet
                    (ii) Update the entry with distance Constants.INFTY
                    (iii) Block NetworkLayerServer.stateChanger.t
                    (iv) Apply DVR starting from router r.
                    (v) Resume NetworkLayerServer.stateChanger.t

            3(b) If, while forwarding, a router x receives the packet from router y,
                    but routingTableEntry shows Constants.INFTY distance from x to y,
                    (i) Update the entry with distance 1
                    (ii) Block NetworkLayerServer.stateChanger.t
                    (iii) Apply DVR starting from router x.
                    (iv) Resume NetworkLayerServer.stateChanger.t

        4. If 3(a) occurs at any stage, packet will be dropped,
            otherwise successfully sent to the destination router
        */
        IPAddress srcIP = p.getSourceIP();
        IPAddress destIP = p.getDestinationIP();

        int srcRId = NetworkLayerServer.interfacetoRouterID.get(endDevice.getGateway());

        EndDevice destEndDevice = NetworkLayerServer.endDeviceMap.get(destIP);
        int destRId = NetworkLayerServer.interfacetoRouterID.get(destEndDevice.getGateway());

        /*System.out.println("--------------------------");
        System.out.println("srcIP: " + srcIP);
        System.out.println("src router: " + srcRId);
        System.out.println("destIP: " + destIP);
        System.out.println("dest router: " + destRId);
        System.out.println("--------------------------");*/

        Boolean isDelivered = false;

        /*srcRId = 2;
        destRId = 2;*/
        srcRId_send = srcRId;
        destRId_send = destRId;

        ArrayList<Integer> route = getRoute_withState(srcRId, destRId);
        globalRoute = route;

        int routeSize = route.size();

        if(routeSize > 0)
        {
            if(destRId == route.get(routeSize-1))
            {
                isDelivered = true;
            }
        }

        /*System.out.println("------------------------------");

        for(int i=0; i<route.size(); i++)
        {
            System.out.println("RouterId: " + route.get(i));

            ArrayList<RoutingTableEntry> tempTable = routingTableMap.get(route.get(i));
            System.out.println("Routing table:");
            for(int j=0; j<tempTable.size(); j++)
            {
                System.out.println(tempTable.get(j).getRouterId() + " ; " + tempTable.get(j).getDistance() + " ; " + tempTable.get(j).getGatewayRouterId());
            }
            System.out.println("etar table shesh");
        }

        System.out.println("------------------------------");*/

        //System.out.println("isDelivered set");

        return isDelivered;
    }

    @Override
    public boolean equals(Object obj) {
        return super.equals(obj); //To change body of generated methods, choose Tools | Templates.
    }
}
