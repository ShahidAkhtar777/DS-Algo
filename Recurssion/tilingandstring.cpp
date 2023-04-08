#include <bits/stdc++.h>
using namespace std;

// String To Integer using Recurssion

int string_to_int(string s, int n)
{

    if (n == 0)
        return 0;

    int last_digit = s[n - 1] - '0';
    int res = string_to_int(s, n - 1);

    return res * 10 + last_digit;
}

// Tiling Problem: tell all possible ways of building wall bricks: 1*4 4*1

int tiling(int n)
{

    if (n <= 3)
        return 1;

    return tiling(n - 1) + tiling(n - 4);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    string s;
    cin >> s;

    int res = string_to_int(s, s.length());
    cout << res << endl;

    int n;
    cin >> n;

    cout << "Total Ways: " << tiling(n);

    return 0;
}