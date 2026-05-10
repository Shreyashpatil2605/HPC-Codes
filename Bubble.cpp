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

    return 0;
}
