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

	// Inicializado y en 0
	var y [MAX]float64 

	// Primer bucle
	start1 := time.Now()
	for i := 0; i < MAX; i++ {
		for j := 0; j < MAX; j++ {
			y[i] += A[i][j] * x[j]
		}
	}
	// Medir tiempo en ms
	time1 := time.Since(start1).Milliseconds() 
	
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
	
	// Medir tiempo en ms
	time2 := time.Since(start2).Milliseconds() 
	
	// Comparación de tiempos
	fmt.Printf("Bucle 1: %d ms\n", time1)
	fmt.Printf("Bucle 2: %d ms\n", time2)
}
