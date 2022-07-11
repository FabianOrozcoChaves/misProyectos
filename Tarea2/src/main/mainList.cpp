// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr

#include "llist.h"
#include <random>
#include <chrono>
#include <time.h>

using namespace std;
void llenarLista_azar(llist<int>* lista);
int buscar_azar(llist<int>* lista);
void llenarLista_sec(llist<int>* lista);

int main() {
  cout << "\n-inicia" << endl << endl;

  llist<int> *miLista;   miLista = new llist<int>();

  // seccion 2.1) paso 2
  // llena con 1M de numeros aleatorios [0,2M]. 
  llenarLista_azar(miLista);
  int qtyBusquedas = buscar_azar(miLista);
  cout << "Qty de busquedas en 10 segundos [llist]" << endl; 
  cout << "Aleatoria:  " << qtyBusquedas << endl;


  delete miLista;
  // seccion 2.1) paso 3
  // llena con 1M de numeros ordenados [0,2M]. 
  miLista = new llist<int>();
  llenarLista_sec(miLista);
  qtyBusquedas = buscar_azar(miLista);
  cout << "Secuencial: " << qtyBusquedas << endl;
  // miLista->imprimirLista();

  
  // miLista->imprimirLista();
  delete miLista;
  cout << "\n-termina" << endl;
  return 0;
}

// ################################################################

void llenarLista_azar(llist<int>* lista) {
  random_device dev;
  mt19937 rng(dev());
  for (int i = 0; i < 1000000; ++i) {
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000); // rango
    llnode<int> * nodo = new llnode<int>(dist6(rng));
    lista->listInsert(nodo);
  }
}

// ################################################################

int buscar_azar(llist<int>* lista){
  auto start = chrono::system_clock::now();
  random_device r;
  mt19937 eng(0);
  int qtyBusquedas = 0;
  while (true)
  {  
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000);
    int num_buscado = dist6(r);
    // cout << num_buscado << " ";
    lista->listSearch(num_buscado);
    auto end = chrono::system_clock::now();
    auto time_elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
    ++qtyBusquedas;
    if (time_elapsed == 10) return qtyBusquedas;
  }
  return 0;
}

// ################################################################

void llenarLista_sec(llist<int>* lista) {
  for (int i = 0; i < 1000000; ++i) {
    llnode<int> * nodo = new llnode<int>(i);
    lista->listInsert(nodo);
  }
}
// ################################################################

// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr
