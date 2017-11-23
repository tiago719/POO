#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "Perfil.h"
#include "celula.h"
#include "Configuracao.h"

using namespace std;

class Colonia;

class Configuracao;
class Caracteristica;

class Ser {
	int vida_max, vida_atual, forca, velocidade, ataque, defesa, coorX, coorY, flag_bandeira, ataque_bonus;
	vector <Caracteristica *> carM;
	char letra;
	int num_carNatureza;
	Colonia * colonia;
	int cor;
	Perfil *per;
	bool castelo;

public:
	Ser(Perfil * p, Colonia * co, Configuracao * conf, int x, int y, int cor);

	Ser(){
		
	}
		 
	~Ser();

	int getTamVecCar();

	Caracteristica * getCar(int id);

	void setFlagBandeira(int b);

	int getFlagBandeira();

	void addPerfil(Perfil * p, Colonia * co, Configuracao * conf);
	void addVida_max(int x);
	void addDefesa(int x);
	void addAtaque(int x);
	void atVida(int x);
	
	//void addCaracteristica(int id, Colonia * co);

	Perfil* getPerfil();

	void toString(ostringstream & os) const;

	void ligaSer(Colonia * c);

	void novaJogada(Configuracao * conf);

	int getVidaAtual();

	int getTamCarM();

	void setVidaAtual(int v);

	int getForca();

	void setAtaque(int f);

	int getDefesa()
	{
		return defesa;
	}

	int getCoorX() const; 

	int getCoorY() const; 

	char getLetra() const;

	char getVidaMax() const;

	int getAtaque();

	void setX(int x);

	void setY(int y);

	bool verifSC();

	Colonia * getColonia() const;

	void copia(Ser * c, Colonia * col, vector <Caracteristica *> * carM);

	Caracteristica * getCarM(int i);

	void setAtaqueBonus(int i);
	int getAtaqueBonus();

	void eleCarM(Caracteristica * c);

	bool getCastelo();


};