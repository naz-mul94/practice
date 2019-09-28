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
{stack<char> inToPo;
    string temp="";
    for(int i=0;i<ex.size();i++)
    {
        if((ex[i]>='a'&&ex[i]<='z')||(ex[i])>='A'&&ex[i]<='Z')
        temp+=ex[i];
    	else if(ex[i]=='(')
    		inToPo.push(ex[i]);
    	else if(ex[i]==')')
    	{
    		while(!inToPo.empty()&&ex[i]!='(')
    		{
    			temp+=ex[i];
    			inToPo.pop();
    		}
    		if(ex[i]=='(')
    			inToPo.pop();
    	}
        else
        {
            if(!inToPo.empty()&&prec(ex[i])<=prec(inToPo.top()))
            {
            	while(!inToPo.empty()&&prec(ex[i])<=prec(inToPo.top()))
            	{
            		temp+=inToPo.top();
            		inToPo.pop();
            	}
            }
            inToPo.push(ex[i]);
        }
       
    }
    while(!inToPo.empty())
    {
    	temp+=inToPo.top();
    	inToPo.pop();
    }
    	
     string ans="";
        for (int i = temp.size()-1;i>=0; --i)
        {
        	ans+=temp[i];
        }

    return ans;
}

int main()
 {
	int noInput;
	cin>>noInput;
	string input;
	for(int i=0;i<noInput;i++)
	{
	    cin>>input;
	    string modifiedString="";
	    for(int i=input.size()-1;i>=0;i--)
	    {
	    	if(input[i]=='(')
	    		modifiedString+=')';
	    	else if(input[i]==')')
	    		modifiedString+='(';
	    	else
	    		modifiedString+=input[i];
	    }
	    cout<<conversion(modifiedString)<<endl;
	}
	return 0;
}
