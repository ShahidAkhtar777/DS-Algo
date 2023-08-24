#include <bits/stdc++.h>
using namespace std;

// Hashing
bool checksum(vector<int> nums)
{
    int pre = 0;
    unordered_map<int, bool> m;
    for (auto n : nums)
    {
        pre += n;
        if (pre == 0 || m[pre])
        {
            return true;
        }
        m[pre] = true;
    }
    return false;
}

int computeZeroLength(vector<int> nums)
{
    int sum = 0;
    int maxLen = 0;
    unordered_map<int, int> m;

    for (int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
        if (sum == 0)
            maxLen = max(maxLen, i + 1);
        else if (m.find(sum) != m.end())
            maxLen = max(maxLen, i - m[sum]);
        m[sum] = i;
    }
    return maxLen;
}

int computeKSumLength(vector<int> nums, int k)
{
    int pre = 0;
    int maxLen = 0;
    unordered_map<int, int> m;

    for (int i = 0; i < nums.size(); i++)
    {
        pre += nums[i];
        if (pre == k)
            maxLen = i + 1;
        else if (m.find(pre - k) != m.end())
            maxLen = max(maxLen, i - m[pre - k]);
        if (m.find(pre) == m.end())
            m[pre] = i;
    }
    return maxLen;
}

// Time - O(NlogN)
int longestConsecutiveSubSequence(vector<int> nums)
{
    map<int, bool> m; // Its sorting them internally so not much optimised solution
    for (auto n : nums)
        m[n] = true;
    int maxLen = 0;

    for (auto n : m)
    {
        if (m.find(n.first - 1) != m.end())
            continue;
        else
        {
            int count = 0;
            int num = n.first;
            while (m.count(num))
            {
                count++;
                num++;
            }
            maxLen = max(count, maxLen);
        }
    }
    return maxLen;
}

// Time - O(n) Optimised code
int longestConsecutiveSubSequenceOptimised(vector<int> &nums) {
    unordered_map<int, bool> numsMap;

        for(int i=0;i<nums.size();i++)
            numsMap[nums[i]] = true;

        int longestSeqLength = 0;
        for(auto e: numsMap) {
            if(!numsMap.count(e.first-1)) {
                int val = e.first;
                int length = 0;
                while(numsMap.count(val)) {
                    length++;
                    val++;
                }
                longestSeqLength = max(length, longestSeqLength);
            }
        }
        return longestSeqLength;
}

// bool IsStrContainPtr(int strHash[26], int ptrHash[26]) {
//     for(int i=0;i<26;i++){
//         if(ptrHash[i]>strHash[i])
//             return false;
//     }
//     return true;
// }

// Time: O(n+m)
// Time: O(n*m) -> If we dont keep count of map size and rather traverse a map
// Very Good and Important Question
void computeMinimumWindow()
{
    string str, ptr;
    str = "zoomlazapzo";
    ptr = "oza";

    int strLen = str.length();
    int ptrLen = ptr.length();

    unordered_map<char, int> strHash;
    unordered_map<char, int> ptrHash;

    for (int i = 0; i < ptrLen; i++)
        ptrHash[ptr[i]]++;
    int ptrMapSize = ptrHash.size();
    int count = ptrMapSize;

    int minLen = INT_MAX;
    int stIdx = 0;
    int resIdx = 0;

    for (int i = 0; i < str.length(); i++)
    {
        strHash[str[i]]++;

        if (ptrHash.count(str[i]))
        {
            ptrHash[str[i]]--;
            if (ptrHash[str[i]] == 0)
                count--;
        }

        while (count == 0)
        {
            if (i - stIdx + 1 < minLen)
            {
                resIdx = stIdx;
                minLen = i - stIdx + 1;
            }
            strHash[str[stIdx]]--;
            if (ptrHash.count(str[stIdx]))
            {
                if (ptrHash[str[stIdx]] == 0)
                    count++;
                ptrHash[str[stIdx]]++;
            }
            stIdx++;
        }
    }

    if (minLen == INT_MAX)
    {
        cout << "No possible Substring" << endl;
        return;
    }

    string res = str.substr(resIdx, minLen);
    cout << "Minimum Window String: " << res << endl;
}

bool isPalindrome(const string &word)
{
    int left = 0, right = word.length() - 1;
    while (left < right)
    {
        if (word[left++] != word[right--])
        {
            return false;
        }
    }
    return true;
}

// Time -> O(n*k^2) 
// n -> number of words
// k -> length of words
void computeUniquePalindromes()
{
    vector<string> words = {"abcd", "dcba", "lls", "s", "sssll"};

    unordered_map<string, int> map;
    vector<vector<int>> res;

    for (int i = 0; i < words.size(); i++)
        map[words[i]] = i;

    for (int i = 0; i < words.size(); i++)
    {
        for (int j = 0; j <= words[i].size(); j++)
        {
            string prefix = words[i].substr(0, j);
            string suffix = words[i].substr(j);

            if (j != 0 && isPalindrome(prefix))
            {
                string reverseSuffix = suffix;
                reverse(reverseSuffix.begin(), reverseSuffix.end());
                if (map.count(reverseSuffix) && map[reverseSuffix] != i)
                    res.push_back({map[reverseSuffix], i});
            }

            if (isPalindrome(suffix))
            {
                string reversePrefix = prefix;
                reverse(reversePrefix.begin(), reversePrefix.end());
                if (map.count(reversePrefix) && map[reversePrefix] != i)
                    res.push_back({i, map[reversePrefix]});
            }
        }
    }
    cout << "All Words: ";
    for (auto word : words)
        cout << "'" << word << "' ";
    cout << endl
         << "Pairs: ";
    for (auto pair : res)
    {
        cout << "[" << pair[0] << "," << pair[1] << "] ";
    }
}

int main()
{
    // Vertical Order traversal: Tree

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    // Q1 -> Check subarray with sum 0.
    cout << "Zero Sum Present: " << checksum(nums) << endl;
    // Q2 -> Longest Subarray with 0 sum
    cout << "Longest Length of Subarray with sum 0: " << computeZeroLength(nums) << endl;
    // Q3 -> Longest subarray with sum k
    int k;
    cin >> k;
    cout << "Longest length with sum k: " << computeKSumLength(nums, k) << endl;

    // Q4 -> Length Longest Consecutive SubSequence
    // [10,4,20,1,3,3,2,19]
    // RES :: 4 1 2 3 :: Length 4
    cout << "Longest Consecutive Subsequence: " << longestConsecutiveSubSequence(nums) << endl;
    cout << "Optimised Longest SubSeq: " << longestConsecutiveSubSequenceOptimised(nums) << endl;

    // Q5 -> Minimum Length Window Substring
    // All chars of pattern should be present in string
    // String -> adobecodebanc
    // Pattern -> abc
    computeMinimumWindow();

    // Q6 -> Unique Words Pair
    // Words = ["abcd", "dcba", "lls", "s", "sssll"]
    // Output = [[0,1] [1,0] [3,2] [2,4]]
    computeUniquePalindromes();
    return 0;
}

// Input
// 10
// 2 -5 0 5 6 7 8 4 3 10
// 2
