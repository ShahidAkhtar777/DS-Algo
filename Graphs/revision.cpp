//////////// Graph Notes /////////////

#include<iostream>
#include<list>
#include<climits>
#include<unordered_map>
#include<vector>
#include<cstring>
#include<queue>
#include<map>
#include<algorithm>
#include<set>
using namespace std;
int V = 7;
/* Special Section
Cycle detection undirected using BFS
 bool cycle_helper_bfs(int src,vector<bool> &vis,int V,vector<int> adj[])
    {
        vector<int> parent(V,-1);
        queue<int> q;
        q.push(src);
        vis[src] = true;
        
        while(!q.empty())
        {
            int f = q.front();
            q.pop();
            
            for(auto nbr: adj[f])
            {
                if(!vis[nbr])
                {
                    vis[nbr] = true;
                    q.push(nbr);
                    parent[nbr] = f;
                }
                else if(parent[f]!=nbr)
                    return true;
            }
        }
        return false;
    }

    //Using BFS
    bool isCycle(int V,vector<int> adj[])
    {
        vector<bool> vis(V,false);
        for(int i=0;i<V;i++)
        {
            if(!vis[i] && cycle_helper_bfs(i,vis,V,adj))
            {
                return true;
            }
        }
        return false;
    }
*/


//Adjacency List Implementstion of Graph
class Graph{
    unordered_map<int,list<int>> m;
    unordered_map<int,list<int>> rev_graph;
public:
    void addEdge(int x,int y,int dir=false)
    {
        m[x].push_back(y);
        if(!dir)
        m[y].push_back(x);

        rev_graph[y].push_back(x);
    }

    void printAdjList()
    {
        for(auto x: m)
        {
            cout<<"Vertex"<<x.first<<": ";
            for(auto p: x.second)
                cout<<p<<" ";
            cout<<endl;
        }
    }

