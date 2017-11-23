#pragma once
#include "celula.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Configuracao;
class Colonia;
class Perfil;
class Ser;
class celula;

class Edificio {
	string nome;
	char letra;
	Colonia * col;
protected:
	int saude, defesa, ataque, custo, saude_inicial, nivel, idEd;
	int x, y;

public:
	Edificio(Colonia * c,int s, int d, char l, int coorX, int coorY, int id);

	Edificio(char l, int s, int d, int c, int a);

	~Edificio();

	Colonia * getColonia();

	int getIdEd() const;

	void setIdEd(int a);

	int getCoorX() const;

	int getCoorY() const;

	void setCoorX(int a);

	void setCoorY(int b);

	void atVida(int b);

	int getCusto() const;

	int getSaude() const;

	void setSaude(int s);

	int getSaudeInicial() const;

	char getLetra() const; 

	int getNivel() const;

	void setNivel(int n);

	int getDefesa();

	void setDefesa(int d);

	int getAtaque();

	void setAtaque(int a);

	void toString(ostringstream &os) const; 

	void repara(Colonia * col, Configuracao * conf);


	virtual bool upgrade(Colonia * col) = 0;

	virtual bool mudarCoord(int x, int y, Configuracao * conf, Colonia * c)=0;

	virtual void novaIteracao(Colonia * col, Configuracao * conf) = 0;

	virtual bool sell(Colonia * col, Configuracao * conf) = 0;

	virtual Edificio * copiaNovo(Edificio * c) = 0;

	void copia(Edificio * c);



};

class Castelo : public Edificio
{

public:
	Castelo(Colonia * c,int coorX, int coorY,int idEd);

	Castelo();

	bool mudarCoord(int x, int y, Configuracao * conf, Colonia * c);

	bool upgrade(Colonia * col);

	void novaIteracao(Colonia * col, Configuracao * conf);

	bool sell(Colonia * col, Configuracao * conf);

	virtual Edificio * copiaNovo(Edificio * c) ;


	
};

class Torre : public Edificio {
public:

	Torre(Colonia * c,int coorX, int coorY, int idEd);

	Torre();

	bool mudarCoord(int x, int y, Configuracao * conf, Colonia * c);

	bool upgrade(Colonia * col);

	void novaIteracao(Colonia * col, Configuracao * conf);

	bool sell(Colonia * col, Configuracao * conf);

	virtual Edificio * copiaNovo(Edificio * c);

};

class Quinta : public Edificio {
public:

	Quinta(Colonia * c,int coorX, int coorY, int idEd);

	Quinta();

	bool mudarCoord(int x, int y, Configuracao * conf, Colonia * c);

	bool upgrade(Colonia * col);

	void novaIteracao(Colonia * col, Configuracao * conf);

	bool sell(Colonia * col, Configuracao * conf);

	virtual Edificio * copiaNovo(Edificio * c);

};