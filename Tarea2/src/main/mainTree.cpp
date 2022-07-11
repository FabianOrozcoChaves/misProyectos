// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr

#include <chrono>
#include <iostream>
#include <random>

#include "bstree.h"

using namespace std;

void f_testTree( tree<int>* );      // prueba un arbol de 10 nodos
void f_fillTree_test( tree<int>* ); // llena con rango -50 a 50


void f_fillTree_rand( tree<int>* ); // llena el arbol con 1M de nums aleatorios
void f_treeData( tree<int>* ); // imprime los datos del arbol

// busca recursivamente por 10s (semilla distinta a la de inserción)
int f_search_rand_rec( tree<int>* ); 
// busca iterativamente por 10s  (semilla distinta a la de inserción)
int f_search_rand_it( tree<int>* ); 

int main() {
  cout << "\n-inicia\n" << endl;

  tree<int>* myTree;
  myTree = new tree<int>();

  // seccion 2.2) paso 2
  f_fillTree_rand(myTree); // llena aleatoriamente con 1M de nodos. rango: [0,2M]
  
  int qtyBusquedas = 0;
  qtyBusquedas = f_search_rand_rec(myTree);
  cout << "Qty de busquedas en 10 segundos [tree]" << endl; 
  cout << "Aleatoria[rec]:  " << qtyBusquedas << endl;
  qtyBusquedas = f_search_rand_it(myTree);
  cout << "Aleatoria[it]:   " << qtyBusquedas << endl;

  f_treeData(myTree);
  // myTree->f_forma(myTree->getRoot());
  // myTree->inorderTreeWalk(myTree->getRoot());
  myTree->treeSuccessor(myTree->getRoot());
  
  delete myTree;

  myTree = new tree<int>();
  myTree->f_fillTree_sec(1000000); // llena de 0 a 999999

  qtyBusquedas = f_search_rand_rec(myTree);
  cout << "Secuencial[rec]: " << qtyBusquedas << endl;
  qtyBusquedas = f_search_rand_it(myTree);
  cout << "Secuencial[it]:  " << qtyBusquedas << endl;

  delete myTree;
  cout << "\n-termina" << endl;
  return 0;
}

// ################################################################

void f_fillTree_test(tree<int>* tree){
  cout << "inserción: ";
  random_device dev;
  mt19937 rng(dev());
  for (int i = 0; i < 10; ++i) {
    uniform_int_distribution<mt19937::result_type> dist6(-50,50);
    int num = dist6(rng);
    cout << num << " ";
    node<int> * nodo = new node<int>(num);
    tree->treeInsert(nodo);
  }
  cout << endl;
}

// ################################################################

void f_fillTree_rand(tree<int>* tree){
  random_device dev;
  mt19937 rng(dev());
  for (int i = 0; i < 1000000; ++i) {
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000);
    node<int> * nodo = new node<int>(dist6(rng));
    tree->treeInsert(nodo);
  }
}
// ################################################################


// ################################################################
void f_testTree(tree<int>* myTree) {
  f_fillTree_test(myTree);
  // myTree->treeInsert( new node<int>(0) );
  node<int>* myTreeRoot = myTree->getRoot();

  cout << "recInOrder: "; myTree->inorderTreeWalk(myTreeRoot);
  cout << endl;
  
  int numBuscado = 6;
  if (myTree->treeSearch(numBuscado) ){
    cout << numBuscado << " ha sido encontrado [rec]\n";
  } else { cout << numBuscado << " no ha sido encontrado [rec]\n";}

  if (myTree->iterativeTreeSearch(numBuscado) ){
    cout << numBuscado << " ha sido encontrado [it]\n";
  } else { cout << numBuscado << " no ha sido encontrado [it]\n";}

  f_treeData(myTree);
  
}
// ################################################################

void f_treeData(tree<int>* myTree) {
  node<int>* myTreeRoot = myTree->getRoot();
  cout << "\nrootKey: " << myTreeRoot->key << "\n";
  cout << "treeMaximum: " << (myTree->treeMaximum())->key << "\n";
  cout << "treeMinimum: " << (myTree->treeMinimum())->key << "\n";
  
  cout << "derecha de root: ";
  if (myTreeRoot->right){cout << myTreeRoot->right->key << "\n";}
  else {cout << "nullptr\n";}

  cout << "izquierda de root: ";
  if (myTreeRoot->left) {cout<< myTreeRoot->left->key << "\n";}
  else {cout << "nullptr\n";}

  cout << "Sucesor de " << myTreeRoot->key << ": " \
    << (myTree->treeSuccessor(myTreeRoot))->key << "\n";
  cout << "rootKey: " << myTreeRoot->key << "\n";
}

// ################################################################

// busca con el método recursivo (usa otra semilla, distinta a la de inserción)
int f_search_rand_rec(tree<int>* myTree){
  // cout << "\n\nPruebas\n";
  auto start = chrono::system_clock::now();
  random_device r;
  mt19937 eng(0);
  int qtyBusquedas = 0;
  while (true) {
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000);
    int num_buscado = dist6(r);
    // cout << num_buscado << " ";
    myTree->treeSearch(num_buscado);
    auto end = chrono::system_clock::now();
    auto time_elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
    ++qtyBusquedas;
    if (time_elapsed == 10) return qtyBusquedas;
  }
  return 0;
}

// ################################################################

// busca con el método iterativo (usa otra semilla, distinta a la de inserción)
int f_search_rand_it(tree<int>* myTree){
  // cout << "\n\nPruebas\n";
  auto start = chrono::system_clock::now();
  random_device r;
  mt19937 eng(0);
  int QtyBusquedas = 0;
  while (true) {
    uniform_int_distribution<mt19937::result_type> dist6(0,2000000);
    int num_buscado = dist6(r);
    // cout << num_buscado << " ";
    myTree->iterativeTreeSearch(num_buscado);
    auto end = chrono::system_clock::now();
    auto time_elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
    ++QtyBusquedas;
    if (time_elapsed == 10) return QtyBusquedas;
  }
  return 0;
}
// ################################################################

// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr
