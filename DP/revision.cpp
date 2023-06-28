// Dynamic Programming Notes::
#include<iostream>
#include<climits>
#include<bits/stdc++.h>
using namespace std;

//Bottom Up
int min_steps_one(int n)
{
    int dp[n+1]={0};
    dp[1] = 0;
    for(int i=2;i<=n;i++)
    {
        int op1,op2,op3; 
        op1 = op2 = op3 = INT_MAX;
        op1 = dp[i-1];
        if(i%2==0)
            op2 = dp[i/2];
        if(i%3==0)
            op3 = dp[i/3];
        dp[i] = min({op1,op2,op3})+1;
    }
    return dp[n];
}
//Coin Change Bottom up code:--
// Minimum no of coins required
int min_coin_change(int coins[],int n,int target)
{
    int dp[target+1]={0};

    for(int i=1;i<=target;i++)
    {
        dp[i] = INT_MAX;
        for(int k=0;k<n;k++)
        {
            if(i-coins[k]>=0 && dp[i-coins[k]]!=INT_MAX)
            {
                dp[i] = min(dp[i],dp[i-coins[k]]+1);
            }
        }
    }
    return dp[target]==INT_MAX?-1:dp[target];
}

//Coin Change Top Down Code:--
// Minimum no of coins req
int min_coin_change2(int coins[],int target,int n,int dp[])
{
    if(target==0)
        return 0;
    if(dp[target]!=0)
        return dp[target];
    
    int coin_no = INT_MAX;
    for(int i=0;i<n;i++)
    {
        if(target-coins[i]>=0)
        {
            coin_no = min(coin_no,1+min_coin_change2(coins,target-coins[i],n,dp));
        }
    }
    return dp[target] = coin_no;
}
// Maximum no of ways coin change problem
// Time: O(N^2)
long long int count( int S[], int m, int n )
    {
       long long int dp[m+1][n+1];
       
       for(int i=0;i<=m;i++)
            dp[i][0] = 1;
            
       for(int i=1;i<=n;i++)
            dp[0][i] = 0;
        
       for(int c=1;c<=m;c++)
       {
           for(int amt=1;amt<=n;amt++)
           {
               dp[c][amt] = dp[c-1][amt];
               if(amt-S[c-1]>=0)
               {
                   dp[c][amt] += dp[c][amt-S[c-1]];
               }
           }
       }
       return dp[m][n];
    }

// Selling Wines Problem 
//Top Down Approach---
int max_wines_profit(int wines[],int yr,int i,int j,int dp[][200])
{
    if(i>j)
        return 0;
    if(dp[i][j]!=0)
        return dp[i][j];
    
    int op1 = wines[i] * yr + max_wines_profit(wines,yr+1,i+1,j,dp);
    int op2 = wines[j] * yr + max_wines_profit(wines,yr+1,i,j-1,dp);

    return dp[i][j] = max(op1,op2);
}

//Wines Problem
//Bottom up approach
int max_wines_profit2(int wines[],int n)
{
    int dp[200][200]={0};

    for(int k=0;k<n;k++)
    {
        int i=0,j=k;
        while(i<n && j<n)
        {
            int y = n-(j-i);
            if(i==j)
                dp[i][j] = wines[i] * y;
            else
                dp[i][j] = max(wines[i] * y + dp[i+1][j] , wines[j] * y + dp[i][j-1]);
            i++;j++;
        }
    }
    return dp[0][n-1];
}

//Maximum Sum Subarray:--
//Dynamic Programming based approach

int max_sum_subarray(int arr[],int n)
{
    int dp[100]={0};
    dp[0] = arr[0]>0?arr[0]:0;
    int max_so_far = 0;
    for(int i=1;i<n;i++)
    {
        dp[i] = dp[i-1] + arr[i];
        if(dp[i]<0)
            dp[i] = 0;
        max_so_far = max(dp[i],max_so_far);
    }
    return max_so_far;
}

//Kadanes Algo for max sum subarray
//Also check if all elements are -ve we need to pick min or 0
int kadanes(int arr[],int n)
{
    int curr_sum = 0;
    int max_so_far = 0;

    for(int i=0;i<n;i++)
    {
        curr_sum += arr[i];
        if(curr_sum<0)
            curr_sum=0;
        max_so_far = max(curr_sum,max_so_far);
    }
    return max_so_far;
}

//Ladders Top down Problem:--
//Time Complexity -- O(n.k)
int ladder_top_down(int target,int k,int dp[])
{
    if(target==0)
        return 1;
    if(dp[target]!=0)
        return dp[target];
    
    int ways=0;
    for(int i=1;i<=k;i++)
    {
        if(target-i>=0)
            ways += ladder_top_down(target-i,k,dp);
    }
    return dp[target] = ways;
}

