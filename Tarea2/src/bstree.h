// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr
#ifndef BINARY_SEARCH_Tree
#define BINARY_SEARCH_Tree
#include <iostream>
#include <string>

using namespace std;

// Nodos del arbol:
template <typename T>
class node{
public:
    // Esta clase es usada por otras clases.
    // Para mayor eficiencia, los atributos se hacen publicos.
    T key;
    node<T> *p, *left, *right;
    
    // Constructor por omision
    node(){
        key = 0;
        p = nullptr;
        left = nullptr;
        right = nullptr;
    };
    
    // Inicializacion de datos miembro
    node(const T& k, node<T> *w = NULL, node<T> *y = NULL, node<T> *z = NULL):key(k), p(w), left(y), right(z){};
    
    ~node(){
    }
};

// Arbol:
template <typename T>
class tree{
public:

    // Constructor. Crea un arbol vacio
    tree(){
        root = new node<T>();
    };
    
    void f_forma(node<T>* x){
        if (x != nullptr) {
            f_forma(x->left);
            if (x != root){    // ---------------------------------------------
                if(x->left) cout << " : " << x->left->key << "  ";
                else{ cout << " : null ";}
                cout << " : " << x->key << " ";
                if(x->right) cout << " : " << x->right->key << "  ";
                else{ cout << " : null ";}
            }
            cout << endl;
            f_forma(x->right);
        }
    }

    // Destructor (borra el arbol)
    ~tree(){
        node<T>* victim = root;
        while(victim != nullptr) {
            // cout << "victim: " << victim->key << "\n"; // de prueba. Funciona
            victim = treeDelete(victim);
            delete victim;
            victim = root;
        }
    };
    
    // Efectua un recorrido en orden del sub�rbol cuya raiz es apuntada
    // por x, imprimiendo en cada visita la llave de cada nodo.
    void inorderTreeWalk(node<T>* x){
        if (x != nullptr) {
            inorderTreeWalk(x->left);
            if (x != root){
                cout << x->key << " ";
            }
            inorderTreeWalk(x->right);
        }
    };
    
    node<T>* f_treeSearch(node<T>* x, const T& k) {
        if (x == nullptr || k == x->key) {
            return x == root ? nullptr : x;
        }
        if (k < x->key) {
            return f_treeSearch(x->left,k);
        } else {
            return f_treeSearch(x->right,k);
        }
    }
    // Busca la llave recursivamente; si la encuentra, devuelve un
    // apuntador al nodo que la contiene, sino devuelve NULL
    node<T>* treeSearch(const T& k){
        return f_treeSearch(root, k);
    };
    
    // Lo mismo que en el anterior pero usando un procedimiento
    // iterativo
    node<T>* iterativeTreeSearch(const T& k){
        node<T>* x = root;
        while(x != nullptr && k != x->key){
            if (k < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return x  == root ? nullptr : x;
    };
    
    node<T>* f_treeMinimum(node<T>* x) {
        if (!root->left && x == root) {
            return f_treeMinimum(x->right); 
        } else {
            while (x->left != nullptr) {
                    x = x->left;
            }
        }
        return x;
    }

    // Devuelve el nodo que tiene la llave menor.
    // Si el arbol est� vacio devuelve NULL.
    node<T>* treeMinimum(){
        return f_treeMinimum(root);
    };
    
    node<T>* f_treeMaximum(node<T>* x) {
        while (x->right != nullptr) {
            x = x->right;
        }
        return x != nullptr ? x : NULL;
    }

    // Devuelve el nodo que tiene la llave mayor.
    // Si el arbol esta vacio devuelve NULL.
    node<T>* treeMaximum() {
        return f_treeMaximum(root);
    };
    
    // Devuelve el nodo cuya llave es la que le sigue a la
    // del nodo x. Si no existe tal nodo devuelve NULL.
    node<T>* treeSuccessor(const node<T>* x){
        if (x->right != nullptr) {
            return f_treeMinimum(x->right);
        }
        node<T>* y = x->p;
        while (y != nullptr && x == y->right){
            x = y;
            y = y->p;
        }
        return y;
    };
    
    // Inserta el nodo z en la posicion que le corresponde en el arbol.
    void treeInsert(node<T>* z){
        node<T>* y = nullptr;
        node<T>* x = root;
        while (x != nullptr){
            y = x;
            if (z->key < x->key){
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->p = y;
        if (y == nullptr){
            root = z; // tree was empty
        }
        else if (z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
    };
    
    // Saca del arbol la llave contenida en el nodo apuntado por z.
    // Devuelve la direccion del nodo eliminado para que se pueda
    // disponer de ella.
    node<T>* treeDelete(node<T>* z){
        node<T> * victim;
        if (z->left == nullptr) {
            victim = f_transplant(z,z->right);
        }
        else if (z->right == nullptr) {
            victim = f_transplant(z, z->left);
        }
        else {
            node<T>* y = f_treeMinimum(z->right);
            if (y->p != z){
                victim = f_transplant(y,y->right);
                y->right = z->right;
                y->right->p = y;
            }
           victim = f_transplant(z,y);
            y->left = z->left;
            y->left->p = y;
        }
        return victim;
    };

    // mueve un subarbol dentro del árbol:
    // el padre del nodo u se convierte en el padre del nodo v.
    node<T>* f_transplant(node<T>* u, node<T>* v) {
        if (u->p == nullptr) { // cambia la raiz por v (u es la raiz)
            root = v;
        }
        else if (u == u->p->left) { // cambia a u por v (izq de padre)
            u->p->left = v;
        }
        else { // cambia a u por v (der de padre)
            u->p->right = v;
        }
        if (v != nullptr) { // v no es la raíz 
            v->p = u->p; // padre de v es padre de u
        }
        return u;
    }
    
    // Devuelve la raiz del arbol. (Para efectos de revisi�n de la tarea).
    node<T> * getRoot() const{
        return this->root;
    };

    // 2.1.2) metodo del paso 3.
    // llena el arbol con 1M de nums secuenciales
    void f_fillTree_sec(int qtyNodos){
        // tome el hijo derecho del nodo maximo (derecha)
        // asignele el nuevo valor
        node<int>* current = root; // inicia con la raiz
        for (int i = 0; i < qtyNodos; ++i) { // llena con 1M de valores consecutivos
            // if (i % 100000 == 0) {cout << i << " ";} // para ver avance (prueba)
            current->right = new node<int>(i);
            current = current->right;
        }
    }
private:
    node<T> *root;    // root of the Tree

    
};
#endif    // BINARY_SEARCH_Tree

// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr
