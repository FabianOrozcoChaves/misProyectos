// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr

#ifndef RED_BLACK_rbtree
#define RED_BLACK_rbtree

using namespace std;

enum colors {RED, BLACK};

// Nodos del arbol:
template <typename T>
class rbnode{
   public:
		// Esta clase es para ser usada por otras clases.
		// Por eficiencia se hacen los atributos publicos.
		T key;
		rbnode<T> *p, *left, *right;
		enum colors color;

		// Constructor por omision.
		rbnode(){
			p = left = right = nullptr;
			color = BLACK;
		};
		
      	//Inicializacion de datos miembro.
		rbnode (const T& k, rbnode<T> *w = NULL, rbnode<T> *y = NULL, 
				 rbnode<T> *z = NULL, enum colors c = RED):
					key(k), p(w), left(y), right(z), color(c)
		{};
		
		~rbnode(){
		}
};

// Arbol:
template <typename T>
class rbtree{
	public:

		// Constructor (crea un arbol vacio)
		rbtree(){
			nil = new rbnode<T>();
			root = nil;
		};
			
		// Destructor (borra el arbol)
		~rbtree(){
			liberar(root);
		};

		void liberar(rbnode<T>* x) {
			if (x != nullptr && x != nil) {
				liberar(x->left);
				liberar(x->right);
				delete x;
			}
		};

		// Efectua un recorrido en orden del sub�rbol cuya raiz es apuntada
		// por x, imprimiendo en cada visita la llave de cada nodo.
		void inorderTreeWalk(rbnode<T>* x){
			if (x != nil) {
				inorderTreeWalk(x->left);
						cout << x->key << " ";
				inorderTreeWalk(x->right);
			}
		};

		rbnode<T>* f_treeSearch(rbnode<T>* x, const T& k) {
			if (x == nullptr || k == x->key) {
					return x == root ? nullptr : x;
			}
			if (k < x->key) {
					return f_treeSearch(x->left,k);
			} else {
					return f_treeSearch(x->right,k);
			}
		};
		// Busca la llave recursivamente, si la encuentra devuelve un 
				// puntero al nodo que la contiene, sino devuelve NULL.
		rbnode<T>* treeSearch(const T& k){
			return f_treeSearch(root, k);
		};
			
		// Igual que en el anterior pero usa un procedimiento iterativo.
		rbnode<T>* iterativeTreeSearch(const T& k){
			rbnode<T>* x = root;
			while(x != nullptr && k != x->key){
					if (k < x->key) {
							x = x->left;
					} else {
							x = x->right;
					}
			}
			return x  == root ? nullptr : x;
		};

		rbnode<T>* f_treeMaximum(rbnode<T>* x) {
			while (x->right != nullptr && x->right != nil) {
					x = x->right;
			}
			return x;
		}

		// Devuelve el nodo con la llave mayor.
		// Si el arbol esta vacio devuelve NULL.
		rbnode<T>* treeMaximum(){
			return f_treeMaximum(root);
		};

		rbnode<T>* f_treeMinimum(rbnode<T>* x) {
			while (x->left != nullptr && x->left != nil) {
				x = x->left;
			}
			return x;
		}

		// Devuelve el nodo con la llave menor.
				// Si el arbol esta vacio devuelve NULL.	
		rbnode<T>* treeMinimum(){
			return f_treeMinimum(root);
		};

		// Devuelve el nodo cuya llave es la siguiente mas grande que 
				// la del nodo x. Si no existe tal nodo devuelve NULL.
		rbnode<T>* treeSuccessor(const rbnode<T>* x){
			if (x->right != nullptr) {
					return f_treeMinimum(x->right);
			}
			rbnode<T>* y = x->p;
			while (y != nullptr && x == y->right){
					x = y;
					y = y->p;
			}
			return y;
		};
			
		// Inserta el nodo z en la posicion que le corresponde en el arbol.
		void treeInsert(rbnode<T>* z){ //aux es y, actual es x.
			// cout << "entra a insertar" << endl;
			rbnode<T> * y = nil;
			rbnode<T> * x = root;

			while (x != nil) {
				// cout << "while: x != nil" << endl;
				y = x;
				if (z->key < x->key) {
					x = x->left;
				} else {
					x = x->right;
				}
			}
			z->p = y;
			if (y == nil) {
				root = z;
			}
			else if(z->key < y->key) {
				y->left = z;
			} else {
				y->right = z;
			}
			z->left = nil;
			z->right = nil;
			z->color = RED;
			// cout << "antes de llamar a fixup" << endl;

			insert_fixup(z);
		};

		// Saca del arbol la llave contenida en el nodo apuntado por z.
		// Devuelve la direccion del nodo eliminado para que se pueda 
		// disponer de el.	
		rbnode<T>* treeDelete(rbnode<T>* z){
			// NO SE REALIZA SEGUN ENUNCIADO.
		};

			
		// Devuelve la raiz del arbol. (Para efectos de revision de la tarea).
		rbnode<T> * getRoot() const{
			return this->root;
		};

		// Devuelve T.nil. (Para efectos de revision de la tarea).
		rbnode<T> * getNil() const{
			return this->nil;
		};

		private:

		void insert_fixup(rbnode<T>* z) {
			rbnode<T>* y;
			while(z->p->color == RED) {
				if (z->p == z->p->p->left) {
					y = z->p->p->right;
					if (y->color == RED) {
						z->p->color = BLACK; 
						y->color = BLACK; 	
						z->p->p->color = RED; 
						z = z->p->p; 	
					} else if (z == z->p->right) {
						z = z->p;
						left_rotate(z);
					} else {
						z->p->color = BLACK;
						z->p->p->color = RED;
						right_rotate(z->p->p);
					}
				} else {
					y = z->p->p->left;
					if (y->color == RED) {
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					} else if (z == z->p->left) {
						z = z->p;
						right_rotate(z);
					}
					else {
						z->p->color = BLACK;
						z->p->p->color = RED;
						left_rotate(z->p->p);
					}
				}
			}
			this->root->color = BLACK;
		};

		void left_rotate(rbnode<T>* x) {
			rbnode<T>* y = x->right;
			x->right = y->left;
			if (y->left != nil) {
				y->left->p = x;
			}
			y->p = x->p;
			if (x->p == nil) {
				root = y;
			}
			else if (x == x->p->left) {
				x->p->left = y;
			}
			else { x->p->right = y;}
			y->left = x;
			x->p = y;
		}

		void right_rotate(rbnode<T>* x) {
			rbnode<T>* y = x->left;
			x->left = y->right;
			if (y->right != nil) {
				y->right->p = x;
			}
			y->p = x->p;
			if (x->p == nil) {
				root = y;
			}
			else if (x == x->p->right) {
				x->p->right = y;
			}
			else { x->p->left = y;}
			y->right = x;
			x->p = y;
		}

		rbnode<T> *root;	// raiz del arbol
		rbnode<T> *nil;	    // nodo nil (hoja) del arbol

};

#endif	// RED_BLACK_rbtree

// Copyright 2021 Fabian Orozco Chaves B95690 fabian.orozcochaves@ucr.ac.cr
