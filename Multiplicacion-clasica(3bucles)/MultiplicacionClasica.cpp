#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Multiplicacion clasica
void multiplyClassic(int N, vector<vector<double>>& A, vector<vector<double>>& B, vector<vector<double>>& C) {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = high_resolution_clock::now();
    cout << "Multiplicacion clasica (N=" << N << "): " << duration<double, milli>(end - start).count() << " ms" << endl;
}
int main() {
    // Tamaños de matriz
    vector<int> sizes = {500, 1000, 1500}; 

    for (int N : sizes) {
        vector<vector<double>> A(N, vector<double>(N, 1.0));
        vector<vector<double>> B(N, vector<double>(N, 1.0));
        vector<vector<double>> C(N, vector<double>(N, 0.0));

        multiplyClassic(N, A, B, C);
   }
    return 0;
}
