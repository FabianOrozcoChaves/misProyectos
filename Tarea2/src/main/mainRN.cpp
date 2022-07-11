// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr

#include <chrono>
#include <iostream>
#include <random>

#include "rbtree.h"

void llenarARN_azar(rbtree<int>* tree, int size);
void llenarARN_sec(rbtree<int>* tree, int size);
int busqueda(rbtree<int>* tree, int segundos);
int busqueda_it(rbtree<int>* tree, int segundos);

// #############################################################################

int main() {
  cout << "\n-inicia" << endl << endl;

  int size = 1000000, numBuscado = 1188916, segundos = 10;
  cout << "Se construye el arbol" << endl;
  rbtree<int>* myTree = new rbtree<int>();
  
  cout << "Llena arbol aleatorio" << endl;
  llenarARN_azar(myTree, size);

  cout << "Arbol de menor a mayor: " << endl;
  // myTree->inorderTreeWalk(myTree->getRoot()); cout << endl;

  cout << "[busqueda recursiva] Llave " << numBuscado;
  if (myTree->treeSearch(numBuscado)) cout << " encontrada" << endl;
  else cout << " NO encontrada" << endl;

  cout << "[busqueda iterativa] Llave " << numBuscado;
  if (myTree->iterativeTreeSearch(numBuscado)) cout << " encontrada" << endl;
  else cout << " NO encontrada" << endl;

  cout << "maximo: " << myTree->treeMaximum()->key << endl;
  cout << "minimo: " << myTree->treeMinimum()->key << endl;
  cout << "sucesor de " << myTree->getRoot()->right->key << ": " 
        << myTree->treeSuccessor(myTree->getRoot()->right)->key << endl;

  cout << "Test#1: [busqueda recursiva] en " << segundos << "s..." << endl;
  cout << " Cantidad de busquedas: " << busqueda(myTree, segundos) << endl;

  cout << "Test#2: [busqueda iterativa] en " << segundos << "s..." << endl;
  cout << " Cantidad de busquedas: " << busqueda_it(myTree, segundos) << endl;
  delete myTree;

  // ==========================================================================
  cout << "\nConstruye arbol secuencial" << endl;
  myTree = new rbtree<int>();
  numBuscado = 0;

  cout << "Llena arbol secuencial" << endl;
  llenarARN_sec(myTree, size);

  cout << "Arbol de menor a mayor: " << endl;
  // myTree->inorderTreeWalk(myTree->getRoot()); cout << endl;

  cout << "[busqueda recursiva] Llave " << numBuscado;
  if (myTree->treeSearch(numBuscado)) cout << " encontrada" << endl;
  else cout << " NO encontrada" << endl;

  cout << "[busqueda iterativa] Llave " << numBuscado;
  if (myTree->iterativeTreeSearch(numBuscado)) cout << " encontrada" << endl;
  else cout << " NO encontrada" << endl;

  cout << "maximo: " << myTree->treeMaximum()->key << endl;
  cout << "minimo: " << myTree->treeMinimum()->key << endl;
  cout << "sucesor de " << myTree->getRoot()->right->key << ": " 
        << myTree->treeSuccessor(myTree->getRoot()->right)->key << endl;

  cout << "Test#1: [busqueda recursiva] en " << segundos << "s..." << endl;
  cout << " Cantidad de busquedas: " << busqueda(myTree, segundos) << endl;

  cout << "Test#2: [busqueda iterativa] en " << segundos << "s..." << endl;
  cout << " Cantidad de busquedas: " << busqueda_it(myTree, segundos) << endl;
  delete myTree;

  cout << "\n-termina" << endl;
  return 0;
}  // end main 

// #############################################################################
void llenarARN_azar(rbtree<int>* tree, int size){
  random_device dev;
  mt19937 rng(dev());
  for (int i = 0; i < size; ++i) {
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000); // rango
    rbnode<int>*node = new rbnode<int>(dist6(rng));
    tree->treeInsert(node);
  }
}

// #############################################################################
void llenarARN_sec(rbtree<int>* tree, int size){
  for (int i = 0; i < size; ++i) {
    rbnode<int>*node = new rbnode<int>(i);
    tree->treeInsert(node);
  }
}
// #############################################################################

int busqueda(rbtree<int>* tree, int segundos) {
  int qtyBusquedas = 0;
  auto start = chrono::system_clock::now();
  random_device r;
  mt19937 eng(0);

  while (true) {
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000);
    int num_buscado = dist6(r);
    // cout << "\nbusqueda -> numBuscado: " << num_buscado << endl;
    tree->treeSearch(num_buscado);
    ++qtyBusquedas;
    if (chrono::system_clock::now() - start > chrono::seconds(segundos)) break;
  }
  return qtyBusquedas;
}
// #############################################################################

int busqueda_it(rbtree<int>* tree, int segundos) {
  int qtyBusquedas = 0;
  auto start = chrono::system_clock::now();
  random_device r;
  mt19937 eng(0);

  while (true) {
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000);
    int num_buscado = dist6(r);
    // cout << "\nbusqueda -> numBuscado: " << num_buscado << endl;
    tree->iterativeTreeSearch(num_buscado);
    ++qtyBusquedas;
    if (chrono::system_clock::now() - start > chrono::seconds(segundos)) break;
  }
  return qtyBusquedas;
}
// #############################################################################

// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr
