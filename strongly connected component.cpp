#include<iostream>
#include<stack>
#include<list>
using namespace std;

class graph
{
    int vertex;
    list<int> *adj;
    void dfsUtil(int v, bool* visited, stack<int> &finishST);
    void dfs(int v, bool* visited);
    public:
        graph(int v)
        {
            vertex=v;
            adj = new list<int>[v+1];
        }
        void addEdge(int u, int v);
        int noConCompo(graph g, int i);
        graph getReverse();
};

void graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void graph::dfsUtil(int v, bool* visited, stack<int> &finishST)
{
    visited[v]=true;

    list<int>::iterator i;
    for(i=adj[v].begin(); i!=adj[v].end(); i++)
    {
        if(!visited[*i])
            dfsUtil(*i, visited, finishST);
    }
    finishST.push(v);
}

void graph::dfs(int v, bool* visited)
{
    visited[v]=true;

    list<int>::iterator i;
    for(i=adj[v].begin(); i!=adj[v].end(); i++)
    {
        if(!visited[*i])
            dfs(*i, visited);
    }
}

graph graph::getReverse()
{
    graph g(vertex);
    for (int i = 0; i < vertex; ++i)
    {
        list<int>::iterator j;
        for(j=adj[i].begin(); j!=adj[i].end();j++)
        {
            g.adj[*j].push_back(i);
        }
    }
    return g;
}

int graph::noConCompo(graph g, int v)
{
    stack<int> finishST;
    bool visited[v];
    int ans=0;
    for(int i=0;i<v;i++)visited[i] = false;
    for (int i = 0; i < v; ++i)
    {
        if(!visited[i])
        {
            dfsUtil(i, visited, finishST);
        }
    }

    graph reverseGraph = getReverse();
    for(int i=0;i<v;i++)visited[i]=false;
    for (int i = 0; i < v; ++i)
    {
        int x=finishST.top();
        finishST.pop();
        if(!visited[x])
        {
            reverseGraph.dfs(x, visited);
            ans++;
        }
    }   
    return ans; 
}
