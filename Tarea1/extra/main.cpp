/**
 * Copyright 2021 <fabian.orozcochaves@ucr.ac.cr>
 * Análisis de algoritmos y estructuras de datos - 2021 II Ciclo - B95690.
 * Nota: uso de tildes omitido para evitar errores de interpretación con C++
 * 
 * El main realiza la creacion, inicializacion de cuatro arreglos, los randomiza,
 * ordena (tomando el tiempo que toma hacerlo) y además verifica que 
 * el ordenamiento sea correcto.
 * 
 * Compilar con: g++ main.cpp Ordenador.h -o tarea
 * Ejecutar con: ./tarea
 */
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <random>

#include "Ordenador.h"

using namespace std;

void randomize(int* array, int size) {
  random_device dev;
  mt19937 rng(dev());
  for (int i = 0; i < size; ++i) {
    uniform_int_distribution<mt19937::result_type> dist6(-size*10,size*10);
    array[i] = dist6(rng);
  }
}

void test(int* A, int n) {
for (int i = 1; i < n ; i ++)
  if( A [ i ] < A [i -1] )
    cout << " ¡Fallo! " << endl;
}

template <typename T>
void fTime(T& start, T& end) {
  cout 
  << setw(5)
  << chrono::duration_cast<chrono::seconds>(end - start).count()
  << setw(10)
  << chrono::duration_cast<chrono::milliseconds>(end - start).count()
  << setw(15)
  << chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

void run_algorithm(const char* alg_name, void (Ordenador::*function)(int*, int)
, Ordenador& ord, int* array, int size_array) {
  cout << "\n   " << alg_name << " time: ";
  auto start = chrono::system_clock::now();
  (ord.*function)(array, size_array);
  auto end = chrono::system_clock::now();

  fTime(start, end);
  test(array, size_array);
  randomize(array, size_array);
}

int main() {
  int sizeA = 50000, sizeB = 100000, sizeC = 150000, sizeD = 200000;

  int A[sizeA]; randomize(A, sizeA);
  int B[sizeB]; randomize(B, sizeB);
  int C[sizeC]; randomize(C, sizeC);
  int D[sizeD]; randomize(D, sizeD);

  Ordenador ordenador;

  int* arreglos[4] = {A,B,C,D};
  for (int arrActual = 0; arrActual < 4; ++arrActual) {
    int* array = arreglos[arrActual];
    int size = 0;

    cout << endl << "Arreglo";
    if (arrActual == 0){cout << " A | 50000\n";  size = 50000;}
    if (arrActual == 1){cout << " B | 100000\n"; size = 100000;}
    if (arrActual == 2){cout << " C | 150000\n"; size = 150000;}
    if (arrActual == 3){cout << " D | 200000\n"; size = 200000;}

    cout << setw(24) << "s" << setw(10) << "ms" << setw(15) << "ns";

    run_algorithm("Selection", &Ordenador::seleccion, ordenador, array, size);
    run_algorithm("Insertion", &Ordenador::insercion, ordenador, array, size);
    run_algorithm("MergeSort", &Ordenador::mergesort, ordenador, array, size);
    run_algorithm("HeapSort ", &Ordenador::heapsort,  ordenador, array, size);
    run_algorithm("QuickSort", &Ordenador::quicksort, ordenador, array, size);
    run_algorithm("RadixSort", &Ordenador::radixsort, ordenador, array, size);

    cout << endl;
  }
  cout << endl;
  return 0;
}
