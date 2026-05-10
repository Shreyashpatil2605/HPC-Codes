#include <iostream>
#include <cuda_runtime.h>
using namespace std;

#define CUDA_CHECK(err) { if (err != cudaSuccess) { cerr << "CUDA Error: " << cudaGetErrorString(err) << " at line " << __LINE__ << endl; exit(1); } }

const int N = 512;
const int TILE_SIZE = 16;

__global__ void matAdd(int* a, int* b, int* c, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < n && col < n)
        c[row * n + col] = a[row * n + col] + b[row * n + col];
}

// Optimized matrix multiplication using shared memory
__global__ void matMul(int* a, int* b, int* c, int n) {
    __shared__ int a_tile[TILE_SIZE][TILE_SIZE];
    __shared__ int b_tile[TILE_SIZE][TILE_SIZE];
    
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    
    int sum = 0;
    
    for (int tile = 0; tile < (n + TILE_SIZE - 1) / TILE_SIZE; tile++) {
        // Load tiles into shared memory
        int a_col = tile * TILE_SIZE + tx;
        int b_row = tile * TILE_SIZE + ty;
        
        if (row < n && a_col < n)
            a_tile[ty][tx] = a[row * n + a_col];
        else
            a_tile[ty][tx] = 0;
            
        if (b_row < n && col < n)
            b_tile[ty][tx] = b[b_row * n + col];
        else
            b_tile[ty][tx] = 0;
        
        __syncthreads();
        
        // Compute partial product
        for (int k = 0; k < TILE_SIZE; k++)
            sum += a_tile[ty][k] * b_tile[k][tx];
        
        __syncthreads();
    }
    
    if (row < n && col < n)
        c[row * n + col] = sum;
}

int main() {
    // Check for CUDA capable devices
    int deviceCount = 0;
    CUDA_CHECK(cudaGetDeviceCount(&deviceCount));
    
    if (deviceCount == 0) {
        cerr << "No CUDA capable GPU found!" << endl;
        return 1;
    }
    
    cout << "CUDA Devices found: " << deviceCount << endl;
    
    int size = N * N * sizeof(int);

    // Host memory allocation
    int *a = new int[N*N], *b = new int[N*N];
    int *add = new int[N*N], *mul = new int[N*N];

    // Initialize matrices
    for (int i = 0; i < N * N; i++) { a[i] = 1; b[i] = 1; }

    // Device memory allocation with error checking
    int *da, *db, *dadd, *dmul;
    CUDA_CHECK(cudaMalloc(&da,   size));
    CUDA_CHECK(cudaMalloc(&db,   size));
    CUDA_CHECK(cudaMalloc(&dadd, size));
    CUDA_CHECK(cudaMalloc(&dmul, size));

    // Copy data to device with error checking
    CUDA_CHECK(cudaMemcpy(da, a, size, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(db, b, size, cudaMemcpyHostToDevice));

    dim3 threads(TILE_SIZE, TILE_SIZE);
    dim3 blocks((N + TILE_SIZE - 1) / TILE_SIZE, (N + TILE_SIZE - 1) / TILE_SIZE);

    // Matrix Addition
    matAdd<<<blocks, threads>>>(da, db, dadd, N);
    CUDA_CHECK(cudaDeviceSynchronize());  // Wait for kernel to complete
    CUDA_CHECK(cudaMemcpy(add, dadd, size, cudaMemcpyDeviceToHost));

    // Matrix Multiplication
    matMul<<<blocks, threads>>>(da, db, dmul, N);
    CUDA_CHECK(cudaDeviceSynchronize());  // Wait for kernel to complete
    CUDA_CHECK(cudaMemcpy(mul, dmul, size, cudaMemcpyDeviceToHost));

    cout << "\nMatrix size: " << N << "x" << N << "\n\n";

    cout << "== Matrix Addition ==\n";
    cout << "C[0][0] = " << add[0]   << " (expected 2)\n";
    cout << "C[1][1] = " << add[N+1] << " (expected 2)\n\n";

    cout << "== Matrix Multiplication ==\n";
    cout << "C[0][0] = " << mul[0]   << " (expected " << N << ")\n";
    cout << "C[1][1] = " << mul[N+1] << " (expected " << N << ")\n";

    // Free device memory with error checking
    CUDA_CHECK(cudaFree(da));
    CUDA_CHECK(cudaFree(db));
    CUDA_CHECK(cudaFree(dadd));
    CUDA_CHECK(cudaFree(dmul));
    
    // Free host memory
    delete[] a; delete[] b; delete[] add; delete[] mul;
    
    cout << "\nExecution completed successfully!" << endl;
    return 0;
}
