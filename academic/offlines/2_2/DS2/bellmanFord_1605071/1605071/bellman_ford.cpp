//#include<bits/stdc++.h>
#include<stdio.h>
#include<fstream>
#include<iostream>
#include <cstdlib>
using namespace std;
//#define NULL_VALUE -999999
#define NULL_VALUE -1
#define INFINITY 999999

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
    ArrayList  * adjList ;
    int * dist;
    int ** weight;
    int *prev;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int * color, * parent, * d_time, * f_time;
    int time;


public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    int getnVertices()
    {
        return nVertices;
    }
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    //void dfs(int source); //will run dfs in the graph
    void dfs();
    void dfsVisit(int u);

    bool bellman_ford(int s);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    dist = 0;
    weight = 0;
    prev = 0;
    time = 0;
    d_time = 0;
    f_time = 0;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    color = 0;
    parent = 0;
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

    weight = new int * [nVertices];
    for(int i=0; i<nVertices; i++)
        weight[i] = new int[nVertices];

    dist = new int[nVertices];
    prev = new int[nVertices];

    color = new int[nVertices];
    parent = new int[nVertices];
    d_time = new int[nVertices];
    f_time = new int[nVertices];
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    //cout << "hi" << endl;
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    weight[u][v] = w;
    if(!directed)
    {
        adjList[v].insertItem(u) ;
        weight[v][u] = w;
    }
    //cout << "hi" <<endl;
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


bool Graph::bellman_ford(int s)
{
    int u, v, d, i, j;
    for(u=0; u<nVertices; u++)
    {
        dist[u] = INFINITY;
        prev[u] = NULL_VALUE;
    }
    dist[s] = 0;

    for(i=0; i<nVertices-1; i++)
    {
        for(u=0; u<nVertices; u++)
        {
            for(j = 0; j<adjList[u].getLength(); j++)
            {
                v = adjList[u].getItem(j);
                if(dist[v] > dist[u] + weight[u][v])
                {
                    dist[v] = dist[u] + weight[u][v];
                    prev[v] = u;
                }
            }
        }
    }

    for(u=0; u<nVertices; u++)
    {
        for(j = 0; j<adjList[u].getLength(); j++)
        {
            v = adjList[u].getItem(j);
            if(dist[v] > dist[u] + weight[u][v])
            {
                return false;
            }
        }
    }

    cout << "vertex  dist  prev"<< endl;

    for(i = 0; i<nVertices; i++)
        cout << i << "\t" << dist[i] << "\t" << prev[i] << endl;

    return true;

}
//void Graph::printGraph()
//{
//    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%d:", i);
//        for(int j=0; j<adjList[i].getLength(); j++)
//        {
//            printf(" %d", adjList[i].getItem(j));
//        }
//        printf("\n");
//    }
//}
//
Graph::~Graph()
{
    //write your distructor here
    if(adjList)
        delete [] adjList;
    adjList = 0 ;
    if(weight)
    {
        for(int i = 0; i < getnVertices(); i++)
            delete [] weight[i];
        delete [] weight;
    }
    weight = 0;
    if(prev)
        delete [] prev;

    prev = 0;
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

int main()
{
    //MinHeap h(50);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int i, n, u, v, w, m;
    bool directed;
    //printf("Enter number of vertices: ");
    cin >> n >> directed;
    //0 for undirected & 1 for directed
    //printf("Enter number of edges: ");
    //cin >> m;

    Graph g(directed);

    g.setnVertices(n);

    while(true)
    {
        cin >> u >> v >> w;
        if (u<0 || v<0)
        {
            break;
        }
        else
        {
            g.addEdge(u, v, w);
        }
    }


    int s;
    cin >> s;
    if(g.bellman_ford(s) == true)
        cout << "No negative cycle." << endl;
    else
        cout << "Negative cycle detected." << endl;

    //cout << "comes here :D \n";

    return 0;
}

