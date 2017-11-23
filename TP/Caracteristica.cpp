#include "stdafx.h"
#include "Caracteristica.h"

int Caracteristica::getId() const
{
	return id;
}

int Caracteristica::getCusto_moedas() const
{
	return custo_moedas;
}

void Bandeira::execCar(Ser * ser, Colonia * co, Configuracao * conf)
{
	ser->setFlagBandeira(1);
	ser->ligaSer(co);
}

int Bandeira::tipo_carateristica()
{
	return 1;
}

void Bandeira::setFlag(int f)
{

}

Caracteristica * Bandeira::novacar()
{
	return nullptr;
}

int Bandeira::getFlag()
{
	return false;
}


void Superior::execCar(Ser * ser, Colonia * co, Configuracao * conf)
{
	ser->addVida_max(1);
}

int Superior::tipo_carateristica()
{
	return 1;
}

Caracteristica * Superior::novacar()
{
	return nullptr;
}

int Superior::getFlag()
{
	return false;
}

void Superior::setFlag(int f)
{

}

void PeleDura::execCar(Ser * ser, Colonia * co, Configuracao * conf)
{
	ser->addDefesa(1);
}
int PeleDura::tipo_carateristica()
{
	return 1;
}

Caracteristica * PeleDura::novacar()
{
	return nullptr;
}

int PeleDura::getFlag()
{
	return false;
}

void PeleDura::setFlag(int f)
{

}

void Armadura::execCar(Ser * ser, Colonia * co, Configuracao * conf)
{
	ser->addDefesa(2);
}
int Armadura::tipo_carateristica()
{
	return 1;
}

Caracteristica * Armadura::novacar()
{
	return nullptr;
}

int Armadura::getFlag()
{
	return false;
}
void Armadura::setFlag(int f)
{

}

void Faca::execCar(Ser * ser, Colonia * co, Configuracao * conf)
{
	ser->addAtaque(1);
}
int Faca::tipo_carateristica()
{
	return 1;
}

Caracteristica * Faca::novacar()
{
	return nullptr;
}

int Faca::getFlag()
{
	return false;
}

void Faca::setFlag(int f)
{

}

void Espada::execCar(Ser * ser, Colonia * co, Configuracao * conf)
{
	if (cont > 0)
	{
		ser->setAtaque(2);
	}
}
int Espada::tipo_carateristica()
{
	return 2;
}

Caracteristica * Espada::novacar()
{
	return new Espada();
}

int Espada::getFlag()
{
	if(cont>0){
		return true;
		cont--;
	}

	return false;
}

void Espada::setFlag(int f)
{

}

int Espada::getCont()
{
	return cont;
}

void Espada::setCont(int c)
{
	cont = c;
}

void Agressao::execCar(Ser * ser, Colonia * co, Configuracao * conf) {
	/*if (ser->getPerfil()->ExistCar(6) == true)
	{
		{
			for (int i = 0; i < ser->getPerfil()->getTamVecC(); i++)
			{
				if (ser->getPerfil()->getCaracteristica(i) == conf->getCar(6))
				{
					ser->addAtaque(3);
					f = 1;
				}
			}
		}
		ser->addAtaque(3);
	}*/


	Ser * s = conf->SerVizinho(co,ser->getCoorX(), ser->getCoorY(), 1);
	if (s != nullptr)
	{
		conf->ser_ser(ser, s);
	}
}
int Agressao::tipo_carateristica()
{
	return 2;
}

Caracteristica * Agressao::novacar()
{
	return new Agressao();
}

int Agressao::getFlag()
{
	return false;
}

void Agressao::setFlag(int f)
{

}


void Ecologico::execCar(Ser * ser, Colonia * co, Configuracao * conf) {
	Edificio * s = conf->EdificioVizinho(ser,ser->getCoorX(), ser->getCoorY());
	if (s != nullptr) {
		conf->ser_edif(ser, s);
	}
}
int Ecologico::tipo_carateristica()
{
	return 2;
}

Caracteristica * Ecologico::novacar()
{
	return new Ecologico();
}

int Ecologico::getFlag()
{
	return false;
}

void Ecologico::setFlag(int f)
{

}

HeatSeeker::HeatSeeker() : Caracteristica("HeatSeeker", 9, 1, 1, 0, 0, 0), inim(nullptr), count(0), dist_ant(-1) {}

