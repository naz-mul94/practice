#include<iostream>
using namespace std;
#include<stack>
int prec(char oper)
{
    if(oper=='^')
    return 3;
    else if(oper=='*'||oper=='/')
    return 2;
    else if(oper=='+'||oper=='-')
    return 1;
    else return -1;
}
string conversion(string ex)
{stack<string> poToIn;
    string temp="";
    for(int i=0;i<ex.size();i++)
    {
        if((ex[i]>='a'&&ex[i]<='z')||(ex[i])>='A'&&ex[i]<='Z')
        poToIn.push(string(1, ex[i]));
        else
        {
            string x = poToIn.top();
            poToIn.pop();
            string y =poToIn.top();
            poToIn.pop();
            x='('+y+ex[i]+x+')';
            poToIn.push(x);
        }
        //cout<<temp<<endl;
    }
    return poToIn.top();
}

int main()
 {
	int noInput;
	cin>>noInput;
	string input;
	for(int i=0;i<noInput;i++)
	{
	    cin>>input;
	    cout<<conversion(input)<<endl;
	}
	return 0;
}
