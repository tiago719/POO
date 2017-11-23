#include "stdafx.h"
#include "ser.h"
#include "Perfil.h"
#include "Configuracao.h"
#include "Consola.h"

Ser::Ser(Perfil * p, Colonia * co, Configuracao * conf, int x, int y, int cor):coorX(x), coorY(y), cor(cor),
num_carNatureza(0), ataque_bonus(0), castelo(true)
{
	vida_max = 10;
	ataque = 0;
	defesa = 0;
	vida_atual = vida_max;
	forca = p->getCustoForcaT();
	colonia = co;
	flag_bandeira = 0;
	letra = p->getLetra();
	per = p;
	addPerfil(p, co, conf);

}
Ser::~Ser()
{
	colonia->removeSer(this);
}

int Ser::getFlagBandeira()
{
	return flag_bandeira;
}

void Ser::addPerfil(Perfil * p, Colonia * co, Configuracao * conf)
{
	//carM = p;
	Caracteristica * nova;		
	for (int i = 0; i < p->getTamVecC(); i++) 
	{
		if (p->ExistCar(1) == true)
		{
			Caracteristica * c = p->getCaracteristica(i);
			if (c->tipo_carateristica() == 1)
			{
				c->execCar(this, co, conf);
			}
			else if (c->tipo_carateristica() == 3) {
				nova = c->novacar();
				carM.insert(carM.begin(), nova);
			}
			else if (c->tipo_carateristica() == 2) {
				nova = c->novacar();
				carM.push_back(nova);
			}
		}
	}
}

void Ser::addVida_max(int x)
{
	vida_max += x;
}

void Ser::addDefesa(int x)
{
	defesa += x;
}

void Ser::addAtaque(int x)
{
	ataque += x;
}

void Ser::setAtaque(int f)
{
	ataque = f;
}

void Ser::atVida(int x)
{
	vida_atual += x;
}

Perfil * Ser::getPerfil()
{
	return per;
}

void Ser::toString(ostringstream & os) const
{
	os << "Perfil: " << letra << "\t Ataque: " << ataque
		<< "\t Defesa: " << defesa << "\t Vida: " << vida_atual << "\t CoorX: " << coorX << " CoorY: " << coorY << "\t Forca Usada: " << forca << " Moedas: " << per->getCustoT()<< endl;
}

void Ser::ligaSer(Colonia* c) {
	colonia = c;
}


int Ser::getTamVecCar()
{
	return static_cast<int>(carM.size());
}

Caracteristica * Ser::getCar(int id)
{
	for (int i = 0; i < carM.size(); i++)
	{
		if (carM[i]->getId() == id)
		{
			carM[i]->getFlag();
			return carM[i];
		}
	}

	return nullptr;
}
void Ser::setFlagBandeira(int b)
{
	flag_bandeira = b;
}
void Ser::novaJogada(Configuracao * conf)
{
	Edificio * C = this->getColonia()->getCastelo();

	if (colonia->getFlagAtaca() == true)
	{
		if (per->ExistCar(1) == true)
		{
			for (int i = 0; i < carM.size(); i++)
			{
				carM[i]->execCar(this, this->colonia, conf);
			}
		}
		else
		{
			conf->getCar(11)->execCar(this, this->colonia, conf);
		}

		if (conf->calcula_dist(coorX, coorY, C->getCoorX(), C->getCoorY()) > 0) {
			castelo = false;
		}

	}
	if (colonia->getFlagRecolhe() == true)
	{
		
		if (C->getCoorX() == coorX && C->getCoorY() == coorY)
		{

		}
		 else if (conf->calcula_dist(coorX, coorY, C->getCoorX(), C->getCoorY()) == 1) {
			conf->getPosMapa(coorX, coorY)->limpaCelula();
			coorX = C->getCoorX();
			coorY = C->getCoorY();
			castelo = true;
		}
		 conf->MoveSer(this, C->getCoorX(), C->getCoorY());
	}
}

int Ser::getVidaAtual()
{
	return vida_atual;
}

void Ser::setVidaAtual(int v)
{
	vida_atual = v;
}

int Ser::getForca()
{
	return forca;
}

int Ser::getCoorX() const
{
	return coorX;
}

int Ser::getCoorY() const
{
	return coorY;
}

char Ser::getLetra() const
{
	return letra;
}

char Ser::getVidaMax() const
{
	return vida_max;
}

int Ser::getAtaque()
{
	return ataque + getAtaqueBonus();
}

void Ser::setX(int x) 
{
	this->coorX = x;
}

void Ser::setY(int y)
{
	coorY = y;
}

bool Ser::verifSC()
{
	for (int i = 0; i < carM.size(); i++) {
		if (carM[i]->getFlag())
			return 1;
	}
	return 0;
}

Colonia * Ser::getColonia() const
{
	return colonia;
}

void Ser::copia(Ser * c, Colonia * col, vector <Caracteristica *> * carM) {
	this->ataque = c->ataque;
	this->vida_max = c->vida_max;
	this->vida_atual = c->vida_atual;
	this->forca = c->forca;
	this->velocidade = c->velocidade;
	this->ataque = c->ataque;
	this->defesa = c->defesa;
	this->coorX = c->coorX;
	this->coorY = c->coorY;
	this->coorY = c->coorY;
	this->letra = c->letra;
	this->num_carNatureza = c->num_carNatureza;
	this->colonia = col;
	this->cor = cor;

	for (int i = 0; i < carM->size(); i++) {
		this->carM.push_back((*carM)[i]->novacar());
	}

}

int Ser::getTamCarM() {
	return static_cast<int>(carM.size());
}

Caracteristica * Ser::getCarM(int i) {
	return carM[i];
}

void Ser::setAtaqueBonus(int i)
{
	ataque_bonus += i;
}

int Ser::getAtaqueBonus()
{
	int temp = ataque_bonus;
	ataque_bonus = 0;
	return temp;
}

void Ser::eleCarM(Caracteristica * c)
{
	for (int i = 0; i < carM.size(); i++) {
		if (carM[i] == c) {
			carM.erase(carM.begin() + i);
		}
			
	}
}

bool Ser::getCastelo() {
	return castelo;
}