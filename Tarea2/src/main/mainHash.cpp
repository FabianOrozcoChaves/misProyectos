// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr

#include "hasht.h"

#include <chrono>
#include <iostream>
#include <random>
// #include <list>
// #include <vector>

using namespace std;

// ############################################################################
void imprimirTabla(vector<list<int> > tabla);
void llenarTabla_azar(hasht<int>* tabla, int size);
void llenarTabla_sec(hasht<int>* tabla, int size);
int busqueda(hasht<int>* tabla, int segundos);
// ############################################################################

int main() {
  cout << "\n-inicia" << endl << endl;

  int qtyEntradas = 1000000, numBuscado = 696750, segundos = 10;
  cout << "Se construye la tabla aleatoria con " << qtyEntradas << " entradas" << endl;
  hasht<int>* myTable = new hasht<int>(qtyEntradas);
  
  cout << "Llena la tabla aleatoria" << endl;
  llenarTabla_azar(myTable, qtyEntradas);

  // cout << "Tabla:"; myTable->imprimirTabla();

  cout << "\nBusqueda de " << numBuscado << ": ";
  if (myTable->search(numBuscado)) cout << "encontrado" << endl;
  else cout << "NO encontrado" << endl;

  cout << "Test [busqueda] en " << segundos << "s..." << endl;
  cout << " Cantidad de busquedas: " << busqueda(myTable, segundos) << endl;

  delete myTable;
  // ==========================================================================
  numBuscado = 6;
  cout << "\nSe construye la tabla secuencial con " << qtyEntradas << " entradas" << endl;
  myTable = new hasht<int>(qtyEntradas);
  
  cout << "Llena la tabla secuencial" << endl;
  llenarTabla_sec(myTable, qtyEntradas);

  // cout << "Tabla:"; myTable->imprimirTabla();

  cout << "\nBusqueda de " << numBuscado << ": ";
  if (myTable->search(numBuscado)) cout << "encontrado" << endl;
  else cout << "NO encontrado" << endl;

  cout << "Test [busqueda] en " << segundos << "s..." << endl;
  cout << " Cantidad de busquedas: " << busqueda(myTable, segundos) << endl;
  // -------------------------------------
  delete myTable;

  cout << "\n-termina" << endl;
  return 0;
}

// ############################################################################
void llenarTabla_azar(hasht<int>* tabla, int size){
  random_device dev;
  mt19937 rng(dev());
  for (int i = 0; i < size; ++i) {
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000); // rango
    tabla->insert(dist6(rng));
  }
}
// ############################################################################
void llenarTabla_sec(hasht<int>* tabla, int size){
  for (int i = 0; i < size; ++i) {
    tabla->insert(i);
  }
}
// ############################################################################

void imprimirTabla(vector<list<int> > tabla){
  for (size_t i = 0; i < tabla.size(); ++i) {
    for (list<int>::iterator it = tabla[i].begin(); it != tabla[i].end(); ++it) {
      cout << ' ' << *it;
    }
  }
};
// ############################################################################

int busqueda(hasht<int>* tabla, int segundos) {
  int qtyBusquedas = 0;
  auto start = chrono::system_clock::now();
  random_device r;
  mt19937 eng(0);

  while (true) {
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000);
    int num_buscado = dist6(r);
    // cout << "\nbusqueda -> numBuscado: " << num_buscado << endl;
    tabla->search(num_buscado);
    ++qtyBusquedas;
    if (chrono::system_clock::now() - start > chrono::seconds(segundos)) break;
  }
  return qtyBusquedas;
}
// #############################################################################

// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr
