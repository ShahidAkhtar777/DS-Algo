#include <bits/stdc++.h>
using namespace std;

int first_occurance(int a[], int n, int num)
{

    if (n == 0)
        return -1;

    if (a[0] == num)
        return 0;

    int idx = first_occurance(a + 1, n - 1, num);
    if (idx == -1)
        return -1;

    return idx + 1;
}

int first_occurance2(int a[], int i, int n, int num)
{

    if (i == n)
        return -1;

    if (a[i] == num)
        return i;

    return first_occurance2(a, i + 1, n, num);
}

int last_occurance(int a[], int n, int num)
{
    if (n == 0)
        return -1;

    int idx = last_occurance(a + 1, n - 1, num);

    if (idx == -1)
    {
        if (a[0] == num)
            return 0;
        else
            return -1;
    }

    return idx + 1;
}

void allOccurance(int a[], int i, int n, int num)
{

    if (i == n)
        return;

    if (a[i] == num)
    {
        cout << "Number found at index: " << i << endl;
    }

    allOccurance(a, i + 1, n, num);
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

    int num;
    cin >> num;

    int res = first_occurance2(arr, 0, n, num);
    if (res == -1)
        cout << "Not Found";
    else
        cout << "Found First at Idx: " << res << endl;

    int res2 = last_occurance(arr, n, num);

    if (res2 == -1)
        cout << "Not Found" << endl;
    else
        cout << "Last At Index: " << res2 << endl;

    allOccurance(arr, 0, n, num);

    return 0;
}