// A
#include <cuda_runtime.h>
#include <iostream>

void matrixAddHost(float* h_C, const float* h_A, const float* h_B, int N,
                   void (*kernel)(float*, const float*, const float*, int)) {
    size_t size = N * N * sizeof(float);
    float *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}
// B
__global__ void matrixAddElementKernel(float* C, const float* A, const float* B, int N) {
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N && j < N) {
        int index = i * N + j;
        C[index] = A[index] + B[index];
    }
}
// Configuración de ejecución:
dim3 threadsPerBlock(16, 16);
dim3 numBlocks((N + 15) / 16, (N + 15) / 16);
matrixAddElementKernel<<<numBlocks, threadsPerBlock>>>(d_C, d_A, d_B, N);

//C
__global__ void matrixAddRowKernel(float* C, const float* A, const float* B, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        for (int j = 0; j < N; j++) {
            int index = i * N + j;
            C[index] = A[index] + B[index];
        }
    }
}

// Configuración de ejecución:
dim3 threadsPerBlock(256);
dim3 numBlocks((N + 255) / 256);
matrixAddRowKernel<<<numBlocks, threadsPerBlock>>>(d_C, d_A, d_B, N);

//D
__global__ void matrixAddColumnKernel(float* C, const float* A, const float* B, int N) {
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    if (j < N) {
        for (int i = 0; i < N; i++) {
            int index = i * N + j;
            C[index] = A[index] + B[index];
        }
    }
}

// Configuración de ejecución:
dim3 threadsPerBlock(256);
dim3 numBlocks((N + 255) / 256);
matrixAddColumnKernel<<<numBlocks, threadsPerBlock>>>(d_C, d_A, d_B, N);

//E
