#include <bits/stdc++.h>
using namespace std;

// Function to find all occurrences of a pattern in a given string
vector<int> stringMatch(string& str, string& pat) {
    int mod = INT_MAX;  // Modulo value for hashing

    int str_len = str.length();  
    int pat_len = pat.length();  
    int pat_hash = 0, str_hash = 0;  // Hash values for the pattern and string
    int hash = 256;  // Hash base value (chosen as 256)
    vector<int> res;  

    if (str_len < pat_len)
        return res;  // If the pattern is longer than the string, return empty result

    int pow = 1;  // Power value for rolling hash calculation
    for (int i = 0; i < pat_len - 1; i++) {
        pow = (pow * hash) % mod;  // Calculate pow as hash^k-1 % mod
    }

    // Calculate hash values for the pattern and initial substring of the string
    for (int i = 0; i < pat_len; i++) {
        pat_hash = (pat_hash * hash + pat[i]) % mod;
        str_hash = (str_hash * hash + str[i]) % mod;
    }

    // Perform pattern matching using rolling hash technique
    for (int i = 0; i <= str_len - pat_len; i++) {
        if (pat_hash == str_hash) {  // If the hashes match, compare characters
            int j;
            for (j = 0; j < pat_len; j++) {
                if (str[i + j] != pat[j])
                    break;
            }
            if (j == pat_len)
                res.push_back(i);  // If characters match till the end of the pattern, add the index to the result
        }

        if (i < str_len - pat_len) {
            // Update the rolling hash value for the next substring
            str_hash = (hash * (str_hash - str[i] * pow) + str[i + pat_len]) % mod;
            if (str_hash < 0)
                str_hash += mod;  // Ensure the hash value is non-negative
        }
    }

    return res;  // Return the vector containing the indices of pattern matches
}

int main() {
    // Example usage
    string str = "this is a string containing a pattern";
    string pat = "ing";
    vector<int> matches = stringMatch(str, pat);

    // Print the indices of pattern matches
    cout << "Pattern matches found at indices: ";
    for (int i = 0; i < matches.size(); i++) {
        cout << matches[i] << " ";
    }
    cout << endl;

    return 0;
}


// Link: https://www.codingninjas.com/codestudio/problems/1115738?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0