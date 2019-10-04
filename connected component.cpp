#include<iostream>
#include<string>
#include<list>
using namespace std;

class graph
{
    int vertex;
    list<int> *adj;
    void dfsUtil(int v, bool* visited);
    public:
        graph(int v)
        {
            vertex=v;
            adj = new list<int>[v+1];
        }
        void addEdge(int u, int v);
        int noConCompo(graph g, int i);
};

void graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void graph::dfsUtil(int v, bool* visited)
{
    visited[v]=true;

    list<int>::iterator i;
    for(i=adj[v].begin(); i!=adj[v].end(); i++)
    {
        if(!visited[*i])
            dfsUtil(*i, visited);
    }
}

int graph::noConCompo(graph g, int v)
{
    bool visited[v+1];
    int ans=0;
    for(int i=1;i<=v;i++)visited[i] = false;
    for (int i = 1; i <= v; ++i)
    {
        if(!visited[i])
        {
            dfsUtil(i, visited);
        }
    }   
    return ans; 
}

int main()
{
    int v, e, u, w;
    cin>>v>>e;
    graph g(v);
    for(int i=0;i<e;i++)
    {
        cin>>u>>w;
        g.addEdge(u, w);
    }
    cout<<g.noConCompo(g, v)<<endl;

}
