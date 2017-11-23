#pragma once
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class lista_edificios {
	string nome;
	//string descricao;//talvez usar isto
	int custo, saude, defesa, id;
	vector<lista_edificios> ed;

public:
	lista_edificios(int id, string nome, int custo, int saude, int defesa)
		:id(id), nome(nome), custo(custo), saude(saude),
		defesa(defesa) {}
	lista_edificios() {
		ed.push_back(lista_edificios(1, "castelo", 0, 50, 10));
		ed.push_back(lista_edificios(2, "torre", 30, 20, 10));
		ed.push_back(lista_edificios(3, "quinta", 20, 20, 10));
	}
	~lista_edificios() {}
	string mostrarLista() const;
	string toString() const;
};

