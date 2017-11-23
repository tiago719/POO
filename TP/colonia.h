#pragma once
#include "ser.h"
#include "celula.h"
#include "Perfil.h"	
#include "celula.h"
#include "Configuracao.h"
#include <cmath> 

class Ser;

class Configuracao;

class Edificio;

class celula;

class Colonia {
	vector< Edificio *> ed;
	vector<Ser *> se;
	int cor;
	int moedas;
	static int cont;
	bool flag_ataca, flag_recolhe;
	int idEd;
	Configuracao * conf;

public:
	Colonia(Configuracao * conf);

	~Colonia();

	bool getFlagAtaca();

	void setFlagAtaca(bool f);

	bool getFlagRecolhe();

	void setFlagRecolhe(bool f);

	int getCoorxSer(int id) const;

	int getCoorySer(int id) const;

	int getCoorxEd(int id) const;

	int getCooryEd(int id) const;
	
	string toString() const;

	//celula ** getMapa();

	void iniciarCastelo();

	int getCor() const;
	
	Edificio * getCastelo() const;

	int getMoedas() const;

	bool mudarCoorCastelo(int x, int y);

	bool addSer(Perfil * p);

	Edificio * getEdificio(int i);

	int getTamEdificio();

	Ser * getSer(int i);

	int getTamSer();

	void setMoedas(int num);
	
	void setCoorCasteloX(int num);

	void setCoorCasteloY(int num);
	
	void alteraMoedas(int num);

	void colocaCasteloMapa();

	bool addEdif(int x, int y, char letra);

	bool sellEdif(int eid);

	void nova_iteracao_edif();

	void nova_iteracao_ser();

	void nova_iteracao_mortos();

	int procuraSer(Ser * s);

	int procuraEd(Edificio *e);

	void removeSer(Ser * s);

	void removeEd(Edificio *e);

	void addEdifVec(Edificio * c);

	void addSerfVec(Ser * c);

};