package main

import (
	"fmt"
	"time"
)

const MAX int = 4

func main() {
	// Definir la matriz y los vectores
	A := [MAX][MAX]float64{
		{1, 2, 3, 4},
		{1, 2, 3, 4},
		{1, 2, 3, 4},
		{1, 2, 3, 4},
	}
	x := [MAX]float64{1, 2, 3, 4}
	var y [MAX]float64 // Inicializado automáticamente en 0

	// Primer bucle
	start1 := time.Now()
	for i := 0; i < MAX; i++ {
		for j := 0; j < MAX; j++ {
			y[i] += A[i][j] * x[j]
		}
	}
	time1 := time.Since(start1).Milliseconds() // Medir tiempo en ms

	// Reiniciar y
	for i := 0; i < MAX; i++ {
		y[i] = 0
	}

	// Segundo bucle
	start2 := time.Now()
	for j := 0; j < MAX; j++ {
		for i := 0; i < MAX; i++ {
			y[i] += A[i][j] * x[j]
		}
	}
	time2 := time.Since(start2).Milliseconds() // Medir tiempo en ms

	// Comparación de tiempos
	fmt.Printf("Bucle 1: %d ms\n", time1)
	fmt.Printf("Bucle 2: %d ms\n", time2)
}
