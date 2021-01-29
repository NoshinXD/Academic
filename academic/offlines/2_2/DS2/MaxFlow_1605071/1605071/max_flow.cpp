#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
using namespace std;
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

struct edge
{
    int from, to, capacity, flow;
    node(int u=0, int v=0, int k=0, int f=0)
    {
        from=u, to=v, capacity=k, flow=f;
    }
//    bool operator < (const node &a)
//    {
//        return key < a.key;
//    }
};

edge E[10000000];

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0)
        return true ;
    else
        return false ;
}


int Queue::dequeue()
{
    if(length == 0)
        return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data)
        delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item )
            return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length )
        return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE )
        return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length)
        return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)
        return true;
    else
        return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list)
        delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList, * edge_no ;
    int **weight;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int * color, * parent, *eparent, * dist, * d_time, * f_time, *path;
    int time;


public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void setnEdges(int m);
    void addEdge(int u, int v, int w, int i);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    //void dfs(int source); //will run dfs in the graph
    void dfs(int s);
    void dfsVisit(int u);
    int find_path(int u, int t);
    int ford_fulkerson(int s, int t);
    void min_cut(int s);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0;
    nEdges = 0 ;
    adjList = 0 ;
    edge_no = 0;
    time = 0;
    d_time = 0;
    f_time = 0;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    color = 0;
    parent = 0;
    eparent = 0;
    dist = 0;

    weight = 0;
    edge_no = 0;
    path = 0;
    /*color = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }*/
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0)
        delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    edge_no = new ArrayList[nVertices];

    color = new int[nVertices];
    parent = new int[nVertices];
    eparent = new int[nVertices];
    dist = new int[nVertices];
    d_time = new int[nVertices];
    f_time = new int[nVertices];

    path = new int[nVertices];
    weight = new int * [nVertices];
    for(int i=0; i<nVertices; i++)
        weight[i] = new int[nVertices];
}

void Graph::setnEdges(int m)
{
    this->nEdges = m ;
}

void Graph::addEdge(int u, int v, int w, int i)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    weight[u][v] = w;
    edge_no[u].insertItem(i);
//    if(!directed)
//    {
//        adjList[v].insertItem(u) ;
//        weight[v][u] = w;
//    }
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    this->nEdges-- ;
    adjList[u].removeItem(v) ;
    if(!directed)
        adjList[v].removeItem(u) ;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    if(adjList[u].searchItem(v) != NULL_VALUE)
        return true;
    else
        return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    //return adjList[u].getLength();
    int i,deg=0;

    if(u<0 || u>=nVertices)
        return NULL_VALUE;
    deg = adjList[u].getLength();

    if(directed)
    {
        if(isEdge(u,u))
            deg--;
        for(i=0; i<nVertices; i++)
        {
            if(isEdge(i,u) == true)
                deg++;
        }
    }
    return deg;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    int i,f=0;
    for(i=0; i<nVertices; i++)
    {
        if(isEdge(u,i) == true && isEdge(v,i) == true)
        {
            f=1;
            break;
        }
    }
    if(f == 1)
        return true;
    else
        return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    parent[source] = -1;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int u;
        u = q.dequeue();
        //;color[u] = BLACK;
        printf("%d\n",u);

        for(int v=0; v<nVertices; v++)
        {
            if(isEdge(u,v) == true)
            {
                if(color[v] == WHITE)
                {
                    color[v] = GREY;
                    q.enqueue(v);
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                }
            }
        }
        color[u] = BLACK;
    }
}

void Graph::dfsVisit(int u)
{
    //cout << "Visited " << u << " at time " << time << "\n";
    time = time + 1;
    d_time[u] = time;
    color[u] = GREY;
    //printf("%d\n",u);
    for(int i=0; i<edge_no[u].getLength(); i++)
        //for(int v=0; v<getDegree(u); v++)
    {
        // int v = adjList[u].getItem(i);
        int e_no = edge_no[u].getItem(i);
        int v = E[e_no].to, w = E[e_no].capacity;
        if(w > 0)
        {
            if(color[v] == WHITE)
            {
                parent[v] = u;
                eparent[v] = e_no;
                //color[u] = BLACK;
                dfsVisit(v);
            }
        }
    }
    color[u] = BLACK;
    //printf("%d\n",u);
    time = time +1;
    f_time[u] = time;
}

void Graph::dfs(int s)
{
    //write this function
    for(int u=0; u<nVertices; u++)
    {
        color[u] = WHITE ;
        parent[u] = -1 ;
        dist[u] = INFINITY ;
        d_time[u] = -1;
        f_time[u] = -1;
    }
    time = 0;
    /*for(int u=0; u<nVertices; u++)
    {
        if(color[u] == WHITE)
        {
            dfsVisit(u);
        }
    }*/
    dfsVisit(s);
}

