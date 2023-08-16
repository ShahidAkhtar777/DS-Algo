/*
## Maximum Number of Events That Can Be Attended II

**Description:**

Given an array of events, each represented by `[startDay, endDay, value]`, where `startDay` and `endDay` denote the event's duration, and `value` represents the benefit of attending that event. Additionally, an integer `k` is provided, indicating the maximum number of events that can be attended.

However, only **one event can be attended at a time**, and the **entire event must be attended**. It is important to note that events with the same start and end day **cannot be attended simultaneously**. The task is to determine the maximum sum of values that can be obtained by attending events within the given constraints.

**Example 1:**

Input: `events = [[1,2,4],[3,4,3],[2,3,1]], k = 2`

Output: `7`

Explanation: Choosing events 0 and 1 (0-indexed) will yield a total value of `4 + 3 = 7`.

**Example 2:**

Input: `events = [[1,2,4],[3,4,3],[2,3,10]], k = 2`

Output: `10`

Explanation: Selecting event 2 will result in a total value of `10`. Note that attending additional events is not required due to overlapping.

**Example 3:**

Input: `events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3`

Output: `9`

Explanation: While these events do not overlap, only three events can be attended. Thus, the three events with the highest values are chosen.

**Constraints:**
- `1 <= k <= events.length`
- `1 <= k * events.length <= 10^6`
- `1 <= startDay <= endDay <= 10^9`
- `1 <= value <= 10^6`

Please note that the given solution has a complexity of **O(k * n^2)**, where `n` represents the number of events.
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int get_idx(vector<vector<int>> &events, int idx){
        int lo = idx+1;
        int hi = events.size()-1;
        int ans = -1;

        while(lo<=hi){
            int mid = (lo+hi)/2;
            if(events[mid][0]>events[idx][1]){
                ans = mid;
                hi = mid-1;
            }else{
                lo = mid+1;
            }
        }
        return ans;
    }

    int solve(vector<vector<int>> &events, int k, int idx, vector<vector<int>> &dp){
        
        if(idx>=events.size() || k==0 || idx==-1) 
            return 0;
        if(dp[idx][k]!=-1)
            return dp[idx][k];

        int next_idx = get_idx(events, idx);

        int op1 = events[idx][2] + solve(events, k-1, next_idx, dp);
        int op2 = solve(events, k, idx+1, dp);
        return dp[idx][k] = max(op1, op2);
    }

    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        vector<vector<int>> dp(n+5, vector<int>(k+1, -1));
        sort(events.begin(), events.end());

        return solve(events, k, 0, dp);
    }
};