//Ladder Problem improved O(n) complexity
//Sliding Window Concept:
int ladders_optimised(int target,int k)
{
    int dp[1000]={0};
    dp[0] = dp[1] = 1;
    int curr_sum=0;
    for(int i=2;i<=k;i++)
        dp[i] = 2 * dp[i-1];

    for(int i=k+1;i<=target;i++)
        dp[i] = 2*dp[i-1] - dp[i-k-1];
    return dp[target];
}

int rod_cutting_problem(int rod_price[],int rod_length,int dp[])
{
    if(rod_length<=0)
        return 0;
    if(dp[rod_length]!=0)
        return dp[rod_length];

    int maxprofit = 0;
    for(int i=1;i<=rod_length;i++)
    {
        int netprofit = rod_price[i] + rod_cutting_problem(rod_price,rod_length-i,dp);
        maxprofit = max(maxprofit,netprofit);
    }
    return dp[rod_length] = maxprofit;
}

int rod_cutting_bu(int rod_price[],int rod_length)
{
    int dp[1000]={0};

    for(int len =1;len<=rod_length;len++)
    {
        int best=0;
        for(int cut=1;cut<=len;cut++)
        {
            int profit = rod_price[cut] + dp[len-cut];  
            best = max(profit,best);  
        }
        dp[len] = best;
    }
    return dp[rod_length];
}