int Graph::find_path(int u, int t)
{
    dfs(u);

    int count = 0;
    if(color[t] == WHITE)
        return count;

    int dest = t;

    //int count = 0;

    while(dest != u)
    {
        path[count] = eparent[dest];
        dest = parent[dest];
        count++;
    }

//    cout << u << "\t";
//
//    for(int i=count-1; i>=0; i--)
//        cout << E[path[i]].to << "\t";
//    cout << "\n";
    return count;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    //return INFINITY ;
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return INFINITY;

    printf("\nThe path is: \n");
    bfs(u);
    if(dist[v] != -1)
        return dist[v];
    else
        return INFINITY;

    /*int d;
    if(dist[v] > dist[u])
        d = dist[v] - dist[u];
    else
        d = dist[u] - dist[v];
    return d;*/
}

int Graph::ford_fulkerson(int s, int t)
{
    int total_f = 0;
    while(true)
    {
        int count = find_path(s, t);
        if(count == 0)
            break;

        int f = INFINITY;

        for(int i=0; i<count; i++)
        {
            int e_no = path[i];
            int w = E[e_no].capacity;

            if(f > w)
                f = w;
        }
        total_f = total_f + f;
        //cout << "Flow through there: " << f << "\n";

        for(int i=0; i<count; i++)
        {
            int e_no = path[i];
            if(e_no % 2 == 0)
            {
                E[e_no].capacity = E[e_no].capacity - f;
                E[e_no + 1].capacity = E[e_no + 1].capacity + f;
                E[e_no].flow = E[e_no].flow + f;
            }
            else
            {
                E[e_no].capacity = E[e_no].capacity - f;
                E[e_no - 1].capacity = E[e_no - 1].capacity + f;
                E[e_no - 1].flow = E[e_no - 1].flow - f;
            }
        }
    }

    return total_f;
}


void Graph::min_cut(int s)
{
    dfs(s);
    int i, u;

    for(i=0; i<nEdges; i+=2)
    {
        int u = E[i].from, v = E[i].to, w = E[i].capacity;
        if(color[u] != WHITE && color[v] == WHITE)
        {
            cout << u << "\t" << v << "\t" << w+E[i].flow << endl;
        }
    }
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(adjList)
        delete [] adjList;
    adjList = 0 ;
    if(color)
        delete [] color;
    color = 0 ;
    if(parent)
        delete [] parent;
    parent = 0 ;
    if(dist)
        delete [] dist;
    dist = 0 ;
    if(d_time)
        delete [] d_time;
    d_time = 0;
    if(f_time)
        delete [] f_time;
    f_time = 0;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int i, n, u, v, w, m;
    bool directed;
    //printf("Enter number of vertices: ");
    cin >> n >> m;
    //0 for undirected & 1 for directed
    //printf("Enter number of edges: ");
    //cin >> m;

    Graph g(true);

    g.setnVertices(n);
    g.setnEdges(m);

//    while(true)
//    {
//        cin >> u >> v >> w;
//        if (u<0 || v<0 || w<0)
//        {
//            break;
//        }
//        else
//        {
//            g.addEdge(u, v, w);
//        }
//    }


    for(i = 0; i < 2*m; i=i+2)
    {
        scanf("%d %d %d", &u, &v, &w);
        g.addEdge(u, v, w, i);
        g.addEdge(v, u, 0, i+1);
        E[i].from = u;
        E[i].to = v;
        E[i].capacity = w;
        E[i+1].from = v;
        E[i+1].to = u;
        E[i+1].capacity = 0;
    }

    int s, t;
    cin >> s >> t;

    int maxflow = g.ford_fulkerson(s, t);
    cout << "Maximum flow : " << maxflow << endl << endl;

    cout << "Flow along each edge : " << endl;
    cout << "From\tto\tcapacity\tflow" << endl;
    for(int i=0; i < 2*m; i=i+2)
    {
        cout << E[i].from << "\t" << E[i].to << "\t" << E[i].capacity+E[i].flow << "\t\t" << E[i].flow << endl;
    }
    cout << endl;
//    for(int i=0; i < 2*m; i=i+2)
//    {
//        cout << E[i].from << " " << E[i].to << " " << E[i].capacity+E[i].flow << " has a flow of unit " << E[i].flow << "\n";
//    }
//    cout << g.find_path(s, t) << "\n";
    cout << "Edges of min-cut : " << endl;
    cout << "From\tto\tflow" << endl;
    g.min_cut(s);

    return 0;
}
