// 3. Longest Substring Without Repeating Characters - Medium

// Given a string s, find the length of the longest 
// substring without repeating characters.

// Example 1:

// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.
// Example 2:

// Input: s = "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.
// Example 3:

// Input: s = "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3.
// Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

// Constraints:

// 0 <= s.length <= 5 * 104
// s consists of English letters, digits, symbols and spaces.

#include<bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s) {
        int max_len = 0;
        int start = 0;
        int len = s.length();
        unordered_map<char, int> m;

        for(int i=0;i<len;i++){
            if(m.find(s[i])==m.end() || start>m[s[i]])
                max_len = max(max_len, i-start+1);
            else
                start = m[s[i]] + 1;
            m[s[i]] = i;
        }   
        return max_len;
    }