#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

const int N = 512;

void matAdd(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c, int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void matMul(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c, int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}

// Sequential versions for comparison
void matAdd_sequential(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void matMul_sequential(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}

int main() {
    cout << "CPU Parallel Matrix Operations (OpenMP)" << endl;
    cout << "Matrix size: " << N << "x" << N << "\n\n";

    // Host memory allocation using vectors
    vector<vector<int>> a(N, vector<int>(N, 1));
    vector<vector<int>> b(N, vector<int>(N, 1));
    vector<vector<int>> add_seq(N, vector<int>(N, 0));
    vector<vector<int>> add_par(N, vector<int>(N, 0));
    vector<vector<int>> mul_seq(N, vector<int>(N, 0));
    vector<vector<int>> mul_par(N, vector<int>(N, 0));

    // Sequential Matrix Addition
    auto start = chrono::high_resolution_clock::now();
    matAdd_sequential(a, b, add_seq, N);
    auto end = chrono::high_resolution_clock::now();
    
    cout << "== Sequential Matrix Addition ==\n";
    cout << "C[0][0] = " << add_seq[0][0] << " (expected 2)\n";
    cout << "C[1][1] = " << add_seq[1][1] << " (expected 2)\n";
    cout << "Time Required: " << chrono::duration<double, milli>(end - start).count() << " ms\n\n";

    // Parallel Matrix Addition
    start = chrono::high_resolution_clock::now();
    matAdd(a, b, add_par, N);
    end = chrono::high_resolution_clock::now();
    
    cout << "== Parallel Matrix Addition (OpenMP) ==\n";
    cout << "C[0][0] = " << add_par[0][0] << " (expected 2)\n";
    cout << "C[1][1] = " << add_par[1][1] << " (expected 2)\n";
    cout << "Time Required: " << chrono::duration<double, milli>(end - start).count() << " ms\n\n";

    // Sequential Matrix Multiplication
    start = chrono::high_resolution_clock::now();
    matMul_sequential(a, b, mul_seq, N);
    end = chrono::high_resolution_clock::now();
    
    cout << "== Sequential Matrix Multiplication ==\n";
    cout << "C[0][0] = " << mul_seq[0][0] << " (expected " << N << ")\n";
    cout << "C[1][1] = " << mul_seq[1][1] << " (expected " << N << ")\n";
    cout << "Time Required: " << chrono::duration<double, milli>(end - start).count() << " ms\n\n";

    // Parallel Matrix Multiplication
    start = chrono::high_resolution_clock::now();
    matMul(a, b, mul_par, N);
    end = chrono::high_resolution_clock::now();
    
    cout << "== Parallel Matrix Multiplication (OpenMP) ==\n";
    cout << "C[0][0] = " << mul_par[0][0] << " (expected " << N << ")\n";
    cout << "C[1][1] = " << mul_par[1][1] << " (expected " << N << ")\n";
    cout << "Time Required: " << chrono::duration<double, milli>(end - start).count() << " ms\n\n";

    cout << "Execution completed successfully!" << endl;
    return 0;
}
