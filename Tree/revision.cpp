/////////// Tree Notes /////////////////
#include<iostream>
#include<queue>
#include<bits/stdc++.h>
using namespace std;

class node{
public:
    int data;
    node *left;
    node *right;

    node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};


class group{
public:
    int height;
    int diameter;
};

node* buildnode()
{
    int d;
    cin>>d;
    if(d==-1)
        return NULL;

    node *root = new node(d);
    root->left = buildnode();
    root->right = buildnode();

    return root;
}

void preorder(node *root)
{
    if(root==NULL)
        return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(node *root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

void bfs(node *root)
{
    queue<node *> q;
    q.push(root);
    while(!q.empty())
    {
        node *front = q.front();
        cout<<front->data<<" ";
        q.pop();
        if(front->left)
            q.push(front->left);
        if(front->right)
            q.push(front->right);
    }
}

int height(node *root)
{
    if(root==NULL)
        return 0;
    
    int lt_ht = height(root->left);
    int rt_ht = height(root->right);

    return max(lt_ht,rt_ht)+1; 
}

int sum(node *root)
{
    if(root==NULL)
        return 0;
    int l_sum = sum(root->left);
    int r_sum = sum(root->right);

    return root->data + l_sum + r_sum;
}

int count(node *root)
{
    if(root==NULL)
        return 0;
    int lt_count = count(root->left);
    int rt_count = count(root->right);

    return 1 + lt_count + rt_count;  
}

void printkthlevel(node *root,int k)
{
    if(root==NULL)
        return; 
    if(k==0)
    {
        cout<<root->data<<" ";
        return; 
    }
    printkthlevel(root->left,k-1);
    printkthlevel(root->right,k-1);
    return;
}

void printAllLevels(node *root)
{
    int ht = height(root);
    for(int i=0;i<ht;i++)
    {
        printkthlevel(root,i);
        cout<<endl;
    }
}

//Print Level Order but not in seperate lines//O(N)
void LvlOrderNoLine(node *root)
{
    queue<node *>q;
    q.push(root);
    while(!q.empty())
    {
        node *f = q.front();
        cout<<f->data<<",";
        q.pop();
        if(f->left)
            q.push(f->left);
        if(f->right)
            q.push(f->right);
    }
}

//Print Level Order Traversal Each Level Seperate Of Tree using Queue
void LevelOrder(node *root)
{
    queue<node *> q;
    if(root==NULL)  
        return;
    
    q.push(root);
    q.push(NULL);

    while(!q.empty())
    {
        node *front = q.front();
        if(front==NULL)
        {
            q.pop();
            cout<<endl;
            if(!q.empty())
                q.push(NULL);
        }
        else
        {
            cout<<front->data<<" ";
            q.pop();
            if(front->left)
                q.push(front->left);
            if(front->right)
                q.push(front->right);
        }
    }
}

//Diameter of tree
int diameter1(node *root)
{
    if(root==NULL)
        return 0;
    
    int ht_left = height(root->left);
    int ht_right = height(root->right);

    int op1 = ht_left + ht_right;
    int op2 = diameter1(root->left);
    int op3 = diameter1(root->right);
    return max({op1,op2,op3});
}

group diameterOptimised(node *root)
{
    group p;
    if(root==NULL)
    {
        p.height=0;
        p.diameter=0;
        return p;
    }

    group left = diameterOptimised(root->left);
    group right = diameterOptimised(root->right);
    p.height = max(left.height,right.height)+1;
    p.diameter = max({left.diameter,right.diameter,left.height+right.height}); 
    return p;
}

//Replace all nodes by sum of its child nodes
int replacesum(node *root)
{
    if(root==NULL)
        return 0;
    if(root->left==NULL && root->right==NULL)
        return root->data;
    
    int left_sum = replacesum(root->left);
    int right_sum = replacesum(root->right);

    int temp = root->data;
    root->data = left_sum + right_sum;
    return temp + root->data;
}

class HBPair{
public:
    int ht;
    bool bal;
    HBPair()
    {
        ht=0;
        bal=false;
    }
};

HBPair isBalanced(node* root)
{
    HBPair p;
    if(root==NULL)
    {
        p.ht = 0;
        p.bal=true;
        return p;
    }

    HBPair left = isBalanced(root->left);
    HBPair right = isBalanced(root->right);
   
    p.ht = max(left.ht,right.ht)+1;
    if(abs(left.ht-right.ht)<=1 && left.bal && right.bal)
        p.bal=true;
    else
        p.bal=false;
    return p;
}

//Build Height Balanced Tree from an array

node* buildBalancedTree(int arr[],int s,int e)
{
    if(s>e)
        return NULL;
    
    int mid = (s+e)/2;
    node *root = new node(arr[mid]);
    root->left = buildBalancedTree(arr,s,mid-1);
    root->right = buildBalancedTree(arr,mid+1,e);

    return root;
}

//Building Binary Tree From inorder and preorder Traversal
node* buildTreeInPre(int inor[],int preor[],int s,int e)
{
    static int k=0;
    if(s>e)
        return NULL;

    node* root = new node(preor[k]);  
    int index=-1;
    for(int j=s;j<=e;j++)
    {
        if(inor[j]==preor[k])
        {
            index = j;
            break;
        }
    }
    k++;
    root->left = buildTreeInPre(inor,preor,s,index-1);
    root->right = buildTreeInPre(inor,preor,index+1,e);
    return root; 
}

//Right View of Binary Tree(Top to Bottom)
void printright(node *root,int lvl,int &maxlvl)
{
    if(root==NULL)
        return;
    if(maxlvl<lvl)
    {
        cout<<root->data<<" ";
        maxlvl = lvl;
    }
    printright(root->right,lvl+1,maxlvl);
    printright(root->left,lvl+1,maxlvl);
}


//Find all nodes at distance k from a given node 

int printatDistk(node* root,node *target,int k)
{
    if(root==NULL)
        return -1;
    if(root==target)
    {
        printkthlevel(root,k);
        return 0;
    }

    int dl = printatDistk(root->left,target,k);
    if(dl!=-1)
    {
        if(dl+1==k)
            cout<<root->data<<" ";
        else
            printkthlevel(root->right,k-2-dl);
        return 1+dl; 
    }

    int dr = printatDistk(root->right,target,k);
    if(dr!=-1)
    {
        if(dr+1==k)
            cout<<root->data<<" ";
        else
            printkthlevel(root->left,k-2-dr);
        return 1+dr; 
    }
    return -1; //node not present
}

//Lowest Common Ancestor(LCA)
//Both a and b present on opposite side is point

node* LCA(node* root,int a,int b)
{
    if(root==NULL)
        return NULL;
    if(root->data==a || root->data==b)
        return root;
    
    node *leftans = LCA(root->left,a,b);
    node *rightans = LCA(root->right,a,b);

    if(leftans!=NULL && rightans!=NULL)
        return root;
    
    if(leftans!=NULL)
        return leftans;
    return rightans;
}

class sumpair{
public:
    int branchsum;
    int maxsum;

    sumpair()
    {
        branchsum = 0;
        maxsum = INT_MIN;
    }
};

sumpair maxsumpath(node *root)
{
    sumpair s;
    if(root==NULL)
        return s;

    sumpair left = maxsumpath(root->left);
    sumpair right = maxsumpath(root->right);

    int op1 = root->data;
    int op2 = left.branchsum + root->data;
    int op3 = right.branchsum + root->data;
    int op4 = root->data + left.branchsum + right.branchsum;

    int curr_sum = max({op1,op2,op3,op4});
    s.branchsum = max({left.branchsum,right.branchsum,0})+root->data;
    s.maxsum = max({curr_sum,left.maxsum,right.maxsum});

    return s;
}

int search(node *root,int target,int depth)
{
    if(root==NULL)
        return -1;
    if(root->data==target)
        return depth;
    int left = search(root->left,target,depth+1);
    if(left!=-1)
        return left;
    return search(root->right,target,depth+1);
}

int findMinDist(node *root,int a,int b)
{
    node* lca = LCA(root,a,b);
    if(lca==NULL)
        return -1;
    else
    {
        int depth_a = search(lca,a,0);
        int depth_b = search(lca,b,0);
        return depth_a + depth_b;
    }
}

//------------Revision of BST--------------------

node* insertInBST(node *root,int data)
{
    if(root==NULL)
        return new node(data);
    if(data < root->data)
        root->left = insertInBST(root->left,data);
    else
        root->right = insertInBST(root->right,data);
    return root;
}

node *buildBST()
{
    int d;
    cin>>d;
    node *root = NULL;
    while(d!=-1)
    {
        root = insertInBST(root,d);
        cin>>d;
    }
    return root;
}

bool searchBST(node* root,int data)
{
    if(root==NULL)
        return false;
    if(root->data == data)
        return true;
    
    if(root->data > data)
        return searchBST(root->left,data);
    else
        return searchBST(root->right,data);
}

//Deletion of a Node in BST
node* DeleteInBST(node *root,int data)
{
    if(root==NULL)
        return NULL;
    else if(root->data == data)
    {
        //Three Cases;
        //0 child case
        if(root->left==NULL && root->right==NULL)
        {
            delete root;
            return NULL;
        }
        //1 child case
        else if(root->left!=NULL && root->right==NULL)
        {
            node* temp = root->left;
            delete root;
            return temp;
        }
        else if(root->right!=NULL && root->left==NULL)
        {
            node* temp = root->right;
            delete root;
            return temp;
        }
        //2 child case
        else
        {
            node* replace = root->right;
            while(replace->left!=NULL)
                replace = replace->left;
            root->data = replace->data;
            root->right = DeleteInBST(root->right,replace->data);
            return root;
        }
    }
    else if(data < root->data)
    {
        root->left = DeleteInBST(root->left,data);
        return root;
    }
    else 
    {
        root->right = DeleteInBST(root->right,data);
        return root;
    }
}

bool isBST(node *root,int minV=INT_MIN,int maxV=INT_MAX)
{
    if(root==NULL)
        return true;
    if(root->data>=minV && root->data<=maxV && isBST(root->left,minV,root->data) && isBST(root->right,root->data,maxV))
        return true;
    return false;
}

int main() 
{
    node *root = buildnode();
    //preorder traversal
    cout<<"PreOrder:";
    preorder(root);
    cout<<endl;
    //inorder traversal
    cout<<"Inorder:";
    inorder(root);
    cout<<endl;
    //BFS traversal 
    cout<<"BFS:";
    bfs(root);
    cout<<endl;
    //Height of tree
    cout<<"Height of Tree:";
    cout<<height(root)<<endl;
    //Print kth level nodes
    cout<<"Kth Level:";
    printkthlevel(root,3);
    cout<<endl;
    //Sum of all nodes
    cout<<"Sum of Nodes:";
    cout<<sum(root)<<endl;
    //Count of nodes
    cout<<"Count of Nodes:";
    cout<<count(root)<<endl;
    //Print Level Order Traversal
    printAllLevels(root);
    //Print Level Order Using Queue
    LevelOrder(root);
    //Print LvlOrder No Line change
    LvlOrderNoLine(root);
    cout<<endl;
    //Diameter O(N2)
    cout<<"Dia of tree: "<<diameter1(root)<<endl;

    //Diameter Optimised
    group ans = diameterOptimised(root);
    cout<<"Height Optm: "<<ans.height<<endl;
    cout<<"Diameter Optm: "<<ans.diameter<<endl;

    //Replace nodes by its child nodes sum
    // replacesum(root);
    // cout<<endl;
    cout<<"LevelOrder:";
    LvlOrderNoLine(root);
    cout<<endl;
    cout<<"Balanced Tree or not:";
    HBPair res = isBalanced(root);
    if(res.bal)
        cout<<"Balanced"<<endl;
    else 
        cout<<"Not Balanced"<<endl;
    int num;
    cin>>num;
    int arr[num];
    for(int i=0;i<num;i++)
        cin>>arr[i];
    //Build height balanced tree from array
    cout<<"Balanced Tree from array:-"<<endl;
    node *Bal_Tree = buildBalancedTree(arr,0,num-1);
    LevelOrder(Bal_Tree);

    //Build Tree from inorder and preorder traversal
    cin>>num;
    int inor[num];
    int preor[num];
    for(int i=0;i<num;i++)
        cin>>inor[i];
    for(int j=0;j<num;j++)
        cin>>preor[j];

    //Build Tree from inrder and preorder traversal
    cout<<"Tree from pre and inord"<<endl;
    node *temp = buildTreeInPre(inor,preor,0,num-1);
    LevelOrder(temp);
    int max_val = -1;
    cout<<"Right View: ";
    printright(temp,0,max_val);
    cout<<endl;
    // int ht = height(temp);

    node *t = root->left->left;
    //Nodes at distance k from given target node
    cout<<"Distance k from target node: ";
    printatDistk(root,t,3);
    cout<<endl;
    //Lowest Common ancestor
    node *lca = LCA(root,8,9);
    cout<<"LCA of Nodes: "<<lca->data<<endl;
    //Build new tree
    root = buildnode();
    cout<<"New Tree Build: ";
    bfs(root);
    cout<<endl;
    LevelOrder(root);

    //Maixmum path sum
    sumpair p = maxsumpath(root);
    cout<<"Maxm path sum: "<<p.maxsum<<endl;

    //Minimum Distance between the two nodes in a binary tree
    int distance = findMinDist(root,2,4);
    cout<<"Min Dist Betn Nodes: "<<distance<<endl;

    //BST Starts here----------------------------
    root = buildBST();
    bfs(root);
    cout<<endl;
    //inorder traversal of bst is sorted
    inorder(root);
    cout<<endl;
    preorder(root);
    cout<<endl;
    // searching in BST
    cout<<"Search In BST:";
    bool found = searchBST(root,6);
    if(found)
        cout<<"Element found in BST"<<endl;
    else
        cout<<"Not found in BST"<<endl;

    cout<<"Deletion in BST:"<<endl;
    root = DeleteInBST(root,3);
    LevelOrder(root);
    inorder(root);
    cout<<endl;
    cout<<"Check BST:";
    if(isBST(root))
        cout<<"Yes";
    else
        cout<<"No";    
    return 0;
}


//-------Input-------
// 1 2 4 6 -1 -1 7 10 -1 -1 11 -1 -1 5 8 -1 -1 9 -1 -1 3 -1 -1
// 7
// 1 2 3 4 5 6 7
// 8
// 3 2 8 4 1 6 7 5
// 1 2 3 4 8 5 6 7
// 10 2 20 -1 -1 1 -1 -1 10 -1 -25 3 -1 -1 4 -1 -1
// 5 3 7 1 6 8 -1