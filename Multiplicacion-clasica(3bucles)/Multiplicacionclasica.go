package main

import (
	"fmt"
	"time"
)

func multiplyMatrices(N int) {
	A := make([][]float64, N)
	B := make([][]float64, N)
	C := make([][]float64, N)

	// Inicializar matrices
	for i := range A {
		A[i] = make([]float64, N)
		B[i] = make([]float64, N)
		C[i] = make([]float64, N)
		for j := range A[i] {
			A[i][j] = 1.0
			B[i][j] = 1.0
		}
	}

	start := time.Now()

	// Multiplicacion clasica
	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			for k := 0; k < N; k++ {
				C[i][j] += A[i][k] * B[k][j]
			}
		}
	}

	duration := time.Since(start).Milliseconds()

	fmt.Printf("Tiempo para N = %d: %d ms\n", N, duration)
}

func main() {
  // Tamaños de las matrices
	sizes := []int{500, 1000, 1500} 

	for _, N := range sizes {
		multiplyMatrices(N)
	}
}
