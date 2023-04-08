#include <bits/stdc++.h>
using namespace std;

// Merge Sort Using Recurssion

void merge(int *a, int st, int e)
{
    int mid = (st + e) / 2;
    int temp[100];
    int j = mid + 1;
    int k = st, i = st;

    while (i <= mid && j <= e)
    {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= e)
        temp[k++] = a[j++];

    for (int i = st; i <= e; i++)
        a[i] = temp[i];
}

void merge_sort(int a[], int st, int e)
{

    if (st >= e)
        return;

    int mid = (st + e) / 2;
    merge_sort(a, st, mid);
    merge_sort(a, mid + 1, e);

    merge(a, st, e);
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

    merge_sort(arr, 0, n - 1);

    for (auto x : arr)
        cout << x << " ";

    return 0;
}