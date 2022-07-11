// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr

#ifndef LINKED_LIST_llist
#define LINKED_LIST_llist
#include <iostream>

// Nodos de la lista:
template <typename T>
class llnode{
public:
    // Esta clase es para ser usada por otras clases.
    // Por eficiencia los atributos se dejan publicos.
    T key;
    llnode<T> *prev, *next;
    //enum colors color;
    
    // Constructor por omision.
    llnode () {
        key = 0; 
        prev = this;
        next = this;
    };
    
    // Inicializacion de los datos miembro.
    llnode (const T& k, llnode<T> *w = NULL, llnode<T> *y = NULL) : key(k), prev(w), next(y) {
    };
    
    ~llnode(){
    }
};

// Lista enlazada con nodo centinela:
template <typename T>
class llist{
public:
    // Constructor (crea una lista vacia)
    llist(){
        nil = new llnode<T>();
    };
    
    // Destructor (borra la lista)
    ~llist() {
        llnode<T> * actual = nil->next;
        llnode<T> * victim = nullptr;
        while (actual && actual != nil) {
            victim = actual;
            actual = actual->next;
            delete victim;
        }
        delete nil;
    };
    
    // Busca la llave iterativamente. Si la encuentra, devuelve un
    // apuntador al nodo que la contiene; sino devuelve NULL.
    llnode<T>* listSearch(const T& k){
        llnode<T> *actual = nil->next;
        while (actual->key != k && actual != nil){
           actual = actual->next;
        }
        return actual;
    };
    
    // Inserta el nodo x en la lista.
    void listInsert(llnode<T>* x) {
        x->next = nil->next;
        nil->next->prev = x;
        nil->next = x;
        x->prev = nil;
    };
    
    // Saca de la lista la llave contenida en el nodo apuntado por x.
    // Devuelve la direccion del nodo eliminado para que se pueda
    // disponer de el.
    llnode<T>* listDelete(llnode<T>* x){
        x->prev->next = x->next;
        x->next->prev = x->prev;
        return x;
    };
    
    // Devuelve el nodo centinela. (Para efectos de revision de la tarea).
    llnode<T> * getNil() const{
        return this->nil;
    };

    // método EXTRA - auxiliar para pruebas.
    void imprimirLista() {
        llnode<T> *actual = nil->next;
        while(&(*actual) != &(*nil)) {
            std::cout << actual->key << " ";
            actual = actual->next;
        }
        std::cout << std::endl;
    }

private:
    llnode<T> *nil;        // nodo centinela
};

#endif    // LINKED_LIST_llist

// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr
