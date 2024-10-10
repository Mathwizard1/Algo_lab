#include <bits/stdc++.h>
using namespace std;

void display_vector(vector<int> num_arr)
{
    for(auto num: num_arr)
    {
        cout << num << ' ';
    }
    cout << '\n';
}

/*** Sorting algo ***/
void insertSort(vector<int> &num_arr)
{
    int arr_size = num_arr.size();
    for(int i = 1; i < arr_size; i++)
    {
        int key = num_arr[i];
        int j = i - 1;

        while (j >= 0 && key < num_arr[j])
        {
            num_arr[j + 1] = num_arr[j];
            j--;
        }
        num_arr[j + 1] = key;
    }
}

vector<int> merge_arr(vector<int> arr_l, vector<int> arr_r)
{
    int l_size = arr_l.size();
    int r_size = arr_r.size();

    int i,j;
    i = j = 0;    
    vector<int> new_arr;

    while (i < l_size && j < r_size)
    {
        if(arr_l[i] < arr_r[j])
        {
            new_arr.push_back(arr_l[i]);
            i++;
        }
        else
        {
            new_arr.push_back(arr_r[j]);
            j++;
        }
    }
    
    if(i == l_size)
    {
        while (j < r_size)
        {
            new_arr.push_back(arr_r[j]);
            j++;
        }
    }
    else
    {
        while (i < l_size)
        {
            new_arr.push_back(arr_l[i]);
            i++;
        }
    }

    return new_arr;
}

vector<int> mergeSort(vector<int> num_arr, int b, int e)
{
    if(b == e)
    {
        vector<int> singleton = {num_arr[b]};
        return singleton;
    }
    
    int mid = (b + e) / 2;
    vector<int> arr_l = mergeSort(num_arr, b, mid);
    vector<int> arr_r = mergeSort(num_arr, mid + 1, e);
    
    return merge_arr(arr_l, arr_r);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partion(vector<int> &num_arr, int b, int e)
{
    int left, right, pivot;

    pivot = num_arr[b];
    left = b + 1;
    right = e;

    while (left <= right)
    {
        while(num_arr[left] < pivot)
        {
            left++;
        }

        while (num_arr[right] > pivot)
        {
            right--;
        }
        
        if(left < right)
        {
            swap(num_arr[left], num_arr[right]);
        }
    }
    
    swap(num_arr[b], num_arr[right]);
    return right;
}

void quickSort(vector<int> &num_arr, int b, int e)
{
    if(b < e)
    {
        int index = partion(num_arr, b, e);

        quickSort(num_arr, b, index);
        quickSort(num_arr, index + 1, e);
    }
}

/*** Max subarray ***/
vector<int> max_crossarray(vector<int> num_arr, int b, int e)
{
    if(b == e)
    {
        vector<int> singleton = {b, e, num_arr[b]};
        return singleton;        
    }

    int mid = (b + e) / 2;
    int l, r, max_l, val_l, max_r, val_r, sum;

    l = mid;
    r = mid + 1;

    val_l = l;
    sum = max_l = num_arr[l];
    l--;

    while(l >= b)
    {
        sum = sum + num_arr[l];
        if(max_l < sum)
        {
            val_l = l;
            max_l = sum;
        }
        l--;
    }

    val_r = r;
    sum = max_r = num_arr[r];
    r++;

    while(r <= e)
    {
        sum = sum + num_arr[r];
        if(max_r < sum)
        {
            val_r = r;
            max_r = sum;
        }
        r++;
    }

    vector<int> cross_arr = {val_l, val_r, max_l + max_r};
    return cross_arr;
}

vector<int> max_subarray(vector<int> num_arr, int b, int e)
{
    if(b == e)
    {
        vector<int> singleton = {b, e, num_arr[b]};
        return singleton;        
    }

    int mid = (b + e) / 2;
    vector<int> l_arr = max_subarray(num_arr, b, mid);
    vector<int> r_arr = max_subarray(num_arr, mid + 1, e);
    vector<int> mid_arr = max_crossarray(num_arr, b, e);
    
    if(l_arr[2] >= r_arr[2] && l_arr[2] >= mid_arr[2])
    {
        return l_arr;
    }
    else if(r_arr[2] >= l_arr[2] && r_arr[2] >= mid_arr[2])
    {
        return r_arr;
    }

    return mid_arr;
}

int Kadane_array(vector<int> num_arr)
{
    int arr_size = num_arr.size();
    int curr_sum, max_sum, num;
    max_sum = curr_sum = num_arr[0];

    for(int i = 1; i < arr_size; i++)
    {
        num = num_arr[i];
        curr_sum = max(curr_sum + num, num);
        max_sum = max(max_sum, curr_sum);
    }

    return max_sum;
}

/*** Divide and conquer ***/
int BFPRT(vector<int> num_arr, int k)
{
    int arr_size = num_arr.size();

    if(arr_size ==  1)
    {
        return num_arr[0];
    }
    if(arr_size <= 5)
    {
        insertSort(num_arr);
        return num_arr[k - 1];
    }

    vector<int> medians_arr, chunk_arr;
    int i = 0;

    while (i < arr_size)
    {
        if(i != 0 && i % 5 == 0)
        {
            //display_vector(chunk_arr);
            medians_arr.push_back(BFPRT(chunk_arr, chunk_arr.size() / 2 + 1));
            chunk_arr.clear();
        }
        chunk_arr.push_back(num_arr[i]);
        i++;
    }
    
    if(chunk_arr.size() > 0)
    {
        //display_vector(chunk_arr);
        medians_arr.push_back(BFPRT(chunk_arr, chunk_arr.size() / 2 + 1));
        chunk_arr.clear();
    }

    insertSort(medians_arr);

    //display_vector(medians_arr);
    int median_medians = BFPRT(medians_arr, medians_arr.size() / 2 + 1);
    //cout << median_medians << '\n';

    vector<int> l_arr, r_arr;

    i = 0;
    while (i < arr_size)
    {
        if(num_arr[i] < median_medians)
        {
            l_arr.push_back(num_arr[i]);
        }
        else if(num_arr[i] > median_medians)
        {
            r_arr.push_back(num_arr[i]);
        }
        i++;
    }

    if(k == l_arr.size() + 1)
    {
        return median_medians;
    }
    else if(k <= l_arr.size())
    {
        return BFPRT(l_arr, k);
    }

    return BFPRT(r_arr, k - l_arr.size() - 1);
}


/*** heap sort ***/
class heap_tree
{
    typedef struct heap_node
    {
        struct heap_node *parent;
        struct heap_node *rchild;
        struct heap_node *lchild;
        int val;

        heap_node(int value, struct heap_node *pt = nullptr)
        {
            parent = pt;
            val = value;
            lchild = rchild = nullptr;
        }
    }heap_node;

};


int main()
{
    vector<int> num_arr = {3,2,1,5,6,4};

    return 0;
}