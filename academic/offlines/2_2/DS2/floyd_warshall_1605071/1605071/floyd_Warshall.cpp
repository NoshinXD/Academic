
#include<stdio.h>
#include<stdlib.h>

#include<iostream>
using namespace std;

#define NULL_VALUE -1
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

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
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix, **pred ; //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    //int WHITE = 1, GREY = 2, BLACK = 3;
    int * color, * parent, * dist, * d_time, * f_time;
    int time;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs();
    void dfsVisit(int u);
    bool floyd_Warshall();
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    pred = 0;
    time = 0;
    d_time = 0;
    f_time = 0;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    color = 0;
    parent = 0;
    dist = 0;
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

    //allocate space for the matrix
    matrix = new int*[nVertices];
    pred = new int*[nVertices];

    color = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];
    d_time = new int[nVertices];
    f_time = new int[nVertices];

    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
        {
            if(i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = INFINITY;
        }
        //initialize the matrix cells to 0
    }
    for(int i=0; i<nVertices; i++)
    {
        pred[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            pred[i][j] = NULL_VALUE; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v, int w)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;

    matrix[u][v] = w;
    pred[u][v] = u+1;
    if(!directed)
    {
        matrix[v][u] = w;
        pred[v][u] = v+1;
    }
    nEdges++;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;

    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
    nEdges--;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;

    if(matrix[u][v] == INFINITY || matrix[u][v] == 0)
        return false;
    else
        return true;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u

    int i,deg=0;

    if(u<0 || u>=nVertices)
        return NULL_VALUE;

    for(i=0; i<nVertices; i++)
    {
        if(isEdge(u,i) == true)
            deg++;
    }
    if(isEdge(u,u) == true)
        deg++;

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
    if(source<0 || source>=nVertices) return;
    //complete this function
    //initialize BFS variables
    for(int u=0; u<nVertices; u++)
    {
        color[u] = WHITE ;
        parent[u] = -1 ;
        dist[u] = INFINITY ;
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
        //color[u] = BLACK;
        printf("%d\n",u);

        for(int v=0; v<nVertices; v++)
        {
            if(isEdge(u,v) == true)
            {
                if(color[v] == WHITE)
                {
                    color[v] = GREY;
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.enqueue(v);
                }
            }
        }
        color[u] = BLACK;
    }
}

void Graph::dfsVisit(int u)
{
    time = time + 1;
    d_time[u] = time;
    color[u] = GREY;
    for(int v=0; v<nVertices; v++)
    //for(int v=0; v<getDegree(u); v++)
    {
        if(isEdge(u,v) == true)
        {
            if(color[v] == WHITE)
            {
                parent[v] = u;
                //color[u] = BLACK;
                //printf("%d\n",u);
                dfsVisit(v);
            }
        }
    }
    color[u] = BLACK;
    //printf("%d\n",u);
    time = time + 1;
    f_time[u] = time;
}

void Graph::dfs()
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
    for(int i=0; i<nVertices; i++)
    {
        if(color[i] == WHITE)
        {
            dfsVisit(i);
        }
    }
//    printf("disco\n");
//    for(int i=0; i<nVertices;i++)
//    {
//        printf("%d\t%",d_time[i]);
//    }
//    printf("\n");
//    printf("finish\n");
//    for(int i=0; i<nVertices;i++)
//    {
//        printf("%d\t%",f_time[i]);
//    }
//    printf("\n");
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return INFINITY;

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

bool Graph::floyd_Warshall()
{
    int k, i, j;

    for(k=0; k<nVertices; k++)
    {
        for(i=0; i<nVertices; i++)
        {
            for(j=0; j<nVertices; j++)
            {
                if(matrix[i][j] > matrix[i][k] + matrix[k][j])
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }

    for(i=0; i<nVertices; i++)
    {
        if(matrix[i][i] < 0)
            return false;
    }

    cout << "All pair shortest paths: " << endl;
    for(i=0; i<nVertices; i++)
    {
        for(j=0; j<nVertices; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Predecessor Matrix: " << endl;
    for(i=0; i<nVertices; i++)
    {
        for(j=0; j<nVertices; j++)
        {
            cout << pred[i][j] << "\t";
//            if(pred[i][j] != NULL_VALUE)
//                cout << pred[i][j]+1 << "  ";
//            else
//                cout << pred[i][j] << "  ";
        }
        cout << endl;
    }
    return true;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(matrix)
    {
        for(int i = 0; i < nVertices; i++)
        {
            delete [] matrix[i];
            matrix[i] = 0;
        }
        delete [] matrix;
    }
	matrix = 0;

	if(pred)
    {
        for(int i = 0; i < nVertices; i++)
        {
            delete [] pred[i];
            pred[i] = 0;
        }
        delete [] matrix;
    }
	matrix = 0;


    if(color) delete [] color;
    color = 0 ;
    if(parent) delete [] parent;
    parent = 0 ;
    if(dist) delete [] dist;
    dist = 0 ;
    if(d_time) delete [] d_time;
    d_time = 0;
    if(f_time) delete [] f_time;
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

    //cin >> n >> directed;
    //0 for undirected & 1 for directed
    cin >> n;
    cin >> m;

    Graph g(true);

    g.setnVertices(n);

    for(i=0; i<m; i++)
    {
        cin >> u >> v >> w;
        g.addEdge(u-1, v-1, w);
    }

    if(g.floyd_Warshall() == true)
        cout << "Negative Cycle: No" << endl;
    else
        cout << "Negative Cycle: Yes" << endl;

    //cout << "comes here :D \n";

    return 0;
}
