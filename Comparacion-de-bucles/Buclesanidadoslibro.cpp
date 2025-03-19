#include <iostream>
#include <chrono>
using namespace std;

int main() {

    const int MAX = 4;
    double A[MAX][MAX] = { {1, 2, 3, 4},
                           {1, 2, 3, 4},
                           {1, 2, 3, 4},
                           {1, 2, 3, 4} };
    double x[MAX] = {1, 2, 3, 4};
    double y[MAX] = {0};

    //primer bucle
    auto start1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++){
            y[i] += A[i][j] * x[j];
        }
    }
    auto end1 = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration<double, milli>(end1 - start1).count();
    // Reiniciamos y
    for (int i = 0; i < MAX; i++) {
        y[i] = 0;
    }
    auto start2 = chrono::high_resolution_clock::now();
    //segundo bucle
    for (int j = 0; j < MAX; j++) {
        for (int i = 0; i < MAX; i++){
            y[i] += A[i][j]*x[j];
        }
    }
    auto end2 = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration<double, milli>(end2 - start2).count();

    // Comparacion de tiempos
    cout << "Bucle 1: " << time1 << " ms\n";
    cout << "Bucle 2: " << time2 << " ms\n";

    return 0;
}
