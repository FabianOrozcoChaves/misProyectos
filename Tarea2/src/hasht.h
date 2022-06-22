#ifndef HASH_CLASS
#define HASH_CLASS
#include <list>
#include <vector>

using namespace std;

template <typename T>

class hasht{
	public:
		// Constructor que especifica el numero de cubetas (entradas) 
		// en la tabla
		hasht(int nEntradas){
		};
			
		// Destructor (borra la tabla)
		~hasht(){
		};
			
		// Retorna un puntero a la llave o NULL si no se encuentra
		T* search(const T& item){
		};
			
		// Inserta el elemento en la tabla
		void insert(const T& item){
		};
			

	private:
		// Nœmero de entradas en la tabla
		int numEntradas;

		// La tabla es un vector de listas de STL
		vector<list<T> > tabla;
};
#endif
