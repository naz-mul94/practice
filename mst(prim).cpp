#include<iostream>
#define MAX 2147483647
using namespace std;

 struct adjencyNode
 {
    int dest;
    int weight;
    adjencyNode* next;
 };

 struct adjlist
 {
    adjencyNode* head;
 };

 struct graph
 {
    int v;
    adjlist* array;
 };

 struct minHeapNode
 {
    int v;
    int key;
 };

 struct minHeap
 {
    int capacity;
    int size;
    int *pos;
    minHeapNode** array;
 };

 graph *creategraph(int v)
 {
    graph *g=new graph;
    g->v=v;
    g->array= new adjlist[v];
    for(int i=0;i<v;i++)g->array[i].head=NULL;
    return g;
 }

void addEdge(graph *g, int s, int d, int w)
{
    adjencyNode* node= new adjencyNode;
    node->dest=d;
    node->weight=w;
    node->next= g->array[s].head;
    g->array[s].head=node;

    node= new adjencyNode;
    node->dest=s;
    node->weight=w;
    node->next= g->array[d].head;
    g->array[d].head=node;
}

minHeap* createMinHeap(int capacity)
{
    minHeap* heap= new minHeap;
    heap->size=0;
    heap->capacity=capacity;
    heap->pos= new int[capacity];
    heap->array = new minHeapNode*[capacity];
}

void updateMinHeapNode(minHeap* heap, int v, int key)
{
    heap->array[v]=new minHeapNode;
    heap->array[v]->v=v;
    heap->array[v]->key=key;
    heap->pos[v]=v;
}

void heapify(minHeap* heap, int idx)
{
    int left=2*idx+1;
    int right=2*idx+2;
    int smallest= idx;

    if(left < heap->size && heap->array[left]->key<heap->array[smallest]->key)
        smallest=left;
    if(right < heap->size && heap->array[right]->key< heap->array[smallest]->key)
        smallest = right;
    if(smallest!=idx)
    {
        minHeapNode* smallestNode = heap->array[smallest];
        minHeapNode* idxNode = heap->array[idx];

        heap->pos[smallestNode->v]= idx;
        heap->pos[idxNode->v] = smallest;

        heap->array[smallest] = idxNode;
        heap->array[idx] =smallestNode;
        heapify(heap, smallest);
    }
}

minHeapNode* extractmin(minHeap* heap)
{
    if(heap->size==0)return NULL;

    minHeapNode* root= heap->array[0];
    minHeapNode* lastNode= heap->array[heap->size-1];
    heap->array[0]=lastNode;

    heap->pos[root->v]=heap->size-1;
    heap->pos[lastNode->v]=0;
    (heap->size)--;
    heapify(heap, 0);
    return root;
}

bool isInHeap(minHeap* heap, int v)
{
    if(heap->pos[v] < heap->size)
        return true;
    return false;
}

void decreaseKey( minHeap* heap, int idx, int w)
{
    int position = heap->pos[idx];
    heap->array[position]->key=w;
    while(position && heap->array[(position - 1)/2]->key > heap->array[position]->key)
    {
        minHeapNode* parNode = heap->array[(position - 1)/2];
        minHeapNode* childNode = heap->array[position];
        heap->pos[parNode->v] = position;
        heap->pos[childNode->v] = (position - 1)/2;

        heap->array[(position - 1)/2]= childNode;
        heap->array[position] = parNode;
        position = (position -1)/2; 
    }
}

void printArr(int* parent, int v)
{
    for (int i = 0; i < v; ++i)
    {
        printf("%d --- %d\n",parent[i], i );
    }
}

void printMst(graph *g)
{
    int v=g->v;
    int key[v];
    int parent[v];
    minHeap* heap= createMinHeap(v);
    heap->pos[0]=0;
    for(int i=1;i<v;i++)
    {
        parent[i]=-1;
        key[i]=MAX;
        updateMinHeapNode(heap, i, key[i]);
    }
    parent[0]=-1;
    key[0]=0;
    updateMinHeapNode(heap, 0, key[0]);
    heap->size=v;
    while(heap->size)
    {
        minHeapNode* node= extractmin(heap);
        int u = node->v;

        adjencyNode* pCrawl=g->array[u].head;
        while(pCrawl)
        {
            int idx=pCrawl->dest;
            if(isInHeap(heap, idx) && pCrawl->weight< key[idx])
            {
                key[idx]=pCrawl->weight;
                parent[idx] = u;
                decreaseKey(heap, idx, key[idx]);
            }
            pCrawl = pCrawl->next;
        }
    }  

    printArr(parent, v);
}

 int main()
 {
    int v, e;
    int u, w;	 
   cin>>v>>e; 
   graph* g = creategraph(v);
   for(int i=0;i<e;i++)
   {
	cin>>u>>v>>w;addEdge(g, u, v, w); 
   }	

    printMst(g);
 }
######################################## method 2(easy but O(V2)  ###########################################################
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
