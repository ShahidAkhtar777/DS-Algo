/*
## DP + Bit Manipulation Question - Hard ##

## Smallest Sufficient Team

**Description:**

In a project, you have a list of required skills `req_skills` and a list of people. Each person `people[i]` contains a list of skills that the person has.

Consider a sufficient team: a set of people such that for every required skill in `req_skills`, there is at least one person in the team who has that skill. These teams can be represented by the index of each person.

For example, a team `[0, 1, 3]` represents the people with skills `people[0]`, `people[1]`, and `people[3]`.

The task is to return any sufficient team of the smallest possible size, represented by the index of each person. The order of the answer does not matter.

It is guaranteed that an answer exists.

**Example 1:**

Input: `req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]`

Output: `[0,2]`

**Example 2:**

Input: `req_skills = ["algorithms","math","java","reactjs","csharp","aws"], people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]`

Output: `[1,2]`

**Constraints:**
- `1 <= req_skills.length <= 16`
- `1 <= req_skills[i].length <= 16`
- `req_skills[i]` consists of lowercase English letters.
- All strings in `req_skills` are unique.
- `1 <= people.length <= 60`
- `0 <= people[i].length <= 16`
- `1 <= people[i][j].length <= 16`
- `people[i][j]` consists of lowercase English letters.
- All strings in `people[i]` are unique.
- Every skill in `people[i]` is a skill in `req_skills`.
- It is guaranteed that a sufficient team exists.

Please note that the solution for this problem is not included here.
*/

// Using only Bit Manipulation:
// Gives memory limit exceeded error

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Bit Manipulation
    vector<int> sol;

    void solve(vector<int> res, int people_skills[], int p, int n, int idx, int mask){
        if(idx==p){
            if(mask==((1<<n) - 1)){
                if(sol.size()==0 || sol.size()>res.size()){
                    sol = res;
                }
            }
            return;
        }

        solve(res, people_skills, p, n, idx+1, mask);
        res.push_back(idx);
        solve(res, people_skills, p, n, idx+1, mask | people_skills[idx]);
        res.pop_back();
    }

    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        unordered_map<string, int> skills;
        int n = req_skills.size();
        for(int i=0;i<n;i++){
            skills[req_skills[i]] = i;
        }


        int tot_people = people.size();
        int people_skills[tot_people];
        for(int i=0;i<tot_people;i++){
            int p_skills = people[i].size();
            people_skills[i] = 0;

            for(int j=0;j<p_skills;j++){
                int skill_idx = skills[people[i][j]];
                people_skills[i] = people_skills[i] | (1<<skill_idx);
            }
        }

        vector<int> res;
        solve(res, people_skills, tot_people,  n, 0, 0);
        return sol;
    }
};
