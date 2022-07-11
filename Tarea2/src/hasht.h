// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr

#ifndef HASH_CLASS
#define HASH_CLASS
#include <list>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class hasht{
	public:
		// Constructor que especifica el numero de cubetas (entradas) 
		// en la tabla
		hasht(int nEntradas){
			numEntradas = nEntradas;
			tabla.resize(numEntradas);
		};

		// Destructor (borra la tabla)
		~hasht(){
			// crea un vector vacio sin memoria asignada y lo intercambia con <<tabla>>, deslocalizando efectivamente la memoria
			vector<list<T>>().swap(tabla);
		};

		// Retorna un puntero a la llave o NULL si no se encuentra
		T* search(const T& item){
			int posicion = item % numEntradas;
			list<int>::iterator it = tabla[posicion].begin();
			for ( ; it != tabla[posicion].end(); ++it){
				if (*it == item) {
					return &(*it);
				}
			}
			return NULL;
		};

		// Inserta el elemento en la tabla
		void insert(const T& item){
			int posicion = item % numEntradas;
			tabla[posicion].push_front(item);
		};

		// metodo extra para pruebas. Funciona.
		// void imprimirTabla(){
		// 	for (size_t i = 0; i < tabla.size(); ++i) {
		// 		list<int>::iterator it;
		// 		for (it = tabla[i].begin(); it != tabla[i].end(); ++it) {
		// 			cout << ' ' << *it;
		// 		}
		// 	}
		// };

	private:
		// Numero de entradas en la tabla
		int numEntradas;

		// La tabla es un vector de listas de STL
		vector<list<T> > tabla;
};
#endif

// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr
