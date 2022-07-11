#include <vector>
#include <iostream>
#include <chrono>
#include <stack>
#include <algorithm>
#include <random>
#include "llist.h"
#include "bstree.h"
#include "rbtree.h"
#include "hasht.h"

// 1 para habilitar : 0 para deshabilitar prueba
#define testlist 0
#define testbtree 0
#define testredblack 1
#define testhash 1

using namespace std;

int generateRandomNumber(int min, int max) 
{
	random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution <int> dist(min, max - 1);
	return dist(generator);
}

void list_test(vector <string> &puntos)
{
	cout << "\nTest #1: Lista generada aleatoria" << endl;

	llnode<int> *paraBorrar = nullptr;

	try
	{
		llist<int> *l3 = new llist<int>;
		puntos.push_back("Constructor (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Constructor (0)");
		std::cerr << e.what() << '\n';
	}

	int elements_q = 1000000, searched_elements = 0;

	cout << "Insertando elementos en la lista..." << endl;

	llist<int> *l1 = new llist<int>;
	try
	{
		for (int i = 0; i < elements_q; i++)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			llnode<int> *node = new llnode<int>(random);
			l1->listInsert(node);
		}
		puntos.push_back("Insercion (4)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Insercion (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Elementos insertados!" << endl
		 << "Buscando elementos aleatorios..." << endl;

	try
	{
		auto time_start1 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			llnode<int> *search_for = l1->listSearch(random);
			searched_elements++;
			if (chrono::steady_clock::now() - time_start1 > chrono::seconds(10))
			{
				paraBorrar = search_for;
				break;
			}
		}
		puntos.push_back("Busqueda (3)");
		puntos.push_back("Prueba 1 (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Busqueda (0)");
		puntos.push_back("Prueba 1 (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Se lograron realizar " << searched_elements << " busquedas!" << endl;




	cout << "\nTest #2: Lista secuencial" << endl;

	llist<int> l2;
	searched_elements = 0;

	cout << "Insertando elementos en la lista..." << endl;

	for (int i = 0; i < elements_q; i++)
	{
		llnode<int> *node = new llnode<int>(i);
		l2.listInsert(node);
	}

	cout << "Elementos insertados!" << endl
		 << "Buscando elementos..." << endl;

	try
	{
		auto time_start2 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			llnode<int> *search_for = l2.listSearch(random);
			searched_elements++;
			if (chrono::steady_clock::now() - time_start2 > chrono::seconds(10))
			{
				break;
			}
		}
		puntos.push_back("Prueba 2 (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Prueba 2 (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;
  

	try
	{
		if (paraBorrar){
			cout << "paraBorrar:" << paraBorrar->key << endl;
			llnode<int> *borrado = l1->listDelete(paraBorrar);
		} else {
			cout << "no se encontro el elemento para borrar" << endl;
		}
		puntos.push_back("Borrado (4)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Borrado (0)");
		std::cerr << e.what() << '\n';
	}

	try
	{
		delete l1;
		cout << "Destructor de Lista exitoso" << endl;
		puntos.push_back("Destructor (3)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Destructor (0)");
		std::cerr << e.what() << '\n';
	}

	cout << endl;

	iter_swap(puntos.begin() + 1, puntos.begin() + 6);
	iter_swap(puntos.begin() + 2, puntos.begin() + 6);
	iter_swap(puntos.begin() + 3, puntos.begin() + 6);
	iter_swap(puntos.begin() + 4, puntos.begin() + 5);
	iter_swap(puntos.begin() + 5, puntos.begin() + 6);

	if (puntos.size() == 7)
	{
		puntos.push_back("Informe (3)");
	}
	else
	{
		puntos.push_back("Informe (0)");
	}

	cout << endl
		 << endl;
}

void btree_test(vector <string> &puntos)
{
	try
	{
		tree<int> *tp = new tree <int>;
		puntos.push_back("Constructor (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Constructor (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Test #1: Arbol generado aleatoriamente" << endl;

	tree<int> *t1 = new tree<int>;
	int elements_q = 10, searched_elements = 0, t = 0;

	cout << "Insertando elementos en el arbol..." << endl;

	try
	{
		for (int i = 0; i < elements_q; i++)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			node<int> *n = new node<int>(random);
			t1->treeInsert(n);
		}
		puntos.push_back("Insercion (4)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Insercion (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Elementos insertados!" << endl
		 << "Buscando elementos aleatorios..." << endl;

	try
	{
		auto time_start1 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			node<int> *search_for = t1->iterativeTreeSearch(random);
			searched_elements++;
			if (search_for != NULL)
			{
				t = search_for->key;
			}
			if (chrono::steady_clock::now() - time_start1 > chrono::seconds(10))
			{
				break;
			}
		}
		puntos.push_back("Busqueda iterativa (5)");
		puntos.push_back("Prueba 1 (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Busqueda iterativa (0)");
		puntos.push_back("Prueba 1 (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;

	try
	{
		cout << "Elementos del arbol de menor a mayor: " << endl;
		t1->inorderTreeWalk(t1->getRoot());
		puntos.push_back("Recorrido (3)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Recorrido (0)");
		std::cerr << e.what() << '\n';
	}

	cout << endl;

	try
	{
		node<int> *e = t1->iterativeTreeSearch(t);
		node<int> *s = t1->treeDelete(e);

		cout << ((e == NULL) ? "No encontrado" : "Encontrado") << endl;
		cout << ((s == NULL) ? "No borrado" : "Borrado") << endl;

		/*node<int> *es = t1->iterativeTreeSearch(t);
		node<int> *ss = t1->treeDelete(es);

		cout << ((es == NULL) ? "No encontrado" : "Encontrado") << endl;
		cout << ((ss == NULL) ? "No borrado" : "Borrado") << endl;*/

		puntos.push_back("Borrado (5)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Borrado (5)");
		std::cerr << e.what() << '\n';
	}



	cout << "\nTest #2: Arbol secuencial" << endl;

	tree <int> *t2 = new tree <int>;
	node <int> *b = nullptr;
	int a = 0;
	searched_elements = 0;

	cout << "Insertando elementos en el arbol..." << endl;

	for (int i = 0; i < elements_q; i++)
	{
		node<int> *n = new node<int>(i);
		t2->treeInsert(n);
	}

	cout << "Elementos insertados!" << endl
		 << "Buscando elementos..." << endl;

	try
	{
		auto time_start2 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			node<int> *search_for2 = t2->iterativeTreeSearch(random);
			searched_elements++;
			if (search_for2 != NULL)
			{
				a = search_for2->key;
				b = search_for2;
			}
			if (chrono::steady_clock::now() - time_start2 > chrono::seconds(10))
			{
				break;
			}
		}
		puntos.push_back("Prueba 2 (1)");
	}
	catch(const std::exception& e)
	{
		puntos.push_back("Prueba 2 (0)");
		std::cerr << e.what() << '\n';
	}
	
	cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;

	cout << "Elementos del arbol de menor a mayor: " << endl;
	t2->inorderTreeWalk(t2->getRoot());

	cout << endl;
	
	try
	{	

		node<int> *e2 = t2->iterativeTreeSearch(a);
	  if (e2){
			node<int> *s2 = t2->treeDelete(e2);
			cout << ((e2 == NULL) ? "No encontrado" : "Encontrado") << endl;
			cout << ((s2 == NULL) ? "No borrado" : "Borrado") << endl;
		}


		/*node<int> *es2 = t2->iterativeTreeSearch(a);
		node<int> *ss2 = t2->treeDelete(es2);

		cout << ((es2 == NULL) ? "No encontrado" : "Encontrado") << endl;
		cout << ((ss2 == NULL) ? "No borrado" : "Borrado") << endl;*/
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	try
	{

		node <int> *min = t1->treeMinimum();

		cout << "Minimo de t1 es:" << min->key << endl; 
		puntos.push_back("Busqueda minimo (1)");
	}
	catch(const std::exception& e)
	{
		puntos.push_back("Busqueda minimo (0)");
		std::cerr << e.what() << '\n';
	}

	try
	{
		node <int> *max = t1->treeMaximum();
		cout << "Maximo de t1 es:" << max->key << endl; 
		puntos.push_back("Busqueda maximo (1)");
	}
	catch(const std::exception& e)
	{
		puntos.push_back("Busqueda maximo (0)");
		std::cerr << e.what() << '\n';
	}

	try
	{
		if (b){
		node <int> *su1 = t1->treeSuccessor(b);
		cout << "El sucesor de " << b->key << " es: " << su1->key << endl; 
		} else {
			cout << "no se inicializo 'b'" << endl;
		}
		puntos.push_back("Sucesor (2)");
	}
	catch(const std::exception& e)
	{
		puntos.push_back("Sucesor (0)");
		std::cerr << e.what() << '\n';
	}

	try
	{
		delete t1;
		puntos.push_back("Destructor (3)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Destructor (0)");
		std::cerr << e.what() << '\n';
	}

	cout << endl;

	//iter_swap(puntos.begin() + , puntos.begin() + );
	iter_swap(puntos.begin() + 1, puntos.begin() + 10);
	iter_swap(puntos.begin() + 2, puntos.begin() + 10);
	iter_swap(puntos.begin() + 3, puntos.begin() + 5);
	iter_swap(puntos.begin() + 4, puntos.begin() + 10);
	iter_swap(puntos.begin() + 5, puntos.begin() + 8);
	iter_swap(puntos.begin() + 6, puntos.begin() + 7);
	iter_swap(puntos.begin() + 7, puntos.begin() + 9);
	iter_swap(puntos.begin() + 8, puntos.begin() + 10);
	iter_swap(puntos.begin() + 9, puntos.begin() + 10);

	if (puntos.size() == 11)
	{
		puntos.push_back("Informe (1)");
		puntos.push_back("Informe (2)");
	}
	else
	{
		puntos.push_back("Informe (0)");
		puntos.push_back("Informe (0)");
	}
	
	cout << endl
		 << endl;
}

void rb_tree_test(vector <string> &puntos)
{
	rbtree <int> *rb;
	
	try
	{
		rb = new rbtree<int>;
		cout << "Constructor (1)" << endl;
		puntos.push_back("Constructor (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Constructor (0)");
		std::cerr << e.what() << '\n';
	}
	
	try
	{
		delete rb;
		puntos.push_back("Destructor (3)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Destructor (0)");
		std::cerr << e.what() << '\n';
	}

	rbtree <int> *t1 = new rbtree<int>();
	rbtree <int> *t2 = new rbtree<int>();
	int elements_q = 100, searched_elements = 0, t = 0;

	cout << "Insertando elementos en el arbol..." << endl;

	try
	{
		for (int i = 0; i < elements_q; i++)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			rbnode <int> *n = new rbnode<int>(random);
			t1->treeInsert(n);
			t2->treeInsert(new rbnode<int>(i));
			t = random;
		}
		cout << "---------------------------------------" << endl;
		t2->inorderTreeWalk(t2->getRoot());
		cout << endl << "---------------------------------------" << endl;
		cout << "Insercion" << endl;
		puntos.push_back("Insercion (4)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Insercion (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Elementos insertados!" << endl; 
	
	try
	{
		rbnode<int> *e = t1->iterativeTreeSearch(t);
		//rbnode<int> *s = t1->treeDelete(e);

		cout << ((e == NULL) ? "No encontrado" : "Encontrado") << endl;
		//cout << ((s == NULL) ? "No borrado" : "Borrado") << endl;

		puntos.push_back("Borrado (5)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Borrado (5)");
		std::cerr << e.what() << '\n';
	}
	
	cout << "Test #1: RB tree aleatorio" << endl << "Buscando elementos aleatorios..." << endl;
	
	try
	{
		auto time_start1 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			rbnode <int> *search_for = t1->iterativeTreeSearch(random);
			searched_elements++;
			if (chrono::steady_clock::now() - time_start1 > chrono::seconds(10))
			{
				break;
			}
		}
		puntos.push_back("Busqueda (5)");
		puntos.push_back("Prueba 1 (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Busqueda (0)");
		puntos.push_back("Prueba 1 (0)");
		std::cerr << e.what() << '\n';
	}
	
	cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;
	
	cout << "\nTest #2: RB tree secuencial" << endl << "Buscando elementos aleatorios..." << endl;
	
	searched_elements = 0;
	
	try
	{
		auto time_start1 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			rbnode <int> *search_for = t2->iterativeTreeSearch(random);
			searched_elements++;
			if (chrono::steady_clock::now() - time_start1 > chrono::seconds(10))
			{
				break;
			}
		}
		puntos.push_back("Prueba 2 (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Prueba 2 (0)");
		std::cerr << e.what() << '\n';
	}
	
	cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;
	
	try
	{
		rbnode <int> *max = t2->treeMaximum();
		cout << "Maximo de t1 es:" << max->key << endl; 
		puntos.push_back("Busqueda maximo (1)");
	}
	catch(const std::exception& e)
	{
		puntos.push_back("Busqueda maximo (0)");
		std::cerr << e.what() << '\n';
	}
	
	try
	{
		rbnode <int> *min = t2->treeMinimum();
		cout << "Minimo de t1 es:" << min->key << endl; 
		puntos.push_back("Busqueda minimo (1)");
	}
	catch(const std::exception& e)
	{
		puntos.push_back("Busqueda minimo (0)");
		std::cerr << e.what() << '\n';
	}
	
	try
	{
		rbnode<int>* su1 = t2->treeSuccessor(t2->getRoot());
		cout << "El sucesor de " << t2->getRoot()->key << " es: " << su1->key << endl; 
		puntos.push_back("Sucesor (2)");
	}
	catch(const std::exception& e)
	{
		puntos.push_back("Sucesor (0)");
		std::cerr << e.what() << '\n';
	}

	try
	{
		cout << "Elementos del arbol de mayor a menor: " << endl;
		t2->inorderTreeWalk(t2->getRoot());
		puntos.push_back("Recorrido (3)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Recorrido (0)");
		std::cerr << e.what() << '\n';
	}
	
	if (puntos.size() == 11)
	{
		puntos.push_back("Informe (1)");
		puntos.push_back("Informe (2)");
	}
	else
	{
		puntos.push_back("Informe (0)");
		puntos.push_back("Informe (0)");
	}
	
    cout << endl << endl;
}


void hash_test(vector <string> &puntos)
{
	int elements_q = 100000, searched_elements = 0, t = 0;
	hasht <int>* tabla1 = new hasht<int>(elements_q);
	hasht <int>* tabla2 = new hasht<int>(elements_q);
	hasht <int>* tabla_t = new hasht<int>(elements_q);
	
	try
	{
		// tabla_t = rb = new hasht<int>(elements_q);
		puntos.push_back("Constructor (3)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Constructor (0)");
		std::cerr << e.what() << '\n';
	}
	
	try
	{
		delete tabla_t;
		puntos.push_back("Destructor (3)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Destructor (0)");
		std::cerr << e.what() << '\n';
	}	

	try
	{
		for (int i = 0; i < elements_q; i++)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			tabla1->insert(random);
			tabla2->insert(random);
		}
		puntos.push_back("Insercion (4)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Insercion (0)");
		std::cerr << e.what() << '\n';
	}	

	cout << "Insertando elementos..." << endl;

	cout << "Test #1: Tabla aleatoria" << endl << "Buscando elementos aleatorios..." << endl;

	try
	{
		auto time_start1 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			auto it = tabla1->search(random);
			searched_elements++;
			if (chrono::steady_clock::now() - time_start1 > chrono::seconds(10))
			{
				cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;
				break;
			}
		}
		puntos.push_back("Busqueda (4)");
		puntos.push_back("Prueba 1 (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Busqueda (0)");
		puntos.push_back("Prueba 1 (0)");
		std::cerr << e.what() << '\n';
	}
	
	cout << "Test #2: Tabla secuencial" << endl << "Buscando elementos..." << endl;
	
	try
	{
		auto time_start1 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			auto it = tabla2->search(random);
			searched_elements++;
			if (chrono::steady_clock::now() - time_start1 > chrono::seconds(10))
			{
				cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;
				break;
			}
		}
		puntos.push_back("Prueba 2 (1)");
	}
	catch (const std::exception &e)
	{
		puntos.push_back("Prueba 2 (0)");
		std::cerr << e.what() << '\n';
	}
	
	if (puntos.size() == 6)
	{
		puntos.push_back("Informe (2)");
		puntos.push_back("Informe (2)");
	}
	else
	{
		puntos.push_back("Informe (0)");
		puntos.push_back("Informe (0)");
	}

}

//Program main

int main()
{
	vector <string> puntosA, puntosB, puntosC, puntosD;
	if (testlist == 1) list_test(puntosA);
	if (testbtree == 1) btree_test(puntosB);
	if (testredblack == 1) rb_tree_test(puntosC);
	if (testhash == 1) hash_test(puntosD);
	
	for (size_t i = 0; i < puntosA.size(); i++)
	{
		cout << puntosA[i] << endl;
	}

	cout << endl << endl;

	for (size_t i = 0; i < puntosB.size(); i++)
	{
		cout << puntosB[i] << endl;
	}

	cout << endl << endl;
	
	for (size_t i = 0; i < puntosC.size(); i++)
	{
		cout << puntosC[i] << endl;
	}

	cout << endl << endl;
	
	for (size_t i = 0; i < puntosD.size(); i++)
	{
		cout << puntosD[i] << endl;
	}

	cout << endl;
	return 0;
}