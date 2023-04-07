#include <bits/stdc++.h>
using namespace std;

// Binary Search using recurssion in a sorted array
// Time Complexity: O(logN)
// Space Complexity: O(logN)

int binary_search(int a[], int st, int e, int n, int num)
{
    int mid = (st + e) / 2;

    if (st == n || e == -1)
        return -1;
    else if (a[mid] == num)
        return mid;
    else if (a[mid] > num)
        return binary_search(a, st, mid - 1, n, num);
    else
        return binary_search(a, mid + 1, e, n, num);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, num;
    cin >> n;
    int arr[n];

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cin >> num;
    int index = binary_search(arr, 0, n - 1, n, num);

    if (index == -1)
        cout << "Number not found";
    else
        cout << "Element found at index: " << index;

    return 0;
}