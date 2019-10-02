#include<iostream>
#include<vector>
#include<string>
#include <map> 
#include <stack> 
#include <cstring> 
#include<climits>
using namespace std; 
#define INF (unsigned int)(~0)
int spanningTree(int V,int E,vector<vector<int> > graph);
// Driver code
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int V,E;
        cin>>V>>E;
        vector< vector<int> > graph(V,vector<int>(V,INT_MAX));
        while(E--)
        {
            int u,v,w;
            cin>>u>>v>>w;
            u--,v--;
            graph[u][v] = w;
            graph[v][u] = w;
        }
        cout<<spanningTree(V,E,graph)<<endl;
    }
    return 0;
}


int minKey(int *Key, int V, bool* mstSet)
{
	int x=INT_MAX, maxIndex=0;
	for(int i=0;i<V;i++)
		if(Key[i]<x&&!mstSet[i])x=Key[i], maxIndex=i;
	return maxIndex;
}
int spanningTree(int V,int E,vector<vector<int> > graph)
{
	bool mstSet[V];
    int Key[V];
    int ans=0;
	for(int i=0;i<V;i++)
	{
		mstSet[i]=false;
		Key[i]=INT_MAX;
	}
	Key[0]=0;
	for(int i=0;i<V;i++)
	{
		int u=minKey(Key, V, mstSet);
		mstSet[u]=true;
		ans+=Key[u];
		for(int j=0;j<V;j++)
		{
			if(graph[u][j]!=INT_MAX && !mstSet[j] && Key[j]>graph[u][j])
			{
				Key[j]=graph[u][j];
			}
			
		}
	}
	return ans;	
}
