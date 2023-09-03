#include<bits/stdc++.h>
using namespace std;
int mod = 1e9+7; 

// Dynamic Programming Revision :-

// Top Down
int minStepsToOne(int steps, int *dp) {
    // Base Case
    if(steps==1)
        return 0;
    if(dp[steps]!=0)
        return dp[steps];

    // Recursive Case
    int op1,op2,op3;
    op1 = op2 = op3 = INT_MAX;

    op1 = minStepsToOne(steps-1, dp);
    if(steps%2==0)
        op2 = minStepsToOne(steps/2, dp);
    if(steps%3==0)
        op3 = minStepsToOne(steps/3, dp);

    return dp[steps] = min({op1,op2,op3}) + 1;
}

// Bottom Up Approach
int minStepsToOneBU(int steps) {
    int dp[steps+1] = {0};
    
    for(int i=2;i<=steps;i++) {
        int op1, op2, op3;
        op1 = op2 = op3 = INT_MAX;

        op1 = dp[i-1];
        if(i%2==0)
            op2 = dp[i/2];
        if(i%3==0)
            op3 = dp[i/3];  
        
        dp[i] = min({op1,op2,op3}) + 1;
    }
    return dp[steps];
}

int min_coin_change_TD(int coins[], int n, int target, int *dp) {
    // Base Case
    if(target==0)
        return 0;
    if(dp[target]!=0)
        return dp[target];

    // Recursive Case
    int coinsNum = INT_MAX;
    for(int i=0;i<n;i++) {
        if(target-coins[i]>=0) {
            int temp = min_coin_change_TD(coins, n, target-coins[i], dp);
            if(temp!=INT_MAX)
                coinsNum = min(coinsNum, temp + 1);
        }
    }
    return dp[target] = coinsNum;
}

int min_coin_change_BU(int coins[], int n, int target) {
    int dp[target+1];

    for(int i=0;i<=target;i++)
        dp[i] = INT_MAX;
    for(int i=0;i<n;i++) {
        if(coins[i]<=target)
            dp[coins[i]] = 1;
    }
    dp[0] = 0;

    for(int i=0;i<=target;i++) {
        for(int j=0;j<n;j++) {
            if(i-coins[j]>=0 && dp[i-coins[j]]!=INT_MAX)
                dp[i] = min(dp[i], dp[i-coins[j]]+1);
        }
    }
    return dp[target];
}

int max_wines_profit_TD(int winePrice[], int currYr, int i, int j, int dp[][100]) {
    // Bases Cases
    if(i>j)
        return 0;
    if(dp[i][j]!=0)
        return dp[i][j];
    
    // Recurssive Cases
    int op1 = winePrice[i] * currYr + max_wines_profit_TD(winePrice, currYr+1, i+1, j, dp);
    int op2 = winePrice[j] * currYr + max_wines_profit_TD(winePrice, currYr+1, i, j-1, dp);

    return dp[i][j] = max(op1, op2);
}

int max_wines_profit_BU(int winePrice[], int n) {
    int dp[100][100] = {0};

    for(int k=0;k<n;k++) {
        int j = k, i=0;
        while(i<n && j<n) {
            int yr = n - j + i;
            if(i==j)
                dp[i][j] = winePrice[i] * yr;
            else
                dp[i][j] = max(dp[i][j-1] + winePrice[j]*yr , dp[i+1][j] + winePrice[i]*yr);
            i++;j++;
        }
    }
    return dp[0][n-1];
}

int max_subarray_sum_DP(int nums[], int len, int *dp) {
    dp[0] = nums[0]<0 ? 0: nums[0];
    int cSum = dp[0];

    for(int i=1;i<len;i++) {
        cSum += nums[i];
        if(cSum<0)
            cSum=0;
        dp[i] = max(dp[i-1], cSum);
    }
    return dp[len-1];
}

// Time O(N)
// Space O(1)
// Extension we want -ve as well if all nums -ve not 0 as min sum
// Run a loop to check all nos -ve keep in flag and return min Val if it is
int max_subarray_sum_Kadanes(int nums[], int len) {
    int cSum = 0, maxSum = 0;
    for(int i=0;i<len;i++) {
        cSum += nums[i];
        if(cSum<0)
            cSum = 0;
        maxSum = max(cSum, maxSum);
    }
    return maxSum;
}

