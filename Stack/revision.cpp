#include <iostream>
#include <stack>
#include <vector>
using namespace std;
// Reversing Stack using 1 stack
void transfer(stack<int> &s1,stack<int> &s2,int n)
{
    for(int i=0;i<n;i++)
    {
        s2.push(s1.top());
        s1.pop();
    }
}

void reverseStack(stack<int> &s1)
{
    int n = s1.size();

    for(int i=0;i<n;i++)
    {
        int num = s1.top();
        s1.pop();
        stack<int> s2;
        transfer(s1,s2,n-i-1);
        s1.push(num);
        transfer(s2,s1,n-i-1);
    }
}

// Reverse Stack Using Rec
void insertAtBottom(stack<int> &s,int x)
{
    if(s.empty())
    {
        s.push(x);
        return;
    }

    int y = s.top();
    s.pop();
    insertAtBottom(s,x);
    s.push(y);
}

void reverseStackRec(stack<int> &s)
{
    if(s.empty())
        return;
    
    int x = s.top();
    s.pop();
    reverseStackRec(s);
    insertAtBottom(s,x);
}

bool isValid(string s) 
{
    int len = s.length();
    stack<char> st;
    for(int i=0;i<len;i++)
    {
        if(s[i]=='(' || s[i]=='{' || s[i]=='[')
           st.push(s[i]);
        else
        {
            if(s[i]==')')
            {
                if(st.empty() || st.top()!='(')
                    return false;
                else
                    st.pop();
            }
            else if(s[i]=='}')
            {
                if(st.empty() || st.top()!='{')
                    return false;
                else
                    st.pop();
            }
            else if(s[i]==']')
            {
                if(st.empty() || st.top()!='[')
                    return false;
                else
                    st.pop();
            }
        }   
    }
    return st.empty();
}

vector<int> calculateSpan(int price[], int n)
{
   // Your code here
   stack<int> s;
   s.push(0);
   vector<int> span;
   span.push_back(1);
   
   for(int i=1;i<n;i++)
   {
       if(price[i]<price[i-1])
        span.push_back(1);
       else
       {
           while(!s.empty() && price[s.top()]<=price[i])
            s.pop();
            
           if(s.empty())
            span.push_back(i+1);
           else
            span.push_back(i - s.top());
       }
       s.push(i);
   }
   return span;
}

int Histogram(vector<int>& heights) 
    {
        stack<int> s;
        int n = heights.size(); 
        int max_area=0,i=0;
        
        // i=>rightmost smaller element
        // s.top=>leftmost smaller element         
        while(i<n)
        {
            if(s.empty() || heights[s.top()] <= heights[i])
                s.push(i++);
            else
            {
                int tp = s.top();
                s.pop();
                int area = heights[tp] * (s.empty() ? i : i-s.top()-1);
                if(max_area<area)
                    max_area = max(max_area,area);
            }
        }
        while(!s.empty())
        {
            int tp = s.top();
            s.pop();
            int area = heights[tp] * (s.empty() ? i : i-s.top()-1);
            if(max_area<area)
                max_area = max(max_area,area);
        }
        
        return max_area;
    }

int findMaxLen(string str) 
    {
        // code here
        stack<int> s;
        s.push(-1);
        int max_count=0;
        int n = str.length();
        for(int i=0;i<n;i++)
        {
            if(str[i]=='(')
                s.push(i);
            else
            {
                s.pop();
                
                if(!s.empty())
                {
                    max_count = max(max_count,i-s.top());
                }
                else
                {
                    s.push(i);  
                }
            }
        }
        return max_count;
    }

int main() 
{
    stack<int> s;

    for(int i=1;i<=5;i++)
        s.push(i);
    // Reversing using 1 Stack

    stack<int> temp = s,temp2=s;
    cout<<"Original Stack: ";
    while(!temp.empty())
    {
        cout<<temp.top()<<" ";
        temp.pop();
    }
    cout<<endl;
    cout<<"Reversed Stack Using 1 Stack: ";
    reverseStack(temp2);

    while(!temp2.empty())
    {
        cout<<temp2.top()<<" ";
        temp2.pop();
    }cout<<endl;

    cout<<"Reversed Stack Using Rec: ";
    reverseStackRec(s);
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    } cout<<endl;

    // Check for balanced paranthesis(){}[] 
    string str = "{([])}";
    if(isValid(str))
        cout<<"Balanced Paranthesis"<<endl;
    else
        cout<<"Unbalanced Paranthesis"<<endl;

    // Stock span problem
    // Lonegst spa till price[i]<=price[i+1]
    cout<<"Stock Span Problem: ";
    int price[]= {100, 80, 60, 70, 60, 75, 85};
    int n = 7;

    vector<int> ans = calculateSpan(price,n);
    for(auto x: ans)
        cout<<x<<" ";
    cout<<endl;
    vector<int> heights = {2,1,5,6,2,3};
    cout<<"Max Rectangle Area: "<<Histogram(heights)<<endl;

    // next greater element see leetcode or GFG

    //max Length of valid parenthesis in a string
    str = "()(()";
    cout<<"Max Length valid string: "<<findMaxLen(str)<<endl;
    

    return 0;
}
