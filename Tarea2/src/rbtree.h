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
		};
			
		// Destructor (borra el arbol)
		~rbtree(){
		};
		
        // Efectua un recorrido en orden del sub‡rbol cuya raiz es apuntada
        // por x, imprimiendo en cada visita la llave de cada nodo.
		void inorderTreeWalk(rbnode<T>* x){
		};
            
		// Busca la llave recursivamente, si la encuentra devuelve un 
        // puntero al nodo que la contiene, sino devuelve NULL.
		rbnode<T>* treeSearch(const T& k){
		};
			
		// Igual que en el anterior pero usa un procedimiento iterativo.
		rbnode<T>* iterativeTreeSearch(const T& k){
		};
			
		// Devuelve el nodo con la llave menor.
        // Si el arbol esta vacio devuelve NULL.	
		rbnode<T>* treeMinimum(){
		};
			
		// Devuelve el nodo con la llave mayor.
        // Si el arbol esta vacio devuelve NULL.
		rbnode<T>* treeMaximum(){
		};
			
		// Devuelve el nodo cuya llave es la siguiente mas grande que 
        // la del nodo x. Si no existe tal nodo devuelve NULL.
		rbnode<T>* treeSuccessor(const rbnode<T>* x){
		};
			
		// Inserta el nodo z en la posicion que le corresponde en el arbol.
		void treeInsert(rbnode<T>* z){ //aux es y, actual es x.
		};
			
		// Saca del arbol la llave contenida en el nodo apuntado por z.
		// Devuelve la direccion del nodo eliminado para que se pueda 
		// disponer de el.	
		rbnode<T>* treeDelete(rbnode<T>* z){
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
	
		rbnode<T> *root;	// raiz del arbol
		rbnode<T> *nil;	    // nodo nil (hoja) del arbol

};

#endif	// RED_BLACK_rbtree
