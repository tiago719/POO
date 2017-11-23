#include "stdafx.h"
#include "Perfil.h"

Perfil::Perfil(char letra): letra(letra), tataque(0), tdefesa(0), saude(0) {}

Perfil::~Perfil()
{

}

void Perfil::addCar(int id, Configuracao * conf) 
{
	VecC.push_back(conf->getCar(id));
	tataque += conf->getCar(id)->getAtaque();
	tdefesa += conf->getCar(id)->getDefesa();
	saude += conf->getCar(id)->getSaude();
}

void Perfil::addCar(Caracteristica * c)
{
	VecC.push_back(c);
}

void Perfil::removeCar(int id)
{
	for (int i = 0; i < VecC.size(); i++)
	{
		if (VecC[i]->getId() == id)
		{
			VecC.erase(VecC.begin() + i);
			break;
		}
	}
}

int Perfil::getNumCar()
{
	return static_cast<int>(VecC.size());
}

Caracteristica * Perfil::getCaracteristica(int i)
{
	return VecC[i];
}

int Perfil::getCustoForcaT() {
	int total = 0;
	for (int i = 0; i < VecC.size(); i++) {
		total += VecC[i]->getCusto_forca();
	}
	return total;
}

int Perfil::getCustoT()
{
	int total=0;

	for (int i = 0; i < VecC.size(); i++)
	{
		total += VecC[i]->getCusto_moedas();
	}

	return total;
}

char Perfil::getLetra()
{
	return letra;
}

string Perfil::toString()
{
	ostringstream os;

	cout << "Perfil: " << letra << endl;
	cout << "Lista de carateristicas: " << endl;

	for (int i = 0; i < VecC.size(); i++)
	{
		cout << VecC[i]->getNome() << endl;;
	}

	cout << "Ataque do Perfil: " << tataque << "\tDefesa do Perfil: " << tdefesa << "\tSaude adicional do Perfil: " << saude << endl;

	return os.str();
}

int Perfil::getTamVecC()
{
	return static_cast<int>(VecC.size());
}

bool Perfil::ExistCar(int id)
{
	for (int i = 0; i < VecC.size(); i++)
	{
		if (VecC[i]->getId() == id)
		{
			return true;
		}
	}

	return false;
}

