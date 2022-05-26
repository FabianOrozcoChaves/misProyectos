/**
 * Copyright 2021 <fabian.orozcochaves@ucr.ac.cr>.
 * Analisis de algoritmos y estructuras de datos - 2021 II Ciclo - B95690. T1
 * Nota: uso de tildes omitido para evitar errores de interpretación con C++.
 * 
 * Se utiliza INT_MAX como centinela el cual sustituye al valor ∞ utilizado 
 * en el libro, para ello se incluye la biblioteca <limits.h>.
 * 
 * Se adjunta a cada implementacion la linea de pseudocodigo como buena
 * practica de programacion.
 */
#ifndef Ordenador_h
#define Ordenador_h

#include <limits.h>     // para utilizar INT_MAX como centinela (sustituye a inf).

class Ordenador{
	private:
	// Defina aqu� los m�todos auxiliares de los algoritmos de ordenamiento solamente.
    // Puede definir cuantos m�todos quiera.

    // parte de mergesort
	void mergeSort(int* arr, int inicio, int fin){
        // if p < r
        if (inicio < fin) {
            // q = [(p + r) / 2]
            int mitad = (inicio + fin) / 2;

            // mergeSort(A,p,q)
            mergeSort(arr, inicio, mitad);
            // mergeSort(A,q + 1, r)
            mergeSort(arr, mitad + 1, fin);
            // merge(A,p,q,r)
            merge(arr, inicio, mitad, fin);
        }
    }

    // parte de mergesort
    void merge(int* arr, int izq, int mitad, int der) {
        // p = izquierda, q = mitad, r = derecha, A = arr
        // n1 = q - p + 1
        const int subArr1 = mitad - izq + 1;
        // n2 = r - q
        const int subArr2 = der - mitad;
        // let L[1..n1 + 1] and R[1..n2 + 1] be new arrays
        int* izqArray = new int[subArr1 + 1];
        int* derArray = new int[subArr2 + 1];

        // for i = 1 to n1
        for (int i = 0; i < subArr1; ++i) {
            // L[i] = A[p + i - 1]
            izqArray[i] = arr[izq + i];
        }
        // for j = 1 to n2
        for (int j = 0; j < subArr2; ++j) {
            // R[j] = A[q + j]
            derArray[j] = arr[mitad + 1 + j];
        }

        // L[n1 + 1] = inf
        izqArray[subArr1] = INT_MAX;
        // R[n2 + 1 ] = inf
        derArray[subArr2] = INT_MAX;
        // i = 1 
        int indexSubArr1 = 0;
        //j = 1
        int indexSubArr2 = 0;

        // k = p
        for (int indexMergeArr = izq; indexMergeArr <= der; indexMergeArr++) {
            // if L[i] <= R[j]
            if (izqArray[indexSubArr1] <= derArray[indexSubArr2]) {
                // A[k] = L[i]
                arr[indexMergeArr] = izqArray[indexSubArr1];
                // i = i + 1
                ++indexSubArr1;
            // else 
            } else {
                // A[k] = R[j]
                arr[indexMergeArr] = derArray[indexSubArr2];
                // j = j + 1
                ++indexSubArr2;
            }
        }
        // liberacion de memoria dinamica.
        delete [] izqArray;
        delete [] derArray;
    }

    // parte de heapsort
    // MAX-HEAPIFY(A, i)
    void max_heapify(int* A, int i, int& length){
        // L = LEFT(i)
        int L = (i << 0x1);
        // r = RIGHT(i)
        int r =(i << 0x1) | 0x1;
        int largest = 0;
        // if L <= A.heap-size and A[L] > A[i]
        if (L <= length && A[L] > A[i]) {
            // largest = L
            largest = L;
        }
        // else largest = i
        else {
            largest = i;
        }
        // if r <= A.heap-size and A[r] > A[largest]
        if (r <= length && A[r] > A[largest]) {
            // largest = r
            largest = r;
        }
        // if largest ¡= i
        if(largest != i) {
            // exchange A[i] with A[largest]
            int temp = A[largest];
            A[largest] = A[i];
            A[i] = temp;
            // MAX-HEAPIFY(A, largest)
            max_heapify(A, largest, length);
        }
    }

    // parte de heapsort
    // BUILD-MAX-HEAP(A)
    void build_max_heap(int* A, int& length) {
        // A.heap-size = A.length
        int A_heap_size = length;
        // for i = rounddown(A.length/2) to 1
        for(int i = (A_heap_size/2); i > 0; --i) {
            // MAX-HEAPIFY(A, i)
            max_heapify(A, i, length);
        }
    }

    // parte de heapsort
    // HEAPSORT(A)
    void heapSort(int* A, int& length) {
        // BUILD-MAX-HEAP(A)
        build_max_heap(A, length);
        // for i = A.length downto 2
        for(int i = length; i > 1; --i) {
            // exchange A[1] with A[i]
            int temp = A[i];
            A[i] = A[1];
            A[1] = temp;
            // A.heap-size = A.heap-size - 1
            --length;
            // MAX-HEAPIFY(A, 1)
            max_heapify(A,1, length);
        }
    }

