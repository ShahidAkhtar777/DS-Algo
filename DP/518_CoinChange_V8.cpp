#include <bits/stdc++.h>
using namespace std;

int change(int amount, vector<int> &coins)
{
    int dp[amount + 1];
    dp[0] = 1;

    for (int i = 1; i <= amount; i++)
        dp[i] = 0;

    for (int i = 0; i < coins.size(); i++)
    {
        for (int goal = coins[i]; goal <= amount; goal++)
        {
            if (goal - coins[i] >= 0)
                dp[goal] += dp[goal - coins[i]];
        }
    }
    return dp[amount];
}