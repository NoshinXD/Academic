//Work needed
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Router {
    private int routerId;
    private int numberOfInterfaces;
    private ArrayList<IPAddress> interfaceAddresses;//list of IP address of all interfaces of the router
    private ArrayList<RoutingTableEntry> routingTable;//used to implement DVR

    private ArrayList<Integer> neighborRouterIDs;//Contains both "UP" and "DOWN" state routers
    private Boolean state;//true represents "UP" state and false is for "DOWN" state
    private Map<Integer, IPAddress> gatewayIDtoIP;
    public Router() {
        interfaceAddresses = new ArrayList<>();
        routingTable = new ArrayList<>();
        neighborRouterIDs = new ArrayList<>();

        /**
         * 80% Probability that the router is up
         */
        Random random = new Random();
        double p = random.nextDouble();
        if(p < 0.80) state = true;
        else state = false;

        numberOfInterfaces = 0;
    }

    public Router(int routerId, ArrayList<Integer> neighborRouters, ArrayList<IPAddress> interfaceAddresses, Map<Integer, IPAddress> gatewayIDtoIP) {
        this.routerId = routerId;
        this.interfaceAddresses = interfaceAddresses;
        this.neighborRouterIDs = neighborRouters;
        this.gatewayIDtoIP = gatewayIDtoIP;
        routingTable = new ArrayList<>();



        /**
         * 80% Probability that the router is up
         */
        Random random = new Random();
        double p = random.nextDouble();
        if(p < 0.80) state = true;
        else state = false;

        numberOfInterfaces = interfaceAddresses.size();
    }

    @Override
    public String toString() {
        String string = "";
        string += "Router ID: " + routerId + "\n" + "Interfaces: \n";
        for (int i = 0; i < numberOfInterfaces; i++) {
            string += interfaceAddresses.get(i).getString() + "\t";
        }
        string += "\n" + "Neighbors: \n";
        for(int i = 0; i < neighborRouterIDs.size(); i++) {
            string += neighborRouterIDs.get(i) + "\t";
        }
        return string;
    }



    /**
     * Initialize the distance(hop count) for each router.
     * for itself, distance=0; for any connected router with state=true, distance=1; otherwise distance=Constants.INFTY;
     */
    public void initiateRoutingTable() {
        clearRoutingTable();
        for(int r=0; r<NetworkLayerServer.routers.size(); r++)
        {
            int rId = NetworkLayerServer.routers.get(r).routerId;
            double distance = Constants.INFINITY * 1.0;
            int gatewayRouterId = -1;

            if(rId == this.routerId)
            {
                distance = 0.0;
                gatewayRouterId = rId;
            }
            else
            {
                boolean is_neigh = false;
                for(int n=0; n<neighborRouterIDs.size(); n++)
                {
                    if(rId == neighborRouterIDs.get(n))
                    {
                        is_neigh = true;
                        break;
                    }
                }

                if(is_neigh == true)
                {
                    boolean neigh_state = NetworkLayerServer.routerMap.get(rId).state;
                    if(neigh_state == true)
                    {
                        distance = 1.0;
                    }
                    //distance = 1.0;
                    gatewayRouterId = rId;
                }
            }

            RoutingTableEntry entry = new RoutingTableEntry(rId, distance, gatewayRouterId);
            addRoutingTableEntry(entry);
        }

        /*if(this.routerId == 7)
        {
            //System.out.println("routingTable-size: " + routingTable.size());
            for(int i=0; i<routingTable.size(); i++)
            {
                System.out.println(routingTable.get(i).getRouterId() + " ; " + routingTable.get(i).getDistance() + " ; " + routingTable.get(i).getGatewayRouterId());

            }
        }*/
    }

    /**
     * Delete all the routingTableEntry
     */
    public void clearRoutingTable() {
        routingTable.clear();
    }

    /**
     * Update the routing table for this router using the entries of Router neighbor
     * @param neighbor
     */
    public boolean updateRoutingTable(Router neighbor) {
        ArrayList<RoutingTableEntry> neighRoutingTable = neighbor.getRoutingTable();

        boolean isUpdate = false;

        if(neighRoutingTable.size() == 0)
        {
            return isUpdate;
        }

        double neighDist = -1;
        for(int i=0; i<neighRoutingTable.size(); i++)
        {
            if(this.routerId == neighRoutingTable.get(i).getRouterId())
            {
                neighDist = neighRoutingTable.get(i).getDistance();
                break;
            }
        }

        for(int i=0; i<this.routingTable.size(); i++)
        {
            double prevDist = this.routingTable.get(i).getDistance();

            double d = neighRoutingTable.get(i).getDistance();

            double newDist = neighDist + d;

            if(newDist < prevDist)
            {
                this.routingTable.get(i).setDistance(newDist);
                this.routingTable.get(i).setGatewayRouterId(neighbor.routerId);

                isUpdate = true;
            }
        }

        /*if(this.routerId == 2 && neighbor.routerId == 1)
        {
            System.out.println();
            System.out.println("updated routing Table: ");
            for(int i=0; i<routingTable.size(); i++)
            {
                System.out.println(routingTable.get(i).getRouterId() + " ; " + routingTable.get(i).getDistance() + " ; " + routingTable.get(i).getGatewayRouterId());

            }
            System.out.println();
        }*/

        return isUpdate;
    }

    public boolean sfupdateRoutingTable(Router neighbor) {
        //System.out.println("here");
        ArrayList<RoutingTableEntry> neighRoutingTable = neighbor.getRoutingTable();

        boolean isUpdate = false;

        if(neighRoutingTable.size() == 0)
        {
            return isUpdate;
        }

        double neighDist = -1;
        int nextHop = -1;
        for(int i=0; i<neighRoutingTable.size(); i++)
        {
            if(this.routerId == neighRoutingTable.get(i).getRouterId())
            {
                neighDist = neighRoutingTable.get(i).getDistance(); //c(x->z)
                //nextHop = neighRoutingTable.get(i).getGatewayRouterId();
                break;
            }
        }

        for(int i=0; i<this.routingTable.size(); i++)
        {
            double prevDist = this.routingTable.get(i).getDistance(); //d(x->y)
            nextHop = this.routingTable.get(i).getGatewayRouterId(); //nexthop(x,y)

            //System.out.println("check_size: " + neighRoutingTable.size());
            //System.out.println("check_size: " + this.routingTable.size());

            double d = neighRoutingTable.get(i).getDistance(); //d(z->y)

            double newDist = neighDist + d;

            //if(newDist < prevDist)
            if((nextHop == neighbor.routerId) || (newDist < prevDist && this.routerId != neighRoutingTable.get(i).getGatewayRouterId()))
            {
                //System.out.println("here");
                if(this.routingTable.get(i).getDistance() != newDist)
                {
                    this.routingTable.get(i).setDistance(newDist);
                    this.routingTable.get(i).setGatewayRouterId(neighbor.routerId);

                    isUpdate = true;
                }
            }
        }

        return isUpdate;
    }

    /**
     * If the state was up, down it; if state was down, up it
     */
    public void revertState() {
        state = !state;
        if(state) { initiateRoutingTable(); }
        else { clearRoutingTable(); }
    }

    public int getRouterId() {
        return routerId;
    }

    public void setRouterId(int routerId) {
        this.routerId = routerId;
    }

    public int getNumberOfInterfaces() {
        return numberOfInterfaces;
    }

    public void setNumberOfInterfaces(int numberOfInterfaces) {
        this.numberOfInterfaces = numberOfInterfaces;
    }

    public ArrayList<IPAddress> getInterfaceAddresses() {
        return interfaceAddresses;
    }

    public void setInterfaceAddresses(ArrayList<IPAddress> interfaceAddresses) {
        this.interfaceAddresses = interfaceAddresses;
        numberOfInterfaces = interfaceAddresses.size();
    }

    public ArrayList<RoutingTableEntry> getRoutingTable() {
        return routingTable;
    }

    public void addRoutingTableEntry(RoutingTableEntry entry) {
        this.routingTable.add(entry);
    }

    public ArrayList<Integer> getNeighborRouterIDs() {
        return neighborRouterIDs;
    }

    public void setNeighborRouterIDs(ArrayList<Integer> neighborRouterIDs) { this.neighborRouterIDs = neighborRouterIDs; }

    public Boolean getState() {
        return state;
    }

    public void setState(Boolean state) {
        this.state = state;
    }

    public Map<Integer, IPAddress> getGatewayIDtoIP() { return gatewayIDtoIP; }

    public void printRoutingTable() {
        System.out.println("Router " + routerId);
        System.out.println("DestID Distance Nexthop");
        for (RoutingTableEntry routingTableEntry : routingTable) {
            System.out.println(routingTableEntry.getRouterId() + " " + routingTableEntry.getDistance() + " " + routingTableEntry.getGatewayRouterId());
        }
        System.out.println("-----------------------");
    }
    public String strRoutingTable() {
        String string = "Router" + routerId + "\n";
        string += "DestID Distance Nexthop\n";
        for (RoutingTableEntry routingTableEntry : routingTable) {
            string += routingTableEntry.getRouterId() + " " + routingTableEntry.getDistance() + " " + routingTableEntry.getGatewayRouterId() + "\n";
        }

        string += "-----------------------\n";
        return string;
    }

}
