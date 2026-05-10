#include<iostream>
#include<bits/stdc++.h>
#include<chrono>

using namespace std;

void minimum(const vector<int>& array){
    int min_serial = INT_MAX;
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < array.size(); i++){
        if(array[i] < min_serial){
            min_serial = array[i];
        } 
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Minimum Element: " << min_serial << endl;
    cout << "Time Taken: " << chrono::duration<double>(end - start).count() << " seconds" << endl; 
    int min_ele = INT_MAX;
    start = chrono::high_resolution_clock::now();
    // #pragma omp parallel for reduction(min: min_ele)
        for(int i = 0; i < array.size(); i++){
            if(array[i] < min_ele){
                min_ele = array[i];
            } 
        }
    end = chrono::high_resolution_clock::now();
    cout << "Minimum Element(Parallel Reduction - Sequential): " << min_ele << endl;
    cout << "Time Taken: " << chrono::duration<double>(end - start).count() << " seconds" << endl;
    
}

void maximum(const vector<int>& array){
    int max_serial = INT_MIN;
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < array.size(); i++){
        if(array[i] > max_serial){
            max_serial = array[i];
        } 
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Maximum Element: " << max_serial << endl;
    cout << "Time Taken: " << chrono::duration<double>(end - start).count() << " seconds" << endl; 
    int max_ele = INT_MIN;
    start = chrono::high_resolution_clock::now();
    // #pragma omp parallel for reduction(max: max_ele)
        for(int i = 0; i < array.size(); i++){
            if(array[i] > max_ele){
                max_ele = array[i];
            } 
        }
    end = chrono::high_resolution_clock::now();
    cout << "Maximum Element(Parallel Reduction - Sequential): " << max_ele << endl;
    cout << "Time Taken: " << chrono::duration<double>(end - start).count() << " seconds" << endl;
    
}

void sum(const vector<int>& array){
    int sum_serial = 0;
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < array.size(); i++){
        sum_serial += array[i]; 
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Summation: " << sum_serial << endl;
    cout << "Time Taken: " << chrono::duration<double>(end - start).count() << " seconds" << endl; 
    int sum_parallel = 0;
    start = chrono::high_resolution_clock::now();
    // #pragma omp parallel for reduction(+: sum_parallel)
        for(int i = 0; i < array.size(); i++){
            sum_parallel += array[i]; 
        }
    end = chrono::high_resolution_clock::now();
    cout << "Summation(Parallel Reduction - Sequential): " << sum_parallel << endl;
    cout << "Time Taken: " << chrono::duration<double>(end - start).count() << " seconds" << endl;
    
}
void average(const vector<int>& array){
    float avg_serial = 0;
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < array.size(); i++){
        avg_serial += array[i]; 
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Average: " << avg_serial / array.size() << endl;
    cout << "Time Taken: " << chrono::duration<double>(end - start).count() << " seconds" << endl; 
    float avg_parallel = 0;
    start = chrono::high_resolution_clock::now();
    // #pragma omp parallel for reduction(+: avg_parallel)
        for(int i = 0; i < array.size(); i++){
            avg_parallel += array[i]; 
        }
    end = chrono::high_resolution_clock::now();
    cout << "Average(Parallel Reduction - Sequential): " << avg_parallel / array.size() << endl;
    cout << "Time Taken: " << chrono::duration<double>(end - start).count() << " seconds" << endl;
    
}

int main(){
    cout << "Enter number of elements in array: ";
    int N;
    int MAX = 1000;
    cin >> N;
    vector<int> array;
    for(int i = 0; i < N; i++){
        array.push_back(rand() % MAX);
        cout << array[i] << " ";
    }
    minimum(array);
    maximum(array);
    sum(array);
    average(array);
    return 0;
}