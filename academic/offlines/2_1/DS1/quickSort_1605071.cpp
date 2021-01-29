#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

int find_median(int arr[], int n, int k)
{
    int left[n], right[n], same[n];
    int l = 0, r = 0, s = 0, idx = rand() % n;

    if(n == 1)
        return arr[0];

    for(int i = 0; i < n; i++)
    {
        if(arr[i] < arr[idx])
            left[l++] = arr[i];
        else if(arr[i] == arr[idx])
            same[s++] = arr[i];
        else right[r++] = arr[i];
    }

    if (k <= l)
        return find_median(left, l, k);
    if (l < k && k <= l + s)
        return same[s - 1];

    return find_median(right, r, k - l - s);
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int get_pos(int arr[], int n, int x)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
}

/*void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}*/

int partition(int arr[], int n)
{
    int pivot = find_median(arr, n, ((n-1) / 2)+1);
    int pos = get_pos(arr, n, pivot);
    //int pos = ((n-1)/2)+1;
    swap(arr[pos], arr[n - 1]);

    int i = 0;
    for (int j = 0; j < n - 1; j++)
    {
        if (arr[j] < pivot)
            swap(arr[i++], arr[j]);
    }

    swap(arr[i], arr[n - 1]);
    return i;
}

void quick_sort(int arr[], int n)
{
    if (n > 0)
    {
        int par = partition(arr, n);
        quick_sort(arr, par);
        quick_sort(arr + par + 1, n - par - 1);
    }
}

int main()
{

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    while(1)
    {
        srand(time(0));

        int n;
        cin >> n;
        int arr[n];

        for (int i = 0; i < n; i++)
            cin >> arr[i];

        //quick_sort(arr, n);

        cout << find_median(arr, n, ((n-1) / 2)+1) << endl;

        quick_sort(arr, n);
        for(int i = 0; i < n; i++) cout << arr[i] << " ";

        printf("\n\n");
    }
}
