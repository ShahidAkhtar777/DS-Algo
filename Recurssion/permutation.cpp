// https://leetcode.com/problems/permutations/description/
// Find All permutations
class Solution
{
public:
    void traverse(vector<vector<int>> &res, vector<int> nums, int idx)
    {
        // Base Case
        if (idx == nums.size())
        {
            res.push_back(nums);
            return;
        }

        // Reccursive Case
        for (int i = idx; i < nums.size(); i++)
        {
            swap(nums[i], nums[idx]);
            traverse(res, nums, idx + 1);
            swap(nums[i], nums[idx]);
        }
    }

    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        traverse(res, nums, 0);
        return res;
    }
};

// https://leetcode.com/problems/permutation-sequence/description/
// Find Kth Permutation
class Solution
{
public:
    string getPermutation(int n, int k)
    {

        vector<int> nums;
        int fact = 1;
        string ans = "";

        for (int i = 1; i < n; i++)
        {
            nums.push_back(i);
            fact = fact * i;
        }
        nums.push_back(n);
        k--;

        while (true)
        {
            ans = ans + to_string(nums[k / fact]);
            nums.erase(nums.begin() + k / fact);
            if (nums.size() == 0)
                break;
            k = k % fact;
            fact = fact / nums.size();
        }

        return ans;
    }
};