int ladder_top_down(int target, int k, int *dp) {
    if(target==0)
        return 1;

    if(dp[target]!=0)
        return dp[target];
    
    int ways = 0;
    for(int i=1;i<=k;i++) {
        if(target-i>=0)
            ways += ladder_top_down(target-i, k, dp);
    }
    return dp[target] = ways;
}

int ladder_bottom_up(int target, int k) {
    int dp[target+1] = {0};
    dp[0] = 1;
    for(int i=1;i<=target;i++) {
        for(int step=1;step<=k;step++) {
            if(i-step>=0)
                dp[i] += dp[i-step];
        }
    }
    return dp[target];
}

// Ways 1 1 2 [4 7 13] 24
// Where k = 3
// If i need to find next which is 7+13+24 == [4+7+13]+[24]-4
//               Which is equal to dp[n+1] == dp[n] + dp[n] - dp[n-k]
// So we can say dp[n] = 2*dp[n-1] - dp[n-k-1]
// Time Complexity : O(N) only this way
int ladders_optimised(int target, int k) {
    int dp[target+1] = {0};
    dp[0] = dp[1] = 1;
    for(int i=2;i<=target;i++) {
        if(i-k-1<0)
            dp[i] = 2*dp[i-1];
        else
            dp[i] = 2*dp[i-1] - dp[i-k-1];
    }
    return dp[target];
}

int rod_cutting_topdown(int price[], int cutLength, int rodLength, int *dp) {
    if(rodLength==0)
        return 0;
    
    if(dp[rodLength]!=0)
        return dp[rodLength];

    int maxProfit = 0;
    for(int cut=1;cut<=cutLength;cut++) {
        if(rodLength - cut >=0) {
            maxProfit = max(maxProfit, price[cut-1] + rod_cutting_topdown(price, cutLength, rodLength-cut, dp));
        }
    }
    return dp[rodLength] = maxProfit;
}

int rod_cutting_bottomup(int price[], int cutLength, int rodLength) {
    int dp[rodLength+1] = {0};

    for(int len = 1; len<=rodLength ;len++) {
        for(int cut = 1; cut<cutLength; cut++) {
            if(len-cut>=0)
                dp[len] = max(dp[len], dp[len-cut] + price[cut-1]);
        }
    }
    return dp[rodLength];
}

int lcsTopDown(string str, string ptr, int i, int j, int dp[][100])
{
    if (i == 0 || j == 0)
        return 0;
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    if (str[i - 1] == ptr[j - 1])
        return dp[i][j] = 1 + lcsTopDown(str, ptr, i - 1, j - 1, dp);
 
    return dp[i][j] = max(lcsTopDown(str, ptr, i, j - 1, dp),
                          lcsTopDown(str, ptr, i - 1, j, dp));
}

