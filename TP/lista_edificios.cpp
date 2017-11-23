#include "stdafx.h"
#include "lista_edificios.h"

string lista_edificios::mostrarLista() const {
	ostringstream os;
	for (int i = 0; i < ed.size(); i++) {
		os << ed[i].toString();
	}
	return os.str();
}
string lista_edificios::toString() const
{
	ostringstream os;
	os << "id: " << id << " nome: " << nome << " custo: "
		<< custo << " saude: " << saude	<< " defesa: " << defesa << endl;
	return os.str();
}
