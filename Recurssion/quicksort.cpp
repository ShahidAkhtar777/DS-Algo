class Solution
{
public:
    // Function to sort an array using quick sort algorithm.
    void quickSort(int arr[], int low, int high)
    {
        if (low >= high)
            return;

        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }

public:
    int partition(int arr[], int low, int high)
    {
        int pivot = arr[high];
        int i = low - 1;
        int j = low;

        while (j < high)
        {
            if (arr[j] <= pivot)
            {
                i = i + 1;
                swap(arr[i], arr[j]);
            }
            j++;
        }

        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};