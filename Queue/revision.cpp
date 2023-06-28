#include<iostream>
#include<queue>
using namespace std;

// Implementaion using an array
class Queue{
    int *arr;
    int f,r,cs,ms;
public:
    Queue(int ds=5)
    {
        arr = new int[5];
        f = 0;
        ms = ds;
        r = ms-1;
        cs = 0;
    }

    bool full()
    {
        return cs==ms;
    }

    bool empty()
    {
        return cs==0;
    }

    void push(int data)
    {
        if(!full())
        {
            r = (r+1)%ms;
            arr[r] = data;
            cs++;
        }
    }

    void pop()
    {
        if(!empty())
        {
            f = (f+1)%ms;
            cs--;
        }
    }

    int front()
    {
        return arr[f];
    }

    ~Queue(){
        if(arr!=NULL)
        {
            delete [] arr;
            arr = NULL;
        } 
    }
};

class Stack{
    queue<int> q1,q2;
public:
    void push(int d)
    {
        q1.push(d);
    }
    void pop()
    {
        if(q1.empty())
            return;
        
        while(q1.size()>1){
            int element = q1.front();
            q2.push(element);
            q1.pop();
        }
        q1.pop();
        // Swap q1 and q2
        swap(q1,q2);
    }

    int top()
    {
        while(q1.size()>1)
        {
            q2.push(q1.front());
            q1.pop();
        }
        int element = q1.front();
        q2.push(element);
        q1.pop();
        swap(q1,q2);

        return element;
    }

    int size()
    {
        return q1.size() + q2.size(); 
    }

    bool empty()
    {
        return size()==0;
    }

};

int main() 
{
    queue<char> q;
    int freq[27]={0}; // Frequency table 

    //1. First non-repeating character in running stream of numbers:
    char ch;
    cin>>ch;

    while(ch!='.')
    {
        q.push(ch);
        freq[ch-'a']++;

        while(!q.empty() && freq[q.front()-'a']>1)
            q.pop();
        
        if(!q.empty())
            cout<<q.front()<<" ";
        else 
            cout<<"-1 "; 
        cin>>ch;
    }
    cout<<endl;
    // 2. Implement Stack Using two Queues:
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);

    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }

    // Implement Queue using two Stack

    // See interleave queue elements using stack in gfg as well

    // Circular Array Petrol Pumps(good question)
    
    return 0;
}

// Input
// a a b c c b c d .