    //Breadth First Search
    void bfs(int src)
    {
        queue<int> q;
        map<int,bool> visited;
        q.push(src);
        visited[src] = true;
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            cout<<node<<" ";
            for(auto x: m[node])
            {
                if(!visited[x])
                {
                    q.push(x);
                    //Mark that neighbour as visited
                    visited[x] = true;
                }
            }
        }
    }

    //Single source shortest path
    void shortestPath(int src)
    {
        queue<int> q;
        unordered_map<int,int> dist;

        for(auto x: m)
        {
            int node = x.first;
            dist[node] = -1;
        }
        q.push(src);
        dist[src] = 0;

        while(!q.empty())
        {
            int f = q.front();
            q.pop();

            for(auto x: m[f])
            {
                if(dist[x]==-1)
                {
                    q.push(x);
                    dist[x] = dist[f] + 1;
                }
            }
        } 

        for(auto x: m)
        {
            int node = x.first;
            int dis = dist[node];
            cout<<"\t"<<"Node "<<node<<" is at dist "<<dis<<endl;
        }
    }

    //DFS Helper Function
    void dfs_helper(int src,unordered_map<int,bool> &visited,int &count)
    {
        cout<<src<<" ";
        visited[src] = true;
        count++;
        for(auto x: m[src])
        {
            if(!visited[x])
            {
                dfs_helper(x,visited,count);
            }
        } 
    }

    //Depth First Search in Graph
    void dfs(int src)
    {
        unordered_map<int,bool> visited;
        for(auto x: m)
        {
            int p = x.first;
            visited[p] = false;
        }
        int count=0;
        dfs_helper(src,visited,count);
        cout<<"No of Nodes: "<<count;
    }

    //Find Number of Connected Components in a Graph

    void connected_comp(int src)
    {
        unordered_map<int,bool> visited;
        for(auto x: m)
        {
            int node = x.first;
            visited[node] = false;
        }
        int count=0;
        for(auto x: m)
        {
            if(!visited[x.first])
            {
                cout<<"Component "<<count<<"->";
                int noComp=0;
                dfs_helper(x.first,visited,noComp);
                cout<<"Nodes Count: "<<noComp<<endl;
                count++;
            }
        }
    }

    bool cycle_helper(int src,unordered_map<int,bool> &visit,int parent)
    {
        visit[src] = true;
        for(auto nbr: m[src])
        {
            if(!visit[nbr])
            {
                bool cycle_mila = cycle_helper(nbr,visit,src);
                if(cycle_mila)
                    return true;
            }
            else if(nbr!=parent)
                return true;
        }
        return false;
    }
    //using bfs given in top maintaining a parent vector
    //Cycle Detection in an undirected graph
    //Using DFS 
    //See BFS in GFG submission of yours
    bool cycle_present()
    {
        unordered_map<int,bool> visit;
        for(auto x: m)
        {
            int node = x.first;
            visit[node] = false;
        }
       return cycle_helper(0,visit,-1);
    }

    //Check Whether Bipartite Graph or Not
    //Bipartite - Cycle of odd length
    bool bipartite_helper(int src,unordered_map<int,int> &visited,int parent,int colour)
    {
        visited[src] = colour;
        for(auto nbr: m[src])
        {
            if(visited[nbr]==0)
            {
                bool isbipartite = bipartite_helper(nbr,visited,src,3-colour);
                if(!isbipartite)
                    return false;
            }
            else if(nbr!=parent && colour == visited[nbr])
                return false;
        }
        return true;
    }

    //Bipartite graph check
    bool Bipartite()
    {
        unordered_map<int,int> visited;
        for(auto x: m)
        {
            visited[x.first] = 0;
        }
        int colour = 1;
        return bipartite_helper(0,visited,-1,colour);
    }

    //Shortest Cycle in Graph
    void find_shortestcycle(int src,int &ans)
    {
        unordered_map<int,int> visited;
        for(auto x: m)
        {
            visited[x.first] = INT_MAX;
        }
        queue<int> q;
        visited[src] = 0;
        q.push(src);
        while(!q.empty())
        {
            int curr = q.front();
            q.pop();

            for(auto nbr: m[curr])
            {
                if(visited[nbr]==INT_MAX)
                {
                    visited[nbr] = visited[src]+1;
                    q.push(nbr);
                }
                else if(visited[nbr] >= visited[curr])
                {
                    ans = min(ans,visited[nbr]+visited[curr]+1);  
                }
            }
        }
    }

    void topological_helper(int src,unordered_map<int,bool> &visited,list<int> &ordering)
    {
        visited[src] = true;
        for(auto nbr: m[src])
        {
            if(!visited[nbr])
                topological_helper(nbr,visited,ordering);
        }
        ordering.push_front(src);
    }

    //Topological Sort in DAG using DFS
    void TopologicalSort()
    {
        unordered_map<int,bool> visited;
        list<int> ordering;

        for(auto x: m)
        {
            visited[x.first] = false;
        }

        for(auto nbr: m)
        {
            if(!visited[nbr.first])
                topological_helper(nbr.first,visited,ordering);
        }
        for(auto node: ordering)
            cout<<node<<" ";
    }

    //Topological sort using bfs
    //Can be also used for detecting cycle in a directed graph
    //We can count the nodes and if it is more than vertices then its cyclic
    void topological_sort()
    {
        unordered_map<int,int> indegree;
        queue<int> q;
        for(auto x: m)
            indegree[x.first] = 0;

        for(auto x: m)
        {
            int node = x.first;
            for(auto p: m[node])
                indegree[p]++;
        }

        int count=0;//For cycle detection
        for(auto x: m)
        {
            int temp = x.first;
            if(indegree[temp]==0)
            {
                q.push(temp);
            }
        }
        
        while(!q.empty())
        {
            int fr = q.front();
            cout<<fr<<" ";
            q.pop();
            for(auto x: m[fr])
            {
                indegree[x]--;
                if(indegree[x]==0)
                    q.push(x);
                count++;
            }
        }
        cout<<endl;
        cout<<"Using BFS: ";
        if(count<V)
            cout<<"Dir graph is cyclic"<<endl;
        else 
            cout<<"Dir graph is not cycic"<<endl;

    }

    //Cycle Detection in a directed graph
    //we need to track the path as well in this case
    bool dir_cycle_helper(int src,unordered_map<int,bool> &visited,unordered_map<int,bool> &path)
    {
        visited[src] = true;
        path[src] = true;

        for(auto nbr: m[src])
        {
            if(path[nbr] == true)
                return true;
            if(!visited[nbr])
            {
                bool iscyclic = dir_cycle_helper(nbr,visited,path);
                if(iscyclic)
                    return true;
            }
        }

        path[src] = false;
        return false;
    }

    // DFS way to check cycle in directed graph
    bool dir_cyclecheck()
    {
        unordered_map<int,bool> visited;
        unordered_map<int,bool> path;

        for(auto x: m)
        {
            visited[x.first] = path[x.first] = false;
            for(auto p: x.second)
                visited[p] = path[p] = false;
        }

        return dir_cycle_helper(0,visited,path);
    }

    void kosaraju_dfs(int src,unordered_map<int,bool> &visited,vector<int> &order)
    {
        visited[src] = true;
        for(auto nbr: m[src])
        {
            if(!visited[nbr])
                kosaraju_dfs(nbr,visited,order);
        }
        order.push_back(src);
    }

    void kosaraju_dfs2(int src,unordered_map<int,bool> &visited)
    {
        visited[src] = true;
        cout<<src<<" ";
        for(auto nbr: rev_graph[src])
        {
            if(!visited[nbr])
            {
                kosaraju_dfs2(nbr,visited);
            }
        } 
    }

    void Kosaraju_Algo()
    {   
        unordered_map<int,bool> visited;
        vector<int> order;

        for(auto x: m)
            visited[x.first] = false;
        
        for(auto x: m)
        {
            if(!visited[x.first])
                kosaraju_dfs(x.first,visited,order);
        }

        visited.clear();
        
        char component = 'A';
        for(int i=order.size()-1;i>=0;i--)
        {
            if(!visited[order[i]])
            {
                cout<<"\t Component "<<component<<"-->";
                kosaraju_dfs2(order[i],visited);
                cout<<endl;
                component++;
            }
        }
    }
};

