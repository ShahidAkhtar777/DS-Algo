#include <bits/stdc++.h>
using namespace std;

// Finding array is sorted using recurssion
// Time: O(N)
// Space: O(N)

bool isSorted(int a[], int n)
{
    if (n == 0 || n == 1)
        return true;

    if (a[0] <= a[1] && isSorted(a + 1, n - 1))
    {
        return true;
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;
    int arr[n];

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    bool res = isSorted(arr, n);

    if (res)
        cout << "Sorted Array";
    else
        cout << "Not sorted array";

    return 0;
}