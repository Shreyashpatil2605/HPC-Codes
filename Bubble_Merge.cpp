#include<iostream>
#include<bits/stdc++.h>
#include<iomanip>
#include<chrono>
#include<vector>

using namespace std;

void sequential_bubble_sort(vector<int> arr) {

    vector<int> array = arr;

    auto start = chrono::high_resolution_clock::now();

    int size = array.size();
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(array[j] > array[j + 1])
                swap(array[j], array[j + 1]);
        }
    }

    auto end = chrono::high_resolution_clock::now();

    cout << "\nSequential Bubble Sort:\n";

    for(int i = 0; i < size; i++)
        cout << array[i] << " ";

    cout << fixed << setprecision(6);

    cout << "\nTime Required: "
         << chrono::duration<double, milli>(end - start).count()
         << " ms\n";
}

void parallel_bubble_sort(vector<int> arr) {

    vector<int> array = arr;

    auto start = chrono::high_resolution_clock::now();

    int size = array.size();
    for(int k = 0; k < size; k++) {

        if(k % 2 == 0) {

            for(int i = 1; i < size - 1; i += 2) {
                if(array[i] > array[i + 1])
                    swap(array[i], array[i + 1]);
            }

        } else {

            for(int i = 0; i < size - 1; i += 2) {
                if(array[i] > array[i + 1])
                    swap(array[i], array[i + 1]);
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();

    cout << "\nParallel Bubble Sort:\n";

    for(int i = 0; i < size; i++)
        cout << array[i] << " ";

    cout << fixed << setprecision(6);

    cout << "\nTime Required: "
         << chrono::duration<double, milli>(end - start).count()
         << " ms\n";
}

void merge(vector<int>& array, int low, int mid, int high) {

    vector<int> temp(high - low + 1);

    int i = low;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= high) {

        if(array[i] < array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    while(i <= mid)
        temp[k++] = array[i++];

    while(j <= high)
        temp[k++] = array[j++];

    k = 0;

    for(int i = low; i <= high; i++)
        array[i] = temp[k++];
}

void mergesort(vector<int>& array, int low, int high) {

    if(low < high) {

        int mid = (low + high) / 2;

        mergesort(array, low, mid);
        mergesort(array, mid + 1, high);

        merge(array, low, mid, high);
    }
}

void perform_merge_sort(vector<int> arr) {

    vector<int> array = arr;

    auto start = chrono::high_resolution_clock::now();

    mergesort(array, 0, array.size() - 1);

    auto end = chrono::high_resolution_clock::now();

    cout << "\nSequential Merge Sort:\n";

    for(int i = 0; i < array.size(); i++)
        cout << array[i] << " ";

    cout << fixed << setprecision(6);

    cout << "\nTime Required: "
         << chrono::duration<double, milli>(end - start).count()
         << " ms\n";
}

void p_mergesort(vector<int>& array, int low, int high) {

    if(low < high) {

        int mid = (low + high) / 2;

        p_mergesort(array, low, mid);
        p_mergesort(array, mid + 1, high);

        merge(array, low, mid, high);
    }
}

void perform_p_merge_sort(vector<int> arr) {

    vector<int> array = arr;

    auto start = chrono::high_resolution_clock::now();

    p_mergesort(array, 0, array.size() - 1);

    auto end = chrono::high_resolution_clock::now();

    cout << "\nParallel Merge Sort:\n";

    for(int i = 0; i < array.size(); i++)
        cout << array[i] << " ";

    cout << fixed << setprecision(6);

    cout << "\nTime Required: "
         << chrono::duration<double, milli>(end - start).count()
         << " ms\n";
}

int main() {

    int SIZE;

    cout << "Enter size of array: ";
    cin >> SIZE;

    vector<int> array(SIZE);

    cout << "Enter array elements:\n";

    for(int i = 0; i < SIZE; i++)
        cin >> array[i];

    sequential_bubble_sort(array);

    parallel_bubble_sort(array);

    perform_merge_sort(array);

    perform_p_merge_sort(array);

    return 0;
}