class DSU{
    int *parent;
    int *rank;
public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for(int i=0;i<n;i++)
        {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    int find(int i)
    {
        if(parent[i]==-1)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int x,int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        //Union by rank
        if(s1!=s2) 
        {
            if(rank[s1]<rank[s2])
            {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else
            {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

//EdgeList representation of graph useful in kruksal for sorting edges
class graph{
    vector<vector<int>> edgelist;
    unordered_map<int,vector<pair<int,int>>> w_m;
    int V;
public:
    graph(int V)
    {
        this->V = V;
    }

    void addEdge(int x,int y,int w)
    {
        edgelist.push_back({w,x,y});
        w_m[x].push_back({y,w});
    }

    //Finding minimum MST in a directed weighted graph
    int Kruskal_Algo()
    {
        //1.Sort accdn to edges wt
        sort(edgelist.begin(),edgelist.end());

        //Init a DSU
        DSU s(V);
        int ans=0;
        for(auto edge: edgelist)
        {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            if(s.find(x)!=s.find(y))
            {
                s.unite(x,y);
                ans += w;
            }
        }
        return ans;
    }

    void DijkstrasAlgo(int src)
    {
        vector<int> dist(V);
        for(int i=0;i<V;i++)
            dist[i] = INT_MAX;
        
        set<pair<int,int>> s;
        dist[src] = 0;
        s.insert({0,src});
        
        while(!s.empty())
        {
            auto tp = *(s.begin());
            int node = tp.second;
            int node_dist = tp.first;
            s.erase(s.begin());
            
            for(auto nbr: w_m[node])
            {
                if(node_dist + nbr.second < dist[nbr.first])
                {
                    int dest = nbr.first;
                    auto f = s.find({dist[dest],dest});
                    
                    if(f!=s.end())
                        s.erase(f);
                    
                    dist[dest] = node_dist + nbr.second;
                    s.insert({dist[dest],dest});
                }
            }
        }

        for(int i=0;i<V;i++)
        {
            // ans = max(ans,dist[i]); 
            cout<<"Sht Dist fr src to node:"<<i<<"->"<<dist[i]<<endl;
        }
        // if(ans==INT_MAX)
        //     return -1;
        // return ans;
    }
};

//HashMap Representation of a Graph

// class Graph{
//     unordered_map<string,list<pair<string,int>>> l;
// public:
//     void addEdge(string x,string y,bool bidir,int wt)
//     {
//         l[x].push_back({y,wt});
//         if(bidir)
//             l[y].push_back({x,wt});
//     }
//     void printAdjList()
//     {
//         for(auto p: l)
//         {
//             string city = p.first;
//             list<pair<string,int>> nbrs = p.second;
//             cout<<"City"<<city<<"-> ";
//             for(auto nbr: nbrs)
//             {
//                 string dest = nbr.first;
//                 int dist = nbr.second;
//                 cout<<dest<<" "<<dist<<",";
//             }
//             cout<<endl;
//         }
//     }
// };



int main() 
{
    Graph g;
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(2,4);
    g.addEdge(5,6);
    g.addEdge(6,7);
    g.addEdge(8,8);
    g.addEdge(1,4);
    cout<<"BFS Traversal: ";
    g.bfs(1);
    cout<<endl;
    cout<<"Single Source Shortest Path:-"<<endl;
    g.shortestPath(1);
    cout<<"DFS Traversal: ";
    g.dfs(2);
    cout<<endl;
    g.connected_comp(1);

    //Cycle in undirected graph
    bool isCyclic = g.cycle_present();
    cout<<"Check Cycle: ";
    if(isCyclic)
        cout<<"Cyclic"<<endl;
    else 
        cout<<"Not Cyclic"<<endl;    

    //Bipartite Graph or not
    cout<<"Check Bipartite: ";
    bool bipartite = g.Bipartite();
    if(bipartite)
        cout<<"Bipartite Graph!!"<<endl;
    else 
        cout<<"Not Bipartite Graph!!"<<endl;
    
    //Find shortest cycle in a undirected graph:
    int ans = 10;
    for(int i=0;i<=4;i++)
    {
        g.find_shortestcycle(i,ans);
    }

    if(ans!=10)
        cout<<"Shortest Cycle Length: "<<ans<<endl;
    else 
        cout<<"No cycle present"<<endl;
    

    cout<<"\t---Directed Graph Section Starts---"<<endl;
    //Taking directed graph now:
    Graph g2;
    g2.addEdge(1,0,true);
    g2.addEdge(0,2,true);
    g2.addEdge(2,1,true);
    g2.addEdge(0,3,true);
    g2.addEdge(3,5,true);
    g2.addEdge(5,6,true);
    g2.addEdge(6,3,true);
    g2.addEdge(3,4,true);

    //Directed Graph Cyclic or Not:
    cout<<"Directed Graph Cyclic: ";
    bool dir_cycle = g2.dir_cyclecheck();
    if(dir_cycle)
        cout<<"Yes Cyclic"<<endl;
    else 
        cout<<"Not Cyclic"<<endl;

    //Topological Sort--Applicable in DAG:
    cout<<"Topological Sort Using DFS: ";
    g2.TopologicalSort();
    cout<<endl;
    cout<<"Topological Sort Using BFS: ";
    g2.topological_sort();

    //Kosaraju algo to find all strongly connected components in a directed graph
    //Not very intitutive approach
    //Step1 - take graph make a path array
    //Step2 - reversing the graph
    //Step3 - traversing on path array from reverse and make dfs call

    cout<<"Kosaraju Algo Strongly Connected Comp:-"<<endl;
    g2.Kosaraju_Algo();

    //Mimimum Spanning Tree(MST) Section---
    //make edgelist gragh

    graph g3(4);
    g3.addEdge(0,1,1);
    g3.addEdge(1,3,3);
    g3.addEdge(3,2,4);
    g3.addEdge(2,0,2);
    g3.addEdge(0,3,2);
    g3.addEdge(1,2,2);

    //Kruksal Algo(Greedy Algo)--
    //Undirected Graph
    //Step1- Sort edges based on weight
    //Step2- Join edges if they belong to diff set
    //Requires concept of DSU as well 
    cout<<"Kruksal Algo MST Weight: "<<g3.Kruskal_Algo();
    cout<<endl;
    //Prims Algo(Greedy Algo)--



    
    //Dijkstras Algo---
    //SSSP in a directed/undirected weighted graph 
    //with no -ve edges present
    int src = 0;
    cout<<"---Dijkstras Shortest Path Algo :---"<<endl;
    g3.DijkstrasAlgo(src);
    return 0;
}

//No Inputs just run to see all the outputs