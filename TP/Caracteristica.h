#pragma once
#include <sstream>
#include <iostream>
#include <vector>
#include "ser.h"
using namespace std;

class Ser;
class Edificio;
class Configuracao;
class Colonia;

class Caracteristica
{
	int id, custo_moedas, custo_forca, ataque, defesa, saude;
	string nome;

public:
	Caracteristica(string n, int i, int cm, int cf, int a, int d, int s);

	Caracteristica(){}

	void toString(ostringstream os);

	int getId() const;

	int getCusto_moedas() const;

	int getCusto_forca() const;

	void setCusto_moedas(int c);

	void setCusto_forca(int c);

	int getAtaque();

	int getDefesa();

	int getSaude();

	string getNome();

	virtual int tipo_carateristica() = 0;
	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co) = 0;
	virtual Caracteristica * novacar() = 0;
	virtual int getFlag() = 0;
	virtual void setFlag(int f) = 0;
	virtual void NoCastelo(Ser * ser) = 0;
	virtual void setContEspada(int i) = 0;
};

//CARATERISTICA DE NATUREZA


class Bandeira :public Caracteristica
{

public:
	Bandeira() :Caracteristica("Bandeira",1,1, 0,0,0,0){}

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);


};

class Superior :public Caracteristica
{

public:
	Superior() :Caracteristica("Superior",2,1,1,0,0,1) {}

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class PeleDura :public Caracteristica
{

public:
	PeleDura() :Caracteristica("PeleDura",3,2,2,0,1,0) {}

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class Armadura :public Caracteristica
{

public:
	Armadura() :Caracteristica("Armadura",4,2,3,0,2,0) {}

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co) ;
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class Faca :public Caracteristica
{

public:
	Faca() :Caracteristica("Faca",5,1,1,1,0,0) {}

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

// -----------------------
//CARATERISTICA DE COMPORTAMENTO

class Espada :public Caracteristica
{
	int cont;

public:
	Espada() :Caracteristica("Espada",6,2,2,3,0,0), cont(2) {} 

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	int getCont();
	void setCont(int c);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class Agressao :public Caracteristica
{
public:
	Agressao():Caracteristica("Agressao",7,1,1,0,0,0) {}

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class Ecologico :public Caracteristica
{
public:
	Ecologico() :Caracteristica("Ecologico",8, 1, 1, 0, 0, 0) {}

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class HeatSeeker :public Caracteristica
{
	Ser * inim;
	int count, dist_ant;
public:
	HeatSeeker();

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class BuildSeeker :public Caracteristica
{
	Edificio * inim;
public:
	BuildSeeker();

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class Walker :public Caracteristica
{
public:
	Walker();

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class Remedio :public Caracteristica
{
	int flag;
public:
	Remedio();

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void setContEspada(int i);
	virtual void NoCastelo(Ser * ser);

};

class SecondChance :public Caracteristica
{
	int flag;
public:
	SecondChance();

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};

class Pistola :public Caracteristica
{
public:
	Pistola();

	virtual void execCar(Ser * ser, Colonia * conf, Configuracao * co);
	virtual int tipo_carateristica();
	virtual Caracteristica * novacar();
	virtual int getFlag();
	virtual void setFlag(int f);
	virtual void NoCastelo(Ser * ser);
	virtual void setContEspada(int i);

};



