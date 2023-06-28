#include <iostream>
#include <vector>
using namespace std;

//Implementing Heap DS
class Heap{
    vector<int> v;
    bool minHeap;
    bool compare(int a,int b)
    {
        if(minHeap)
            return a < b;
        else
            return a > b;
    }

    void heapify(int idx)
    {
        int left = 2*idx;
        int right = 2*idx + 1;
        int min_idx = idx,last = v.size()-1;

        if(left <= last && compare(v[left],v[min_idx]))
            min_idx = left;
         
        if(right <= last && compare(v[right],v[min_idx]))
            min_idx = right;
        
        if(min_idx != idx)
        {
            swap(v[min_idx],v[idx]);
            heapify(min_idx);
        }
        
    }

public:
    Heap(int default_size = 10,bool type=true)
    {
        v.reserve(default_size);
        v.push_back(-1);
        minHeap = type;
    }

    int top()
    {
        return v[1];
    }

    bool empty()
    {
        return v.size()==1;
    }

    void push(int n)
    {
        v.push_back(n);
        int idx = v.size()-1;
        int parent = idx/2;
        while(idx>1 && compare(v[idx],v[parent]))
        {
            swap(v[idx],v[parent]);
            idx = parent;
            parent = idx/2;
        }
    }

    void pop()
    {
        int idx = v.size()-1;
        swap(v[1],v[idx]);
        v.pop_back();
        heapify(1);
    }

    void print()
    {
        for(auto e: v)
            if(e!=-1)
                cout<<e<<" ";
        cout<<endl; 
    }
};

int main() 
{
    Heap h(10,false);
    int n;
    cin>>n;
    while(n--)
    {
        int d;
        cin>>d;
        h.push(d);
    }

    h.print();
    h.pop();
    h.print();
    h.pop();
    h.print();

    return 0;
}

// Input :--
// 5
// 4 8 9 2 7