#include <bits/stdc++.h>
using namespace std;

// Fast Power Using Recurssion

int find_power(int a, int b)
{

    if (b == 1)
        return a;

    if (b & 1)
    {
        return a * find_power(a, b / 2) * find_power(a, b / 2);
    }
    else
        return find_power(a, b / 2) * find_power(a, b / 2);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int a, b;
    cin >> a >> b;

    int res = find_power(a, b);

    cout << "A to the power B gives: " << res << endl;

    return 0;
}