    // parte de quicksort
    // PARTITION(A, p, r)
    int partition(int* array, int inicio, int fin) {
        // x = A[r]
        int x = array[fin];
        //i = p - 1
        int i = inicio - 1;
        //for j = p to r - 1
        for (int j = inicio; j < fin; ++j) {
            // if A[j] <= x
            if (array[j] <= x) {
                // i = i + 1
                ++i;
                // exchange A[i] with A[j]
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
        // exchange A[i+1] with A[r]
        int temp = array[fin];
        array[fin] = array[i+1];
        array[i+1] = temp;
        return i + 1;
    }

    // parte de quicksort
    // QUICKSORT(A, p, r)
    void quickSort(int* array, int inicio, int fin) {
        // if p < r
        if (inicio < fin) {
            // q = PARTITION(A, p, r)
            int pivote = partition(array, inicio, fin);

            // QUICKSORT(A, p, q - 1)
   	        quickSort(array, inicio, pivote-1);

   	        // QUICKSORT(A, q + 1, r)
   	        quickSort(array, pivote+1, fin);
        }
    }

    // parte de radixSort
// COUNTING-SORT(A, B, k)
void countingSort(int* A, int* B, int k, int& length) {
    A--; B--;
    //  let C[0…k] be a new array
    int* C = new int[k];
    //  for i = 0 to k => // C[i] = 0
    for (int i=0; i < k; ++i) { C[i] = 0; } // inicializa contadores en 0
    // for j = 1 to A.length =>  // C[A[j]] = C[A[j]] + 1
    for(int j = 1; j <= length; ++j) { C[A[j]] = C[A[j]] + 1; } // cantidad de veces que está cada número
    // for i = 1 to k => // C[i] = C[i] + C[i-1]
    for(int i = 1; i < k; ++i) { C[i] = C[i] + C[i-1]; }// cantidad de menores o iguales a cada elemento
    for(int j = length; j > 0; --j) { // for j = A.length downto 1
        B[C[A[j]]] = A[j]; // B[C[A[j]]] = A[j]
        C[A[j]] = C[A[j]] - 1; // C[A[j]] = C[A[j]] - 1
    }
}

    // parte de radixSort
    int maximo(int* A, int size) { // retorna el num mayor de un arreglo
        int max = A[0];
        for (int i = 0; i < size; ++i) { if (A[i] > max) max = A[i]; }
        return max;
    }

    void invert_array(int *A, int length) { // invierte el orden del arreglo
        int i, j, temp;
        for(i = 0, j = length-1; i < length/2; i++ , j--) {
            temp=A[i];
            A[i]=A[j];
            A[j]=temp;
        }
    }

    // parte de radixSort
    void cuenteSignos(int* A, int& length,int& qtyNegativos, int& qtyPositivos) { // cuenta la cantidad de negativos y positivos en el arreglo principal
        for (int i = 0; i < length; ++i) { A[i] < 0 ? ++qtyNegativos : ++qtyPositivos; }
    }

	public:
	Ordenador(){;}
	~Ordenador(){;}
	
	// Si piensa no implementar algunos de los m�todos de ordenamiento, no los borre,
	// simplemente d�jelos con el cuerpo vac�o para evitar errores de compilaci�n, ya
	// que se va a ejecutar el mismo �main� para todas las tareas.
    // Implemente los algoritmos en este archivo  (no en un CPP aparte).
	void seleccion(int *A, int n) {
        // Para i = 1...n
        for (int i = 0; i < n - 1; ++i) {
            // m = i
            int min = i;
            // Para j = i + 1...n
            for (int j = i + 1; j < n; ++j) {
                // si A[j] < A[m] // m = j
                if (A[j] < A[min]) min = j;
            }
            // t = A[i];
            int aux = A[i];
            // A[i] = A[m];
            A[i] = A[min];
            // A[m] = aux;
            A[min] = aux;
        }
	}

	void insercion(int *A, int n) {
		int j, key, i;
        // for j = 2 to A.length
		for (j=1; j < n; ++j) {
            //key = A[j]
            key = A[j];
            // insert A[j] into the sorted
                // sequence A[1...j-1]
            //i = j - 1
            i = j-1;
            // while i > 0 and A[i] > key
            while (i >= 0 && A[i] > key) {
                // A[i+1] = A[i]
                A[i+1] = A[i];
                // i = i-1
                --i;
            }
            // A[i+1] = key
            A[i+1] = key;
        }
	}

	void mergesort(int* A, int n) {
        mergeSort(A, 0, n-1);
    }

    void heapsort(int* A, int n) {
        A--;
        heapSort(A,n);
    }

	void quicksort(int *A, int n) {
        quickSort(A, 0, n);
    }

    void radixsort(int* A, int n) {
        int qtyNegativos = 0, qtyPositivos = 0;
        cuenteSignos(A, n, qtyNegativos, qtyPositivos);

        int* negativos = new int[qtyNegativos];
        int* negOrdenados = new int[qtyNegativos];
        int* positivos = new int[qtyPositivos];
        int* posOrdenados = new int[qtyPositivos];

        int j = 0, k = 0;
        for(int i = 0; i < n; ++i) { // llena subarreglos (negativo y positivo)
            A[i] < 0 ? negativos[j++] = -A[i] : positivos[k++] = A[i];
        }
        // ordena positivos
        int max = maximo(positivos, qtyPositivos);
        countingSort(positivos, posOrdenados, max+1, qtyPositivos);
        // ordena negativos
        max = maximo(negativos, qtyNegativos);
        countingSort(negativos, negOrdenados, max+1, qtyNegativos);
        invert_array(negOrdenados, qtyNegativos);
        // hace merge de negativos y positivos al principal
        int i = 0;
        for( ; i < qtyNegativos; ++i) { A[i] = -negOrdenados[i]; }
        for( k = 0 ; k < qtyPositivos; ++k){ A[i++] = posOrdenados[k]; }
    }
};
#endif
