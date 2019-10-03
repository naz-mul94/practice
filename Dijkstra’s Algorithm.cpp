#include<iostream>
#define MAX 2147483647

struct adjNode
{
    int dest;
    int weight;
    adjNode* next;
};

struct adjList
{
    adjNode* head;
};

struct graph
{
    int vertex;
    adjList* array;
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
    int* pos;
    minHeapNode** array;
};

graph* createGraph(int v)
{
    graph* g= new graph;
    g->vertex = v;
    g->array = new adjList[v];
    for(int i=0;i<v;i++)g->array[i].head = NULL;
    return g;    
}

void addEdge(graph *g, int u, int v, int w)
{
    adjNode* node = new adjNode;
    node->dest = v;
    node->weight = w;
    node->next = g->array[u].head;
    g->array[u].head = node;

    node = new adjNode;
    node->dest = u;
    node->weight = w;
    node->next = g->array[v].head;
    g->array[v].head = node;
}

minHeap* createMinHeap(int capacity)
{
    minHeap* heap = new minHeap;
    heap->size =0;
    heap->capacity = capacity;
    heap->pos = new int[capacity];
    heap->array = new minHeapNode*[capacity];
    return heap;
}

void updateMinHeapNode(minHeap* heap, int vNo, int key)
{
    minHeapNode* node = new minHeapNode;
    node->v = vNo;
    node->key=key;
    heap->pos[vNo]=vNo;
    heap->array[vNo] = node;
}

void heapify(minHeap* heap, int idx)
{
    int left = 2*idx +1;
    int right = 2*idx +2;
    int smallest = idx;

    if(left < heap->size && heap->array[left]->key < heap->array[smallest]->key)
        smallest = left;
    if(right < heap->size && heap->array[right]->key < heap->array[smallest]->key)
        smallest = right;
    if(smallest != idx)
    {
        minHeapNode* smallestNode = heap->array[smallest];
        minHeapNode* idxNode = heap->array[idx];
        heap->pos[smallestNode->v] = idx;
        heap->pos[idxNode->v] = smallest;
        heap->array[idx] = smallestNode;
        heap->array[smallest] = idxNode;
        heapify(heap, smallest);
    }
}

minHeapNode* extractMin(minHeap* heap)
{
    if(heap->size ==0)return NULL;
    minHeapNode* root = heap->array[0];
    minHeapNode* lastNode =  heap->array[heap->size -1];
    heap->array[0] = lastNode;
    heap->pos[root->v] = heap->size -1;
    heap->pos[lastNode->v] =  0;
    heap->size--;
    heapify(heap, 0);
    return root;
}

bool isInHeap(minHeap* heap, int vNo)
{
    if(heap->pos[vNo] < heap->size)
        return true;
    return false;
}

void decreaseKey(minHeap* heap, int vNo, int key)
{
    int i = heap->pos[vNo];
    heap->array[i]->key = key;
    while(i && heap->array[(i-1)/2]->key > heap->array[i]->key)
    {
        minHeapNode* parNode = heap->array[(i-1)/2];
        minHeapNode* childNode = heap->array[i];
        heap->pos[vNo] = (i-1)/2;
        heap->pos[parNode->v] = i;
        heap->array[(i-1)/2] = childNode;
        heap->array[i] = parNode;
        i=(i-1)/2;
    }
}

void printArr(int *key, int* parent,  int v)
{
    for (int i = 0; i < v; ++i)
    {
        printf("source to %d = %d\n", i, key[i]);
    }
}

void dijkstra(graph *g, int src)
{
    int v = g->vertex;
    int key[v];
    int parent[v];
    minHeap* heap = createMinHeap(v);

    for (int i = 0; i < v; ++i)
    {
        if(i==src)
        {
            key[i]=0;
            parent[i]=-1;
            updateMinHeapNode(heap, i, key[i]);
            continue;
        }
        key[i]=MAX;
        parent[i]=-1;
        updateMinHeapNode(heap, i, key[i]);
    }

    heap->size = v;

    while(heap->size)
    {
        minHeapNode* node = extractMin(heap);
        int u = node->v;

        adjNode* pCrwal = g->array[u].head;
        while(pCrwal)
        {
            int idx = pCrwal->dest;
            if(isInHeap(heap, idx) && key[u] + pCrwal->weight < key[idx])
            {
                key[idx] = key[u] + pCrwal->weight;
                parent[idx] = u;
                decreaseKey(heap, idx, key[idx]);
            }
            pCrwal = pCrwal->next;
        } 
    }
    printArr(key, parent, v);
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
    

    dijkstra(g, 0);

}
