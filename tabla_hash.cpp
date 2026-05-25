#include <iostream>
#include <list>
#include <stdexcept>

class TablaHash {

	private:
		int tamano;
		std::list<int>* tabla;

		int hash(int valor) {
			return std::abs(valor)%tamano;

		}

		float indice_llenado() {
			int ocupados = 0;
			for (int i = 0; i < tamano; i++){
				if (!tabla[i].empty())
					ocupados++;
			}
			return (float)ocupados/tamano;

		}

		bool rehash() {
			int nuevoTamano = tamano * 2;
			std::list<int>* nuevaTabla = new std::list<int>[nuevoTamano];

			for (int i = 0; i < tamano; i++) {
				for (int i = 0; i < tamano; i++) {
					for (int val : tabla[i]) {
						int nuevaPos = std::abs(val) % nuevoTamano;
						nuevaTabla[nuevaPos].push_back(val);
					}
		
				}

			}
			delete[] tabla;
			tabla = nuevaTabla;
			tamano = nuevoTamano;
			return true;
		}

	public:

		TablaHash(int tamano) {
			if (tamano <= 0)
				throw std::invalid_argument("El tamano debe ser positivo");
			this -> tamano = tamano;
			tabla = new std::list<int>[tamano];


		}

		~TablaHash() {
			delete[] tabla;
		}
	
		bool insertar(int valor){
			//Hace rehash si el indice de llenado es mayor al 70%
			if (indice_llenado() >= 0.7f) {
				rehash();
			} 

			int pos = hash(valor);
			for (int val : tabla[pos]) {
				if (val == valor)
					return false; 
			}
			tabla[pos].push_back(valor);
			return true;
		}

		bool eliminar(int valor) {
			int pos = hash(valor);
			auto& lista = tabla[pos];
			for (auto it = lista.begin(); it != lista.end(); ++it) {
				if (*it == valor) {
					lista.erase(it);
					return true;

				}
			}
			return false;
			

		}

		bool buscar(int valor) {
			int pos = hash(valor);
			for (int val : tabla[pos]) {
				if (val == valor) 
					return true;
			}
			return false;

		}

		void imprimir() {
			for (int i = 0; i < tamano; i++) {
				std::cout << "[" << i << "]";
				for (int val : tabla[i]) {
					std::cout << val << "->";
				}
				std::cout << "NULL\n";
			}
		}
};

int main() {

	TablaHash th(5);

	th.insertar(10);
	th.insertar(25);
	th.insertar(3);
	th.insertar(15);
	th.insertar(7);

	std::cout << "Despues de insericones:\n";
	th.imprimir();

	std::cout << "\nBuscar 25:" << (th.buscar(25) ? "Encontrado" : "No encontrado") << "\n";
	std::cout << "Buscar 99: " << (th.buscar(99) ? "Encontrado" : "No encontrado") << "\n";

	th.eliminar(25);

	std::cout << "\nDespues de eliminar el 25:\n";
	th.imprimir();

	return 0;


}
