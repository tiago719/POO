#pragma once
#include "Perfil.h"
#include "colonia.h"
#include <vector>
#include "Edificio.h"

class Colonia;

class Perfil;

class Caracteristica;

class Caracteristica_comportamento;

class celula;

class Edificio_Lista;

class Configuracao {
	int dimX, dimY, moedas, zoom, focoX, focoY;
	string nome_save;
	//vector<Ser *> VecS;
	vector<Perfil *> VecP;
	vector<Perfil *> VecP_PC;
	vector<Colonia *> VecC;
	vector<Caracteristica *> ListaCar;
	vector<Edificio *> ListaEd;
	celula ** mapa;

public:
	Configuracao();

	~Configuracao();

	void criaMapa();

	int getZoom() const;
	
	string getNome() const;

	void setZoom(int z);

	int getFocoX() const;

	void setFocoX(int x);

	int getFocoY() const;

	void setFocoY(int y);

	celula * getPosMapa(int x, int y);

	void setPosMapa(int x, int y,char c, int cor);

	void mudarCoordSer(Ser * s, int x, int y, int xnovo, int ynovo, Configuracao * conf);


	//Lista_Caracteristica getListaCar();

	/*Caracteristica getCar(int id)
	{
		return lista_car->getCaracteristica(id);
	}*/

	void novaColonia();

	int getTamVecC();

	Colonia * getColonia(int cor);

	Colonia * getColoniaPos(int pos);

	int getTamVecP();
	int getTamVecP_PC();

	Perfil * getPerfil(char c);
	Perfil * getPerfil_PC(char c);

	char getLetraPerfil(int a);

	void novoPerfil(char c);
	void novoPerfil_PC(char c);

	bool eliminaPerfil(char c);

	int getDimX() const;

	int getDimY() const;
	
	int getMoedas() const;
	
	void setDimX(int x);
	
	void setDimY(int y);
	
	void setMoedas(int m);
	void setNome(string m);
	
	bool verifica();
 
	//void criarLista();

	Caracteristica * getCar(int id);

	int getTamLisEd();
	
	Edificio * getEd(int a);

	Edificio * getEdbyLetra(char l);

	int getTamListaCar();

	Ser * SerVizinho(Colonia * col, int x, int y, int a);

	Edificio * EdificioVizinho(Ser * ser,int x, int y);

	bool checkMovimento(int x, int y, Configuracao * conf);

	int calcula_dist(int x, int y, int xdest, int ydest);

	void MoveSer(Ser * s, int xdest, int ydest);

	void novaIteracao();

	//retorna true se fim de jogo
	bool verifFim();

	void copia(Configuracao * c);

	Perfil * getPerfilId(int x);
	Perfil * getPerfilId_PC(int x);

	void ser_ser(Ser *a, Ser * b);

	void ser_edif(Ser *a, Edificio * b);

	void edif_ser(Edificio * a, Ser * b);
	void fazMaxEdificio(Colonia * c, int i);

	void fazMaxSeres(Colonia * c, int i);




};