#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int BLOCK_SIZE = 32;

// Multiplicación por bloques (seis bucles anidados)
void multiplyBlocked(int N, vector<vector<double>>& A, vector<vector<double>>& B, vector<vector<double>>& C) {
    auto start = high_resolution_clock::now();

    for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
        for (int bj = 0; bj < N; bj += BLOCK_SIZE) {
            for (int bk = 0; bk < N; bk += BLOCK_SIZE) {
                for (int i = bi; i < min(bi + BLOCK_SIZE, N); i++) {
                    for (int j = bj; j < min(bj + BLOCK_SIZE, N); j++) {
                        for (int k = bk; k < min(bk + BLOCK_SIZE, N); k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    auto end = high_resolution_clock::now();
    cout << "Tiempo para (N=" << N << "): " << duration<double, milli>(end - start).count() << " ms" << endl;
}
int main() {
    // Tamaños de las matrices
    vector<int> sizes = {500, 1000, 1500};

    for (int N : sizes) {
        vector<vector<double>> A(N, vector<double>(N, 1.0));
        vector<vector<double>> B(N, vector<double>(N, 1.0));
        vector<vector<double>> C(N, vector<double>(N, 0.0));

        multiplyBlocked(N, A, B, C);
    }

    return 0;
}
