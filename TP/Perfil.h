#pragma once
#include "Caracteristica.h"
#include <vector>
using namespace std;

class Configuracao;
class Caracteristica;

class Perfil {
	vector<Caracteristica *> VecC;
	char letra;
	int tataque, tdefesa, saude;
public:
	Perfil(char letra);

	~Perfil();

	void addCar(int id, Configuracao * conf);

	void addCar(Caracteristica * c);

	void removeCar(int id);

	int getNumCar();

	Caracteristica * getCaracteristica(int i);

	int getCustoForcaT();

	int getCustoT();

	char getLetra();

	string toString();

	int getTamVecC();

	bool ExistCar(int id);
};
