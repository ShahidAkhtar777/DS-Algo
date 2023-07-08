// Trie Implementation:
// Questions: Delete in Trie
// Count number of same words in Trie
// Longest Common Prefix
// Max Xor of Two Numbers in an Array
// Max Range Xor in array

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    char data;
    unordered_map<char, Node*> child;
    bool isTerminal;

    Node(char d){
        data = d;
        isTerminal = false;
    }
};

class Trie {
public:
    Node* root;

    Trie(){
        root = new Node('\0');
    }

    void insert(string word){
        int len = word.length();
        Node *curr = root;

        for(int i=0;i<len;i++){
            char ch = word[i];
            if(curr->child.count(ch))
                curr = curr->child[ch];
            else{
                Node *n = new Node(ch);
                curr->child[ch] = n;
                curr = n;   
            }
        }
        curr->isTerminal = true;
    }
};

string longestCommonPrefix(vector<string> words, int len){
    Trie *t = new Trie();
    string res;

    for(int i=0;i<len;i++){
        t->insert(words[i]);
    }

    Node *curr = t->root;
    while (curr->child.size() == 1 && !curr->isTerminal) {
        auto it = curr->child.begin();
        char ch = it->first;
        res += ch;
        curr = it->second;
    }

    return res;
}

int main() {
    vector<string> words;
    int n;

    cin>>n;
    for(int i=0;i<n;i++){
        string str;
        cin>>str;
        words.push_back(str);
    }

    string ans = longestCommonPrefix(words, n);
    cout<<ans;
    return 0; 
}
