#include<iostream>
#include<stack>
#include<queue>
using namespace std;

void nextGreater(long long int* arr, int N)
{
    stack<pair<long long int, int>> next;
    long long int *index=new long long int[N];
    for (int i = 0; i < N; ++i)
    {
        if(next.empty())next.push({arr[i], i});
        else if(arr[i]>next.top().first)
        {
            while(!next.empty() && arr[i]>next.top().first)
            {
                index[next.top().second]=i;
                next.pop();
            }
            
        }
        next.push({arr[i], i});
    }
    while(!next.empty())
    {
        index[next.top().second]=-1;
        next.pop();
    }
    for(int i=0;i<N;i++)
    if(index[i]==-1)printf("-1 ");
    else printf("%lld ", arr[index[i]]);
    cout<<endl;
}

int main()
{
    int noInput, N;
    long long int *arr;
    cin>>noInput;
    while(noInput--)
    {
        cin>>N;
        arr=new long long int[N];
        for(int i=0;i<N;i++)cin>>arr[i];
        nextGreater(arr, N);
    }
    

}
