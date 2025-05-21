#include <cuda_runtime.h>
#include <iostream>

// Kernel: cada thread calcula un elemento de A
__global__ void matVecMulKernel(float* A, const float* B, const float* C, int N) {
    int row = threadIdx.x + blockIdx.x * blockDim.x;
    if (row < N) {
        float sum = 0.0f;
        for (int j = 0; j < N; ++j) {
            sum += B[row * N + j] * C[j];  // Acceso lineal a la matriz
        }
        A[row] = sum;
    }
}

// Host stub function
void matVecMul(float* hostA, const float* hostB, const float* hostC, int N) {
    // Reservar memoria en el device
    float *devA, *devB, *devC;
    size_t matrixSize = N * N * sizeof(float);
    size_t vectorSize = N * sizeof(float);

    cudaMalloc((void**)&devA, vectorSize);
    cudaMalloc((void**)&devB, matrixSize);
    cudaMalloc((void**)&devC, vectorSize);

    // Copiar datos al device
    cudaMemcpy(devB, hostB, matrixSize, cudaMemcpyHostToDevice);
    cudaMemcpy(devC, hostC, vectorSize, cudaMemcpyHostToDevice);

    // Lanzar kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    matVecMulKernel<<<blocksPerGrid, threadsPerBlock>>>(devA, devB, devC, N);

    // Copiar resultado al host
    cudaMemcpy(hostA, devA, vectorSize, cudaMemcpyDeviceToHost);

    // Liberar memoria del device
    cudaFree(devA);
    cudaFree(devB);
    cudaFree(devC);
}