void HeatSeeker::execCar(Ser * ser, Colonia * co, Configuracao * conf)
{
	if (inim == nullptr || count > 3){
		count = 0;
		int tam = conf->getTamVecC();
		Ser * in_best = nullptr;

		for (int i = 1; i <= tam; i++) {
			Colonia * c = conf->getColonia(i);
			int tam1 = c->getTamSer();
			int ini_perto=-1;
			for (int j = 0; j < tam1 && ser->getColonia() != c ; j++) {
				Ser * in = c->getSer(j);
				int dis = conf->calcula_dist(ser->getCoorX(), ser->getCoorY(), in->getCoorX(), in->getCoorY());

				if (dis < ini_perto || ini_perto == -1){
					ini_perto = dis;
					in_best = in;
				}
			}
		}
		inim = in_best;
	}
	else {
		int dist = conf->calcula_dist(ser->getCoorX(), ser->getCoorY(), inim->getCoorX(), inim->getCoorY());
		if (dist > dist_ant) {
			count++;
			dist_ant = dist;
		}
	}
	if (inim!=nullptr)
		conf->MoveSer(ser, inim->getCoorX(), inim->getCoorY());

}

int HeatSeeker::tipo_carateristica()
{
	return 3;
}

Caracteristica * HeatSeeker::novacar()
{
	return new HeatSeeker();
}

int HeatSeeker::getFlag()
{
	return false;
}

void HeatSeeker::setFlag(int f)
{

}

BuildSeeker::BuildSeeker() : Caracteristica("BuildSeeker", 10, 1, 1, 0, 0, 0), inim(nullptr) {}

void BuildSeeker::execCar(Ser * ser, Colonia * co, Configuracao * conf)
{
	if (inim == nullptr ) {

		int tam = conf->getTamVecC();
		Edificio * in_best = nullptr;

		for (int i = 1; i <= tam; i++) {
			Colonia * c = conf->getColonia(i);
			int tam1 = c->getTamEdificio();
			int ini_perto = -1;
			for (int j = 0; j < tam1 && ser->getColonia() != c; j++) {
				Edificio * in = c->getEdificio(j);
				int dis = conf->calcula_dist(ser->getCoorX(), ser->getCoorY(), in->getCoorX(), in->getCoorY());

				if (dis < ini_perto || ini_perto == -1) {
					ini_perto = dis;
					in_best = in;
				}
			}
		}
		inim = in_best;

	}

	if (inim != nullptr)
		conf->MoveSer(ser, inim->getCoorX(), inim->getCoorY());

}

int BuildSeeker::tipo_carateristica()
{
	return 3;
}

Caracteristica * BuildSeeker::novacar()
{
	return new BuildSeeker();
}

int BuildSeeker::getFlag()
{
	return false;
}

void BuildSeeker::setFlag(int f)
{

}

Walker::Walker() : Caracteristica("Walker", 11, 1, 1, 0, 0, 0) {}

struct temp {
	int x, y;
};

void Walker::execCar(Ser * ser, Colonia * co, Configuracao * conf)
{
	temp a;
	vector <temp> t;
	if (conf->checkMovimento(ser->getCoorX() - 1, ser->getCoorY() - 1, conf)) {
		a.x = ser->getCoorX() - 1;
		a.y = ser->getCoorY() - 1;
		t.push_back(a);
	}
	if (conf->checkMovimento(ser->getCoorX() - 1, ser->getCoorY(), conf)) {
		a.x = ser->getCoorX() - 1;
		a.y = ser->getCoorY();
		t.push_back(a);
	}
	if (conf->checkMovimento(ser->getCoorX() - 1, ser->getCoorY() + 1, conf)) {
		a.x = ser->getCoorX() - 1;
		a.y = ser->getCoorY() + 1;
		t.push_back(a);
	}
	if (conf->checkMovimento(ser->getCoorX(), ser->getCoorY() - 1, conf)) {
		a.x = ser->getCoorX();
		a.y = ser->getCoorY() - 1;
		t.push_back(a);
	}
	if (conf->checkMovimento(ser->getCoorX(), ser->getCoorY() + 1, conf)) {
		a.x = ser->getCoorX();
		a.y = ser->getCoorY() + 1;
		t.push_back(a);
	}
	if (conf->checkMovimento(ser->getCoorX() +1 , ser->getCoorY() - 1, conf)) {
		a.x = ser->getCoorX() +1;
		a.y = ser->getCoorY() - 1;
		t.push_back(a);
	}
	if (conf->checkMovimento(ser->getCoorX() +1, ser->getCoorY() , conf)) {
		a.x = ser->getCoorX()+1;
		a.y = ser->getCoorY();
		t.push_back(a);
	}
	if (conf->checkMovimento(ser->getCoorX()+1, ser->getCoorY() + 1, conf)) {
		a.x = ser->getCoorX()+1;
		a.y = ser->getCoorY() + 1;
		t.push_back(a);
	}
	if (t.size() == 0) //ser encurralado
		return;
	temp b = t[rand() % t.size()];
	int novo_x=b.x, novo_y=b.y;

	conf->mudarCoordSer(ser, ser->getCoorX(), ser->getCoorY(), novo_x, novo_y, conf);

}

int Walker::tipo_carateristica()
{
	return 3;
}

Caracteristica * Walker::novacar()
{
	return new Walker();
}

int Walker::getFlag()
{
	return false;
}

void Walker::setFlag(int f)
{

}

