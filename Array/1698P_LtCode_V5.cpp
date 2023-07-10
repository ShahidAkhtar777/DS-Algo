/*
Problem Statement:

You are given a string S of length N. You have to find the count of all distinct substrings of this string.

Input Format:

- The first line contains an integer T, denoting the number of test cases.
- Each test case contains a string S of length N.

Output Format:

For each test case, print the count of all distinct substrings of the given string.

Constraints:

- 1 <= T <= 10^2
- 1 <= N <= 10^5

Example Input:

2
ababa
aaaaa

Example Output:

10
5
*/

// Trie DS Implementation
// Time: O(N^2)
// Space: O(length(str))

#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    char data;
    Node* child[26];

    Node(char d){
        data = d;
    }
};

class Trie {
public:
    Node* root;

    Trie(){
        root = new Node('\0');  
    }

    int insert(string s){
        Node *curr = root;
        int distinctStr = 0;
        int len = s.length();

        for(int i=0;i<len;i++){
            curr = root;
            for(int j=i; j<len; j++)
            {
                char ch = s[j];
                if(curr->child[ch-'a']!=NULL){
                    curr = curr->child[ch-'a'];   
                }else{
                    Node *n = new Node(ch);
                    curr->child[ch-'a'] = n;
                    curr = n;
                    distinctStr++;
                }
            }   
        }
        return distinctStr+1;
    }
};

int countDistinctSubstrings(string &s)
{
    Trie *t = new Trie();
    return t->insert(s);
}