//Time: O(N^2) Space: O(N^2)
//2D DP based approach
// LCS(longest common subseq)
int Longest_SubSeq_Length(string str,string pattern)
{
    int len=0;
    int str_len = str.length();
    int pat_len = pattern.length();

    int dp[str_len+1][pat_len+1];
    memset(dp,0,sizeof(dp));

    for(int i=1;i<=str_len;i++)
    {
        for(int j=1;j<=pat_len;j++)
        {
            if(str[i-1]==pattern[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);  
        }
    }   
    return dp[str_len][pat_len];
}

//O(N^2) solution for LIS (DP approach)
int LIS1(int seq[],int no)

{
    int dp[no];
    memset(dp,0,sizeof(dp));

    for(int i=0;i<no;i++)
    {
        int best = 1; //Every Single element can be LIS
        for(int j=0;j<i;j++)
        {
            if(seq[j]<seq[i])
                best = max(dp[j]+1,best);
        }
        dp[i] = best; 
    }

    int lis = 0;
    for(int i=0;i<no;i++)
    {
        // cout<<dp[i]<<" "; 
        lis = max(lis,dp[i]);
    }
    return lis;
}

int LIS2(int seq[],int no)
{
    int dp[no+1];
    dp[0] = INT_MIN;
    for(int i=1;i<=no;i++)
        dp[i] = INT_MAX;

    for(int i=0;i<no;i++)
    {
        for(int len=0;len<no;len++)
        {
            if(dp[len]<seq[i] && seq[i]<dp[len+1])
                dp[len+1] = seq[i];
        }
    }
    int lis=0;
    // for(int i=0;i<=no;i++)
    //     cout<<dp[i]<<" ";
    for(int i=1;i<=no;i++)
    {
        if(dp[i]!=INT_MAX)
            lis = i;
    }
    return lis;
}

int LIS3(int seq[],int no)
{
    int dp[no+1];
    dp[0] = INT_MIN;
    for(int i=1;i<=no;i++)
        dp[i] = INT_MAX;

    for(int i=0;i<no;i++)
    {
        int len = upper_bound(dp,dp+no+1,seq[i]) - dp;
        if(dp[len-1]<seq[i] && seq[i]<dp[len])
            dp[len] = seq[i];
    }

    int lis=0;
    for(int i=1;i<=no;i++)
    {
        if(dp[i]!=INT_MAX)
            lis = i;
    }
    return lis;
}

int Catalan(int no)
{
    int dp[no+1];
    dp[0]=dp[1]=1;

    for(int i=2;i<=no;i++)
    {
        dp[i]=0;
        for(int j=0;j<i;j++)
        {
            dp[i] += dp[j] * dp[i-j-1];
        }
    }
    // for(int i=0;i<=no;i++)
    //     cout<<dp[i]<<" ";
    return dp[no];
}

// Friends can come single or in pair
// Remember to take mod
int countFriendsPairings(int n) 
{ 
    int dp[n+1];
    dp[1]=1;
    dp[2]=2;
    int mod = 1e9+7;
    for(long int i=3;i<=n;i++)
    {
       dp[i] = (dp[i-1]%mod + ((i-1)%mod * dp[i-2]%mod)%mod)%mod;
    }
    // for(int i=1;i<=n;i++)
    //     cout<<dp[i]<<" ";
    return dp[n];
}

int Knapsack(int no,int wt[],int val[],int cap)
{
    int dp[no+1][cap+1];
    memset(dp,0,sizeof(dp));

    for(int i=1;i<=no;i++)
    {
        for(int j=1;j<=cap;j++)
        {
            if(wt[i-1]<=j)
                dp[i][j] = max(val[i-1] + dp[i-1][j-wt[i-1]],dp[i-1][j]);
            else
                dp[i][j] = dp[i-1][j];
        }   
    }
    return dp[no][cap];
}

// Maximum Diff of zeros and ones in binary string
// Any subpart can be taken
//  11000010001=>6
// from index 2 to 9
int maxSubstring(string S)
{
	    // Your code goes here
	    int one_count=0;
	    for(int i=0;i<S.length();i++)
	        one_count += (S[i]=='1')?1:0;
	    int sum=0;
	    int max_diff=0;
	    for(int i=0;i<S.length();i++)
	    {
	        int temp = S[i]=='0'?1:-1;
	        sum += temp;
	        max_diff = max(sum,max_diff);
	        if(sum<0)
	            sum=0;
	    }
	    if(one_count==S.length())
	        return -1;
	    else
	        return max_diff;
}

// Minimum no of jumps to reach end
// jump could be taken of amt arr[i] from position i
// 1 3 5 8 9 2 6 7 6 8 9
// Ans=>3
 int minJumps(int arr[], int n)
    {
        // Your code here
        int curr_far=0,jumps=0;
        int curr_end=0;
        for(int i=0;i<n;i++)
        {
            curr_far = max(curr_far,i+arr[i]);
            if(i==curr_end)
            {
                jumps++;
                curr_end = curr_far;
            }
            if(curr_end>=n-1)
                break;
        }
        if(curr_end<n-1)
            return -1;
        return jumps;
    }

// Minimum removals from array to make max – min <= K
// Very good question follow gfg for O(N^2)/(NlogN)/(N) codes
// impressive problem to solve
// https://www.geeksforgeeks.org/minimum-removals-array-make-max-min-k/
int removals(int arr[],int n,int k)
{
    sort(arr,arr+n);
    int dp[n];
    memset(dp,-1,sizeof(dp));
    dp[0]=0;
    int ans=n-1;
    for(int i=1;i<n;i++)
    {
        dp[i] = i;
        int j = dp[i-1];
        while(j!=i && arr[i]-arr[j]>k)
            j++;
        dp[i] = min(dp[i],j);
        ans = min(ans,n-(i-j+1));
    }
    return ans;
}
//////////////// Grid Based DP///////////////

int MinCostPath(int path[][200],int r,int c)
{
    for(int i=1;i<r;i++)
        path[i][0] += path[i-1][0]; 
    for(int j=1;j<c;j++)
        path[0][j] += path[0][j-1];

    for(int i=1;i<r;i++)
    {
        for(int j=1;j<c;j++)
        {
            path[i][j] += min(path[i-1][j],path[i][j-1]);
        }
    }
    return path[r-1][c-1];
}

int total_ways(int r,int c)
{
    int ways[r][c];
    memset(ways,0,sizeof(ways));
    for(int i=0;i<r;i++)
        ways[i][0] = 1;
    for(int j=1;j<c;j++)
        ways[0][j] = 1;
    for(int i=1;i<r;i++)
    {
        for(int j=1;j<c;j++)
        {
            ways[i][j] = ways[i-1][j] + ways[i][j-1];
        }
    }
    return ways[r-1][c-1];
}

int main() 
{
    int dp1[1000]={0};
    int dp[200][200]={0};
    int k;
    // Minimum Steps to one :--
    // Each step jump 1x 2x or 3x steps:--
    int dest;
    cin>>dest;
    cout<<"Minimum steps to reach one: "<<min_steps_one(dest)<<endl;

    //Min Coin Change Problem :--
    int type;
    cin>>type;
    int coins[type];
    for(int i=0;i<type;i++)
        cin>>coins[i];
    int target;
    cin>>target;
    cout<<"No of Coins Needed: "<<min_coin_change(coins,type,target)<<endl;

    //Top Down Code Coin Change
    cout<<"No of Coins Needed(top_down): "<<min_coin_change2(coins,target,type,dp1)<<endl;

    //Wines Bottle Problem
    //Max price one could get after certain yrs selling wines from extreme ends

    int no;
    cin>>no;
    int wines[no];
    
    for(int i=0;i<no;i++)
    {
        cin>>wines[i];
    }
    cout<<"Max Profit Selling Wines: "<<max_wines_profit(wines,1,0,no-1,dp)<<endl;
    cout<<"Max Profit Wines BottomUP: "<<max_wines_profit2(wines,no)<<endl;

    //Maximum Subarray Sum Problem:-
    cin>>no;
    int arr[no];
    for(int i=0;i<no;i++)
    {
        cin>>arr[i];
    }
    cout<<"Maximum Sum Subarray: "<<max_sum_subarray(arr,no)<<endl;
    cout<<"Kadanes SubarrSum: "<<kadanes(arr,no)<<endl;

    //Ladders Problem
    //Output ways to reach position n taking max of k steps at a time
    memset(dp1,0,sizeof(dp1));
    cin>>target;
    cin>>k;
    cout<<"Ladder Total Ways O(nk): "<<ladder_top_down(target,k,dp1)<<endl;
    cout<<"Ladder Optimised O(n): "<<ladders_optimised(target,k)<<endl;

    //Rod Cutting Problem: Time: O(N^2)
    //Follow GFG problem as well for rod cutting
    memset(dp1,0,sizeof(dp1));
    int totlength;
    cin>>totlength;
    int rod_price[totlength+1];
    for(int i=1;i<=totlength;i++)
        cin>>rod_price[i];
    cout<<"Max Profit Selling Rod(TD): "<<rod_cutting_problem(rod_price,totlength,dp1)<<endl;
    memset(dp1,0,sizeof(dp1));
    cout<<"Max Price Selling Rod(BU): "<<rod_cutting_bu(rod_price,totlength)<<endl;

    //Longest Common SubSequence
    //Important (explaination practice well)
    string str,pattern;
    cin>>str>>pattern;
    cout<<"Longest Common SubSeq: "<<Longest_SubSeq_Length(str,pattern)<<endl;

    //Longest Increasing SubSequence
    cin>>no;
    int seq[no];
    for(int i=0;i<no;i++)
        cin>>seq[i];
    cout<<"Longest Increasing Subseq Length O(N^2): "<<LIS1(seq,no)<<endl;
    cout<<"Longest Increasing SubSeq Length O(N^2):"<<LIS2(seq,no)<<endl;
    //Applying Binary Search on LIS2
    cout<<"Longest Increasing SubSeq Length O(NlogN):"<<LIS3(seq,no)<<endl;

    // Catalan Number
    // Finding nth Catalan number
    cin>>no;
    cout<<"Nth Catalan No: "<<Catalan(no)<<endl;

    cin>>no;
    cout<<"Ways to Attend Party: "<<countFriendsPairings(no)<<endl;

    //0-1 Knapsack and its Derivative
    int cap;
    cin>>no>>cap;
    int val[no];
    int wt[no];
    for(int i=0;i<no;i++)
        cin>>wt[i];
    for(int i=0;i<no;i++)
        cin>>val[i];
    
    cout<<"Max Profit Selling(Knapsack): "<< Knapsack(no,wt,val,cap)<<endl;
    

    ////////////Grid Based DP/////////////
    cout<<"/////////Grid Based DP//////////"<<endl;
    //Min Path Sum(right and down direction only)
    int r,c;
    cin>>r>>c;
    int path[200][200];
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
            cin>>path[i][j];
    }
    cout<<"Minimum Path Sum:"<<MinCostPath(path,r,c)<<endl;

    //Total No of Ways to Reach (m,n) in matrix
    cin>>r>>c;
    memset(path,0,sizeof(path));
    cout<<"Ways To Reach Corner: "<<total_ways(r,c)<<endl;

    return 0;
}

// Input
// 5
// 3
// 1 3 5
// 9
// 5
// 2 3 5 1 4
// 10
// -3 2 5 -1 6 3 -2 7 -5 2
// 4 3(ladder problem)
// 4(rod cutting problem)
// 2 3 2 5
// aggtab(longest common subsequence)
// gxtayb
// 8(Longest Increasing Subseq)
// 1 5 2 3 4 9 6 10
// 4(Catalan No)
// 4(Friends Pairing Problem)
// 3 3(row column)
// 1 2 3(matrix)
// 4 8 2
// 1 5 3
// 3 3(row col)


//Must do problems not in course
//1. Coin Change Problem(https://practice.geeksforgeeks.org/problems/coin-change2448/1)
//2. Target Sum(https://leetcode.com/problems/target-sum/)
//3. Count no of subset with given diff(covered in 2 only)  