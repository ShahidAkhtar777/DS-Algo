
long long int bobsHomework(int n)
{
    vector<int> nums;

    while (n != 0)
    {
        nums.push_back(n % 10);
        n = n / 10;
    }

    reverse(nums.begin(), nums.end());

    int i = nums.size() - 2;

    while (i >= 0)
    {
        if (nums[i] < nums[i + 1])
            break;
        i--;
    }

    if (i < 0)
        return -1;

    int t_idx = i, j = nums.size() - 1;

    while (j > i)
    {
        if (nums[j] > nums[i])
            break;
        j--;
    }

    swap(nums[i], nums[j]);
    reverse(nums.begin() + i + 1, nums.end());

    long long int res = 0;

    for (auto x : nums)
    {
        res = res * 10 + x;
    }
    return res;
}