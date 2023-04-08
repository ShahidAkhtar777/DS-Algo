#include <bits/stdc++.h>
using namespace std;

// Ladder: Jump 1 2 3 ... k step at a time
// steps: n

int ladder_ways(int n, int k)
{

    if (n == 0 || n == 1)
        return 1;
    else if (n == 2)
        return 2;
    else if (n < 0)
        return 0;

    int ans = 0;
    for (int i = 0; i < k; i++)
        ans += ladder_ways(n - i, i);

    return ans;
}

// Friends Pairing Problem
// person can go to party as single or couple
// n-> number of person

int pairing(int n)
{

    if (n == 0 || n == 1)
        return 1;

    return pairing(n - 1) + (n - 1) * pairing(n - 2);
}

// Count binary string with no consecutive ones
// n -> length of string

int count_binary(int n)
{

    if (n < 0)
        return 0;
    else if (n == 0)
        return 1;
    else if (n == 1)
        return 2;

    return count_binary(n - 1) + count_binary(n - 2);
}

// Tower of Hanoi: Move rings from one pillar to another using 3rd.
// Condition we can put the smaller ring only on top of a ring.
// n -> number of rings

int tower_of_hanoi(int n, char src, char helper, char dest)
{
    if (n == 0)
        return 0;
    int step = 0;
    step += tower_of_hanoi(n - 1, src, dest, helper);
    step++;
    cout << "Move ring: " << n << " from " << src << " to " << dest << endl;
    step += tower_of_hanoi(n - 1, helper, src, dest);

    return step;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, k;
    cin >> n, k;

    cout << "Total Ladder Ways: " << ladder_ways(n, k) << endl;

    cout << "No of Pairings: " << pairing(n) << endl;

    cout << "No of binary strings: " << count_binary(n) << endl;

    int res = tower_of_hanoi(n, 'A', 'B', 'C');
    cout << "Hanoi total steps: " << res << endl;

    return 0;
}