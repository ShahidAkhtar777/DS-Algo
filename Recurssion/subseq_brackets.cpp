#include <bits/stdc++.h>
using namespace std;

// Subsequences using recurssion

void all_subsequences(string in, char *out, int i, int j)
{

    // Base Condition
    if (i == in.length())
    {
        out[j] = '\0';
        cout << out << endl;
        return;
    }

    out[j] = in[i];
    all_subsequences(in, out, i + 1, j + 1);
    all_subsequences(in, out, i + 1, j);
}

// Generate Brackets

int generate_brackets(int n, char *out, int open, int close, int idx)
{
    if (idx == n)
    {
        out[idx] = '\0';
        cout << out << endl;
        return 1;
    }

    int ans = 0;

    if (open < n / 2)
    {
        out[idx] = '(';
        ans += generate_brackets(n, out, open + 1, close, idx + 1);
    }
    if (close < open)
    {
        out[idx] = ')';
        ans += generate_brackets(n, out, open, close + 1, idx + 1);
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    string s;
    cin >> s;

    char out[30];

    all_subsequences(s, out, 0, 0);

    int n;
    cin >> n;
    if (n & 1)
        cout << "Balanced Parenthesis not possible";
    else
    {
        int ways = generate_brackets(n, out, 0, 0, 0);
        cout << "Total Ways: " << ways << endl;
    }

    return 0;
}