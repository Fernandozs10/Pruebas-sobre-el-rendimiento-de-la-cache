package main

import (
	"fmt"
	"math"
	"time"
)

const BLOCK_SIZE int = 32 // Tamaño del bloque

// Multiplicacion por bloques (seis bucles anidados)
func multiplyBlocked(N int, A, B, C [][]float64) {
	start := time.Now()

	for bi := 0; bi < N; bi += BLOCK_SIZE {
		for bj := 0; bj < N; bj += BLOCK_SIZE {
			for bk := 0; bk < N; bk += BLOCK_SIZE {
				for i := bi; i < int(math.Min(float64(bi+BLOCK_SIZE), float64(N))); i++ {
					for j := bj; j < int(math.Min(float64(bj+BLOCK_SIZE), float64(N))); j++ {
						for k := bk; k < int(math.Min(float64(bk+BLOCK_SIZE), float64(N))); k++ {
							C[i][j] += A[i][k] * B[k][j]
						}
					}
				}
			}
		}
	}

	duration := time.Since(start).Milliseconds()
	fmt.Printf("Tiempo para (N=%d): %d ms\n", N, duration)
}

func main() {
	// Tamaños de las matrices
	sizes := []int{500, 1000, 1500}

	for _, N := range sizes {
		A := make([][]float64, N)
		B := make([][]float64, N)
		C := make([][]float64, N)

		// Inicializar matrices
		for i := 0; i < N; i++ {
			A[i] = make([]float64, N)
			B[i] = make([]float64, N)
			C[i] = make([]float64, N)
			for j := 0; j < N; j++ {
				A[i][j] = 1.0
				B[i][j] = 1.0
			}
		}

		multiplyBlocked(N, A, B, C)
	}
}
