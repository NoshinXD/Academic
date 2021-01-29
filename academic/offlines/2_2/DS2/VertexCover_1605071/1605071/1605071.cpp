
#include<bits/stdc++.h>
using namespace std;
#define NULL_VALUE -999999

struct edge
{
    int u;
    int v;
    edge() {}

    edge(int u, int v)
    {
        this->u = u;
        this->v = v;
    }
};

class Graph
{
    int nVertices, nEdges;
    //vector <int> node;
    vector<edge> e;
    //vector<int> deg;

public:
    Graph(int n)
    {
        this->nVertices = n;
        nEdges = 0;
        //deg = new int[n];
        //node = new vector<int>[nVertices];
        //deg.resize(n);
    }

    void addEdge(int u, int v)
    {
        if(u<0 || v<0 || u>=nVertices || v>=nVertices)
            return; //vertex out of range
        this->nEdges++ ;
        e.push_back(edge(u, v));
        //deg[u]++;
        //deg[v]++;
    }


    int rand_Vertex_Cover()
    {
        vector<int> C;
        vector <edge> active;
        active = e;

        //srand(time(0));

        //int k = 0;

        while(active.size() != 0)
        {
            int i = abs(rand()) % active.size();

            edge a = active[i];
            C.push_back(a.u);
            C.push_back(a.v);

            vector<edge> newedge;

            for(auto j : active)
            {
                if(!(j.u == a.u || j.v == a.u || j.u == a.v || j.v == a.v))
                {
                    newedge.push_back(j);
                }
            }
            active = newedge;
        }

//        for(auto it : C)
//        {
//            cout << it << "\t";
//        }

        return C.size();
    }

//    static bool compare(edge a,edge b)
//    {
//        return a.sum < b.sum;
//    }

    int maxs_Vertex_Cover()
    {
        vector<int> C;//vertex coverr nodegulor vector

        vector <edge> active;
        active = e;

        while(active.size() != 0)
        {

            vector<int> degree(nVertices);

            for(auto i : active)
            {
                degree[i.u]++;
                degree[i.v]++;
            }

            int maxs = 0;
            edge a;
            for(auto i : active)
            {
                if(degree[i.u] + degree[i.v] > maxs)
                {
                    maxs = degree[i.u] + degree[i.v];
                    a = i;
                }
            }

            C.push_back(a.u);
            C.push_back(a.v);

            vector<edge> newedge;

            for(auto j : active)
            {
                if(!(j.u == a.u || j.v == a.u || j.u == a.v || j.v == a.v))
                {
                    newedge.push_back(j);
                }
            }

            //cout << active.size() - newedge.size() << endl;

            active = newedge;
        }

//        for(auto it : C)
//        {
//            cout << it << "\t";
//        }


        return C.size();
    }
};

int main()
{
    srand(time(0));

    FILE *fp;

    while(1)
    {
        cout << "Please enter i for information of graph i : ";
        int ch;
        cin >> ch;

        if(ch == 1)
            fp = fopen("graph1.txt", "r");
        else if(ch == 2)
            fp = fopen("graph2.txt", "r");
        else if(ch == 3)
            fp = fopen("graph3.txt", "r");
        else if(ch == 4)
            fp = fopen("graph4.txt", "r");
        else
            break;

        int n, edges, u, v;

        // cin >> n >> edges ;
        fscanf(fp, "%d %d", &n, &edges);

        Graph sav(n);
        // Graph g(n);
        int res[5];

        for(int i=0; i<edges ; i++)
        {
            // cin >> u >> v;
            fscanf(fp, "%d %d", &u, &v);
            sav.addEdge(u-1, v-1);
        }

        for(int i=0; i<5; i++)
        {
            Graph g = sav;
            //vector<int> res(5);

            int C = g.rand_Vertex_Cover();
            res[i] = C;
        }

        sort(res, res+5);

        cout << "Best : " << res[0] << endl;
        cout << "Worst : " << res[4] << endl;

        double sum = 0;

        for(int i=0; i<5; i++)
        {
            //cout << res[i] << "\t";
            sum = sum + res[i];
        }
        //cout << endl;
        cout << "Average : " << sum/5 << endl;

        //cout << "Random : " << sav.rand_Vertex_Cover() << endl;
        cout << "Max_Sum : " << sav.maxs_Vertex_Cover() << endl;
        cout << endl;

        fclose(fp);
    }

    return 0;
}