int longestCommonSubSequenceLength(string str, string ptr) {
    int dp[100][100] = {0};

    int strLen = str.length();
    int ptrLen = ptr.length();

    for(int i=1;i<=str.length();i++) {
        for(int j=1;j<=ptr.length();j++) {
            if(str[i-1] == ptr[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[strLen][ptrLen];
}

// Time Complexity: O(n^2)
// Brute Force
// dp[i] -> repersent LIS starting with current i idx
int LISApproach1(int sequence[], int len) {
    int dp[len] = {0};
    // Take an element look ahead if the elements are bigger then increase len
    // Store ans in dp[] from last to front for quick ans of sub-problem
    for(int i=len-1;i>=0;i--) {
        int maxLen = 1;
        for(int j=i+1;j<len;j++) {
            if(sequence[i]<sequence[j])
                maxLen = max(1+dp[j], maxLen);
        }
        dp[i] = maxLen;
    }

    int lis = 0;
    for(int i=0;i<len;i++) 
        lis = max(lis, dp[i]);

    return lis;
}

// dp[i] -> indicates element at which LIS ends of length i
int LISApproach2(int sequence[], int n) {
    int dp[n+1] = {0};
    dp[0] = INT_MIN;

    for(int i=1;i<=n;i++)
        dp[i] = INT_MAX;  

    for(int i=0;i<n;i++) {
        for(int len=0;len<n;len++) {
            if(sequence[i]>dp[len] && sequence[i]<dp[len+1])
                dp[len+1] = sequence[i];
        }
    }

    int lis = 0;
    for(int i=1;i<=n;i++) {
        if(dp[i]!=INT_MAX)
            lis++;
        else
            break;
    }
    return lis;
}

// The above approach we can optimise as the DP is monotonic and increasing
int LISOptimised(int sequence[], int n) {
    int dp[n+1] = {0};
    dp[0] = INT_MIN;

    for(int i=1;i<=n;i++)
        dp[i] = INT_MAX;
    
    for(int i=0;i<n;i++) {
        int idx = upper_bound(dp, dp+n+1, sequence[i]) - dp;
        if(dp[idx-1] != sequence[i])
            dp[idx] = sequence[i];
    }

    int lis = 0;
    for(int i=1;i<=n;i++) {
        if(dp[i]!=INT_MAX)
            lis++;
        else
            break;
    }
    return lis;
}   

// Time Complexity: O(n^2)
// Finding number of nodes in complete binary tree
int computeCatalan(int n) {
    int dp[n+1] = {0};
    dp[0] = dp[1] = 1;

    for(int i=2;i<=n;i++) {
        for(int j=0;j<i;j++) {
            dp[i] += dp[j] * dp[i-j-1];
        }
    }
    return dp[n];
}

// Find total ways of pairing
int friendsPairing(int n) {
    long long int dp[n+1] = {0};
    dp[0] = dp[1] = 1;

    for(int i=2;i<=n;i++) {
        dp[i] = (((i-1) * dp[i-2]) % mod + dp[i-1]) % mod;
    }

    return dp[n];
}

// Time Complexity: O(n^2)
int knapsack_top_down(int prices[], int weights[], int i, int n, int capacity, int dp[][100]) {
    if(capacity==0 || i>=n)
        return 0;
    
    if(dp[i][capacity]!=0)
        return dp[i][capacity];
    
    int op1 = 0;
    int op2 = 0;

    if(capacity >= weights[i]) 
        op1 = prices[i] + knapsack_top_down(prices, weights, i+1, n, capacity-weights[i], dp); 
    op2 = knapsack_top_down(prices, weights, i+1, n, capacity, dp);

    return dp[i][capacity] = max(op1, op2);
}

// Time Complexity: O(n^2)
int knapsack_bottom_up(int prices[], int weights[], int n, int capacity) {
    int dp[1001][1001] = {0};

    for(int i=1;i<=n;i++) {
        for(int j=1;j<=capacity;j++) {
            if(weights[i-1]>j)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = max(dp[i-1][j], prices[i-1] + dp[i-1][j-weights[i-1]]);
        }
    }    
    return dp[n][capacity];
} 

// Time Complexity: O(n^2)
int minimumCostPath(int grid[][4], int r, int c) {
    for(int i=1;i<r;i++)
        grid[i][0] += grid[i-1][0];
    for(int j=1;j<c;j++)
        grid[0][j] += grid[0][j-1];

    for(int i=1;i<r;i++) {
        for(int j=1;j<c;j++) {
            grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
        }
    }

    return grid[r-1][c-1];
}

// Time Complexity: O(n^2)
// Similar Question: Falling Path Sum [Leetcode]
int maximumPathSum(int path[][4], int r, int c) {
    
    for(int i=r-2;i>=0;i--) {
        for(int j=0;j<c;j++) {
            int op1,op2,op3;
            op1 = op2 = op3 = INT_MIN;

            if(j-1>=0)
                op1 = path[i+1][j-1];
            if(j>=0 && j<c)
                op2 = path[i+1][j];
            if(j+1<c)
                op3 = path[i+1][j+1];
            path[i][j] += max({op1, op2, op3});
        }
    }
    
    int maxPathSum = INT_MIN;
    for(int j=0;j<c;j++)
        maxPathSum = max(maxPathSum, path[0][j]);
    return maxPathSum;
}

int minOperationRequired(string &str1, string &str2) {
    int dp[1001][1001] = {0};

    for(int i=0;i<=str2.size();i++)
        dp[0][i] = i;

    for(int j=0;j<=str1.size();j++)
        dp[j][0] = j;

    for(int i=1;i<=str1.size();i++){
        for(int j=1;j<=str2.size();j++){

            if(str1[i-1]==str2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else{
                int insert_steps = 1 + dp[i-1][j];
                int replace_steps = 1 + dp[i-1][j-1];
                int delete_steps =  1 + dp[i][j-1];

                dp[i][j] = min({insert_steps, replace_steps, delete_steps});
            } 
        }
    }
    return dp[str1.size()][str2.size()];
}


int main() {
    // Q1. Minimum Steps to reach one :--
    // Each step jump 1X 2X or 3X steps:--
    int dp[1000] = {0};
    int dp2[100][100] = {0};

    int steps = 10;
    cout<<"Minimum steps to reach one [TD]: "<< minStepsToOne(steps, dp) <<endl;
    cout<<"Minimum steps to reach one [BU]: "<< minStepsToOneBU(steps) <<endl;
    
    memset(dp, 0, sizeof(dp));
    // Q2. Min Coin Change Problem :--
    // Calculate min number of coins to reach target :-
    // All denominations available in infinite quantity.
    // Extension - Compute number of ways of forming a target amount.
    int coins[] = {9, 6, 5, 1};
    int n = sizeof(coins) / sizeof(coins[0]); 
    int target = 11;

    cout<<"No of Coins Needed [TD]: "<< min_coin_change_TD(coins,n,target,dp) <<endl;
    cout<<"No of Coins Needed [BU]: "<< min_coin_change_BU(coins,n,target) <<endl;
    
    memset(dp, 0, sizeof(dp));
    // Q3. Wines Bottle Problem
    // Max price one could get after certain yrs selling wines from extreme ends
    // Every yr price of extremes becomes price * yr
    int winePrice[] = {2,3,5,1,4};
    int len = sizeof(winePrice) / sizeof(winePrice[0]);

    cout<<"Max Profit Selling Wines [TD]: "<< max_wines_profit_TD(winePrice,1,0,len-1,dp2)<<endl;
    cout<<"Max Profit Selling Wines [BU]: "<< max_wines_profit_BU(winePrice,len) <<endl;

    memset(dp2 ,0 ,sizeof(dp2));
    // Q4. Find Max Sum Subarray
    // Ex - [-3, 2, 5, -1, 6, 3, -2, 7, -5, 2]
    //  Answer - 20 : [2,5,-1,6,3,-2,7] 
    int nums[] = {-3, 2, 5, -1, 6, 3, -2, 7, -5, 2};
    len = sizeof(nums) / sizeof(nums[0]);

    cout<< "Max Subarray Sum [DP]: " << max_subarray_sum_DP(nums, len, dp) << endl;
    cout<< "Max Subarray Sum [Kadanes]: " << max_subarray_sum_Kadanes(nums, len) << endl;

    memset(dp, 0, sizeof(dp));
    // Q5. Ladders Problem
    // Output ways to reach position n taking max of k steps at a time
    target = 12;
    int k = 8;

    cout<<"Ladder Total Ways O(nk): [TD]-> "<<ladder_top_down(target,k,dp)<<endl;
    cout<<"Ladder Total Ways O(nk): [BU]-> "<<ladder_bottom_up(target,k)<<endl;
    cout<<"Ladder Optimised O(n): "<<ladders_optimised(target,k)<<endl;

    memset(dp, 0, sizeof(dp));
    // Q6. Rod Cutting Problem
    // Calculate selling price of entire rod after cutting
    int rodLength = 10;
    int price[] = {2,3,2,5}; // Cutting Length: 1 2 3 4
    len = sizeof(price)/ sizeof(price[0]);

    cout<<"Max Profit Selling Rod[TD]: "<<rod_cutting_topdown(price, len, rodLength, dp)<<endl;
    cout<<"Max Profit Selling Rod[BU]: "<<rod_cutting_bottomup(price, len, rodLength)<<endl;

    memset(dp, 0, sizeof(dp));
    // Q7. Longest Common SubSequence Length
    string str = "aggtab", ptr="gxtayb";
    memset(dp2, -1, sizeof(dp2));

    cout<<"Length of longest Common SubSequence [TD]: "<< lcsTopDown(str, ptr, str.length(), ptr.length(), dp2)<<endl;
    cout<<"Length of longest Common SubSequence [BU]: "<< longestCommonSubSequenceLength(str, ptr)<<endl;
    
    memset(dp2, 0, sizeof(dp2));
    // Q8. Longest Increasing SubSequence Length
    // Given Sequence is = [1 5 2 3 4 9 6 10]
    // Length is -> 6 -- {1 2 3 4 9 10}
    int sequence[] = {1,5,2,3,4,9,6,10};
    len = sizeof(sequence) / sizeof(sequence[0]); 

    cout<<"Longest Increasing Subsequence: O(n^2) " << LISApproach1(sequence, len) << endl;
    cout<<"Longest Increasing Subsequence [Tricky]: O(n^2) " << LISApproach2(sequence, len) << endl;
    cout<<"Longest Increasing Subsequence: O(nlogn) " << LISOptimised(sequence, len) << endl;
    // There's one more approach of segment tree I can skip for interviews

    memset(dp, 0, sizeof(dp));
    // Q9. Catalan Number
    // Finding nth Catalan number
    n = 10;
    cout<<"Nth Catalan number: " << computeCatalan(n) << endl;

    // Q10. Friends Pairing
    // N friends come to party in solo or pairs
    // Find number of ways possible
    n = 4;
    cout<<"Total number of Ways of pairing: " << friendsPairing(n) << endl;

    // Q11. 0-1 Knapsack
    // Robber robbs a shop we have weights and prices of those wt given
    // Robber has a bag of some capacity and can take limited items 
    // Help him maximise his profit
    int capacity = 50;
    n = 3;
    int prices[] = {60,100,120};
    int weights[] = {10,20,30};

    cout<< "Max Profit Robber can make [TD]: " << knapsack_top_down(prices, weights, 0, n, capacity, dp2) << endl;
    cout<< "Max Profit Robber can make [BU]: " << knapsack_bottom_up(prices, weights, n, capacity) << endl;

    memset(dp2, 0, sizeof(dp2));
    // Q12. Find Min Cost Path [Grid Based DP]
    // We can move either right or down only
    // Down: (row+1, col)
    // Right: (row, col+1)
    int grid[4][4] = {
        {1,2,10,4},
        {100,3,2,1},
        {1,1,20,2},
        {1,2,2,1}
    };
    int r = 4, c = 4;
    cout<< "Min Cost Path is [Down, Right]: " << minimumCostPath(grid, r, c) << endl;

    // Q13. Find Max Path Sum [Grid Based DP]
    // We can move in down, down diagonally left, down diagonally right
    // Down: (row+1,col)
    // Down left diagonal: (row+1,col-1)
    // Down right diagonal: (row+1, col+1)
    int path[4][4] = {
        {1,2,10,4},
        {100,3,2,1},
        {1,1,20,2},
        {1,2,2,1}
    };
    r = 4, c = 4;

    cout<< "Max Path Sum is [Down, D Left, D Right]: " << maximumPathSum(path, r, c) << endl;

    // Q14. Total Ways to reach m,n position in a matrix
    // DP Approach :-
    // ways[i][0] = 1 && ways[0][j] = 1 
    // ways[i][j] = ways[i-1][j] + ways[i][j-1]
    // Return ways[r-1][c-1]
    
    // Maths Approach :-
    // Total(n) = (r-1) + (c-1)
    // Ways = nC(r-1)
    // = (r-1+c-1)! / (r-1)! * (c-1)!

    // [*TODO] Code: [Not understood Properly]
    // int path = 1;
    // for (int i = n; i < (r + c - 1); i++) {
    //     path *= i;
    //     path /= (i - n + 1);
    // }
    // return path;

    // Q15. Given 2 strings [V.V.I]
    // Find Minimum number of operations required to convert word1 to word2.
    // Insert a character
    // Delete a character  
    // Replace a character
    // These can be done at any positions not necessarily ends
    string word1 = "horse", word2 = "ros";
    cout<< "Minimum Operation Required for conversion: " << minOperationRequired(word1, word2) <<endl;

    // TODO :--
    // Egg Dropping
    // Max Sum Increasing SubSequence Length
    // Word Break
    // Job Scheduling
    // Palindrome Partitioning
    // Frog Jump
    // House Robber [1,2,3,4]
    // Count Partition with given diffrence
    // Unbounded Knapsack
    // Buy and Sell Stocks [1,2,3,4]
    // Print LIS
    // Longest Biotonic SubSeq
    // Max Rect area with all 1
    // Burst Balloon 
    // Min cost to cut Stick

    return 0;
}