Remedio::Remedio() : Caracteristica("Remedio", 12, 2, 1, 0, 0, 2), flag(1) {}

void Remedio::execCar(Ser * ser, Colonia * conf, Configuracao * co)
{
	if (ser->getVidaAtual() <= 3 && flag) {
		flag = 0;
		ser->atVida(2);
	}
}

int Remedio::tipo_carateristica()
{
	return 2;
}

Caracteristica * Remedio::novacar()
{
	return new Remedio();
}

int Remedio::getFlag()
{
	return false;
}
void Remedio::setFlag(int f)
{

}

void Remedio::setContEspada(int i)
{
}

SecondChance::SecondChance() : Caracteristica("SecondChance", 13, 3, 0, 0, 0, 0), flag(0) {}

void SecondChance::execCar(Ser * ser, Colonia * conf, Configuracao * co)
{
	if (flag==1) {
		co->mudarCoordSer(ser, ser->getCoorX(), ser->getCoorY(), conf->getCastelo()->getCoorX(), conf->getCastelo()->getCoorY(), co);
		ser->setVidaAtual(ser->getVidaMax());
		flag = 2;

		ser->eleCarM(this);
		this->~SecondChance();
	}
}

int SecondChance::tipo_carateristica()
{
	return 2;
}

Caracteristica * SecondChance::novacar()
{
	return new SecondChance();
}

int SecondChance::getFlag()
{
	return flag;
}

void SecondChance::setFlag(int f)
{
	flag = f;
}

Caracteristica::Caracteristica(string n, int i, int cm, int cf, int a, int d, int s) :nome(n), id(i), custo_moedas(cm), custo_forca(cf), ataque(a), defesa(d), saude(s) {}

void Caracteristica::toString(ostringstream os)
{
	os << "Carateristica: " << nome << " Custo monetario: " << custo_moedas << " Custo forca: " << custo_forca << endl;
}


void Caracteristica::setCusto_forca(int c)
{
	custo_forca = c;
}

int Caracteristica::getAtaque()
{
	return ataque;
}

int Caracteristica::getDefesa()
{
	return defesa;
}

int Caracteristica::getSaude()
{
	return saude;
}

string Caracteristica::getNome()
{
	return nome;
}

int Caracteristica::getCusto_forca() const
{
	return custo_forca;
}

void Caracteristica::setCusto_moedas(int c)
{
	custo_moedas = c;
}


void Bandeira::NoCastelo(Ser * ser) {

}
void Bandeira::setContEspada(int i)
{
}
void Superior::NoCastelo(Ser * ser) {

}
void Superior::setContEspada(int i)
{
}
void PeleDura::NoCastelo(Ser * ser) {

}

void PeleDura::setContEspada(int i)
{
}

void Armadura::NoCastelo(Ser * ser) {

}
void Armadura::setContEspada(int i)
{
}
void Faca::NoCastelo(Ser * ser) {

}
void Faca::setContEspada(int i)
{
}
void Espada::NoCastelo(Ser * ser) {
	if (ser->getCastelo()) {
		cont = 2;
	}
}
void Espada::setContEspada(int i)
{
	cont += i;
}
void Agressao::NoCastelo(Ser * ser) {

}
void Agressao::setContEspada(int i)
{
}
void Ecologico::NoCastelo(Ser * ser) {

}
void Ecologico::setContEspada(int i)
{
}
void HeatSeeker::NoCastelo(Ser * ser) {
	if (ser->getCastelo()){
		inim = nullptr;
		dist_ant = -1;
	}
}
void HeatSeeker::setContEspada(int i)
{
}
void BuildSeeker::NoCastelo(Ser * ser) {
	if (ser->getCastelo())
		inim = nullptr;
}
void BuildSeeker::setContEspada(int i)
{
}
void Walker::NoCastelo(Ser * ser) {

}
void Walker::setContEspada(int i)
{
}
void Remedio::NoCastelo(Ser * ser) {
	if (ser->getCastelo())
		flag = 1;
}
void SecondChance::NoCastelo(Ser * ser) {
	//if (ser->getCastelo())
	//	flag = 0;
}

void SecondChance::setContEspada(int i)
{
}

Pistola::Pistola() : Caracteristica("Pistola", 14, 3, 4, 0, 0, 0) {}

int Pistola::tipo_carateristica()
{
	return 2;
}
void Pistola::execCar(Ser * ser, Colonia * co, Configuracao * conf) {
	
	Ser * s = conf->SerVizinho(co, ser->getCoorX(), ser->getCoorY(), 2);
	if (s != nullptr)
	{
		conf->ser_ser(ser, s);
	}
}
int Pistola::getFlag()
{
	return false;
}
void Pistola::setFlag(int f)
{

}
Caracteristica * Pistola::novacar()
{
	return new Pistola();
}
void Pistola::NoCastelo(Ser * ser) {
	
}

void Pistola::setContEspada(int i)
{
}
