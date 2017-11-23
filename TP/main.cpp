// TP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "perfil.h"
#include "ser.h"
#include "colonia.h"
#include "Edificio.h"
#include "Caracteristica.h"
#include "lista_edificios.h"
#include "Consola.h"
#include "celula.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Configuracao.h"
#include <fstream>

#define MaxMoedas 10000 

using namespace std;

void mostrar_mapa(Configuracao * conf) {
	system("cls");

	if(conf->getZoom() == 1)
		Consola::setTextSize(8, 16);
	else
		Consola::setTextSize(4, 8);


	/*switch (conf->getZoom()) {
	case 1:
		Consola::setTextSize(8, 16);
		break;
	case 2:
		Consola::setTextSize(4, 8);
		break;
	case 3:
		Consola::setTextSize(4, 8);

		Consola::setTextSize(2, 4);
		break;
	case 4:
		Consola::setTextSize(4, 8);

		Consola::setTextSize(1, 2);
		break;
	}*/

	int focox = conf->getFocoX();
	int focoy = conf->getFocoY();

	for (int i = focox; i <  (20 * conf->getZoom()) && i<conf->getDimX(); i++)
	{
		for (int j = focoy; j <(40 * conf->getZoom()) && j<conf->getDimY(); j++) 
		{

			Consola::setTextColor(conf->getPosMapa(i,j)->getCor());
			putchar(conf->getPosMapa(i,j)->getLetra());
			Consola::setTextColor(Consola::BRANCO);

			putchar('|');
		}
		putchar('\n');
	}
	//Consola::setTextSize(8, 16);
	
	for (int i = 1; i <= conf->getTamVecC(); i++)
	{
		Consola::setTextColor(conf->getColonia(i)->getCor());
		cout << "Moedas colonia " << conf->getColonia(i)->getCor() << " : " << conf->getColonia(i)->getMoedas() << endl;
	}
	Consola::setTextColor(Consola::BRANCO);
}

void mostrar_mapa_todo(Configuracao * conf, int zoom=1) {//debug
	system("cls");
	switch (zoom) {
	case 1:
		Consola::setTextSize(4, 8);
		break;
	}
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j <100; j++) {
			putchar('|');

			Consola::setTextColor(conf->getPosMapa(i,j)->getCor());
			putchar(conf->getPosMapa(i, j)->getLetra());
			Consola::setTextColor(Consola::BRANCO);

			//cout << "X: " << i << " Y: " << j ;
		}
		putchar('\n');

	}
}

bool interpeta_comando(string line, Configuracao * conf, string fich_ant, bool * flag) {

	string palavra;

	for (int i = 0; line[i] != '\0'; i++)
	{
		line[i] = toupper(line[i]);
	}

	istringstream si(line);

	si >> palavra;

	int i1 = 0, i2 = 0, i3 = 0;
	char c;
	string cor = "NULL";

	ostringstream os;

	string cores[16] = { "PRETO", "AZUL", "VERDE", "CYAN","VERMELHO", "ROXO", "AMARELO", "BRANCO", "CINZENTO", "AZUL_CLARO", "VERDE_CLARO", "CYAN_CLARO", "VERMELHO_CLARO", "COR_DE_ROSA", "AMARELO_CLARO", "BRANCO_CLARO" };
	string key[10] = { "DIM","MOEDAS","OPONENTES" ,"CASTELO", "MKPERFIL", "ADDPERFIL", "SUBPERFIL","RMPERFIL", "LOAD", "INICIO" };
	for (int i = 0; i < 10; i++)
	{
		if (palavra == key[i])
		{
			switch (i)
			{
			case 0://DIM
			{
				i1 = i2 = -1;
				si >> i1 >> i2;
				conf->setDimX(i1);
				conf->setDimY(i2);

				if (i1 < 20 || i2 < 40 || i1 > 150 || i2 > 150)
				{
					cout << "Sintaxe: dim { numero linhas(20-150) } { numero colunas(40-150) }" << endl;
					return false;
				}
				conf->criaMapa(); //TODO: quando as coordenadas sao 20 40 esta a dar erro, nao sei porque
				cout << "Comando Aceite" << endl;
				return true;
			}

			case 1://MOEDAS
			{
				i1 = 0;
				si >> i1;
				if (i1 < 20)
				{
					cout << "Sintaxe: moedas { numero de moedas > 20 } " << endl; 
					return false;
				}
				conf->setMoedas(i1);
				
				cout << "Comando Aceite" << endl;
				return true;
			}
			case 2://OPONENETES
			{
				i1 = i2 = -1;
				si >> i1;

				if (i1 < 1 || i1 >15)
				{
					cout << "Sintaxe: oponentes { numero oponentes(1-15 }" << endl;
					return false;
				}

				for (int i = 0; i < i1; i++) {

					conf->novaColonia();
				}

				cout << "Comando Aceite" << endl;
				return true;
			}
			case 3://CASTELO
			{
				if (conf->getDimX() == 0 || conf->getDimY()==0)
				{
					cout << "Precisa configurar o mapa de jogo primeiro" << endl;
					return false;
				}

				i1 = i2 = -1;
				si >> cor; 

				if (cor == "NULL")
				{
					cout << "Sintaxe: castelo {cor} { linha castelo (0-" << conf->getDimX() << ") } {coluna castelo (0-" << conf->getDimY() << ")} "<< endl;
					return false;
				}

				for (int i = 0; cor[i] != '\0'; i++)
				{
					cor[i] = toupper(cor[i]);
				}//TODO:TIRAR ISTO PORQUE JA FAZ TOUPPER ANTES

				int n_colonia = -1;

				for (int i = 1; i < 16; i++)
				{
					if (cor == cores[i])
					{
						n_colonia = i;
						break;
					}
				}

				si >> i1 >> i2;

				if (i1 == NULL || i2 == NULL)
				{
					cout << "Sintaxe: castelo {cor} { linha castelo (0-" << conf->getDimX() << ") } {coluna castelo (0-" << conf->getDimY() << ")} " << endl;
					return false;
				}
				int a = conf->getTamVecC();

				if (n_colonia == NULL || n_colonia > a)
				{
					cout << "Colonia Inexistente" << endl;
					return false;
				}

				else
					if (i1 <0 || i1 >conf->getDimX() || i2 < 0 || i2>conf->getDimY())
					{
						cout << "Sintaxe: castelo {cor} { linha castelo (0-" << conf->getDimX() << ") } {coluna castelo (0-" << conf->getDimY() << ")} " << endl;
						return false;
					}
				conf->getPosMapa(conf->getColonia(n_colonia)->getCastelo()->getCoorX(), conf->getColonia(n_colonia)->getCastelo()->getCoorY())->setEdificio(nullptr);
				conf->setPosMapa(conf->getColonia(n_colonia)->getCastelo()->getCoorX(), conf->getColonia(n_colonia)->getCastelo()->getCoorY(), '0', 0);
				conf->getColonia(n_colonia)->setCoorCasteloX(i1);
				conf->getColonia(n_colonia)->setCoorCasteloY(i2);
				conf->setPosMapa(i1, i2, 'C', n_colonia);
				conf->getPosMapa(i1, i2)->setEdificio(conf->getColonia(n_colonia)->getCastelo());

				cout << "Comando Aceite" << endl;
				return true;
			}

			case 4://MKPERFIL
			{
				si >> c;

				if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) // ascii // TODO: se inserir, por exemplo, 80 vai dar na mesma porque corresponde a uma letra valida
				{
					cout << "Sintaxe: perfil { letra correspondente ao perfil (A-Z) ou (a-z) }" << endl;
					return false;
				}

				conf->novoPerfil(c);
				cout << "Comando Aceite" << endl;
				return true;
			}

			case 5://ADDPERFIL
			{
				i1 = -1;
				c = 'º';
				si >> c >> i1;

				if (i1 == -1 || i1 > conf->getTamListaCar() || !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
				{
					cout << "Sintaxe: addperfil { letra correspondente ao perfil (A-Z) ou (a-z) } { id carateristica (1-" << conf->getTamListaCar() + 1 << ") }" << endl;
					return 0;
				}

				if (conf->getPerfil(c)!=0)
				{
					if (conf->getPerfil(c)->getCustoForcaT() + conf->getCar(i1)->getCusto_forca() <= 10)
					{
						conf->getPerfil(c)->addCar(i1, conf);
						cout << "Comando Aceite" << endl;
						return true;
					}

					else
					{
						cout << "A carateristica ultrapasse o limite de pontos de forca" << endl;
						return 0;
					}
				}
				else
				{
					return false;
				}
			}

			case 6://SUBPERFIL
			{
				i1 = -1;
				c = 'º';
				si >> c >> i1;// TODO: ver se a carateristica e valida
				if (i2 == -1 || i2 > conf->getTamListaCar() || c=='º' || !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
				{
					cout << "Sintaxe: subperfil { letra correspondente ao perfil (A-Z) ou (a-z) } { id carateristica (1-" << conf->getTamListaCar() + 1 << ") }" << endl;
				}

				if (conf->getPerfil(c))
				{
					int j = 0;
					for ( j = 0; j < conf->getPerfil(c)->getTamVecC(); j++)
					{
						if (conf->getPerfil(c)->getCaracteristica(j)->getId() == i1)
						{
							break;
						}
					}

					if (conf->getPerfil(c)->getTamVecC() == j)
					{
						cout << "A caraterisitca introduzida nao existe no perfil indicado" << endl;
						return 0;
					}

					conf->getPerfil(c)->removeCar(i1);
					cout << "Comando Aceite" << endl;
					return true;
				}
				else
				{
					cout << "Perfil inexistente" << endl;
				}
				return false;
			}

			case 7://RMPERFIL
			{
				si >> c;

				if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) 
				{
					cout << "Sintaxe:  rmperfil { letra correspondente ao perfil (A-Z) ou (a-z) }" << endl;
					return false;
				}

				if (conf->eliminaPerfil(c))
				{
					cout << "Comando Aceite" << endl;
					return true;
				}
			case 8://LOAD
			{
				si >> palavra;
				ifstream fich("../" + palavra);

				if (fich.is_open() && palavra != fich_ant)
				{
					while (!fich.eof())
					{
						getline(fich, line);
						interpeta_comando(line, conf, palavra, flag);
					}
					fich.close();
				}
				else
				{
					fich.close();
					cout << "Nao foi possivel abrir o ficheiro" << endl;
				}
			}
			return true;

			case 9://INICIO
			{
				//TODO:comeca o jogo
				*flag = true;
				cout << "Comando Aceite" << endl;
			}
			return true;
			}
			}
		}//if
	}
	return false;
}

void config(Configuracao * conf) 
{
	string linha;
	bool flag = false;
	do {
		getline(cin, linha);

		//-----------PARA DEBUG------------------TODO:RETIRAR
		if (linha == "a" || linha == "A")
			linha = "load configuracao.txt";
		//---------------------------------------

		if (!interpeta_comando(linha, conf,"", &flag))
			cout << "Comando Invalido!" << endl;
		if (flag) {
			break;
		}
	} while (linha != "inicio" );
	
}

bool interpeta_simulacao(string line, Configuracao * conf, vector<Configuracao *> * saves)
{
	string key[21] = { "FOCO","ZOOMOUT", "SETMOEDAS", "BUILD", "LIST", "LISTP", "LISTALLP", "MKBUILD", "REPAIR", "UPGRADE", "SELL", "SER", "NEXT", "NEXTN", "ATACA", "RECOLHE", "FIM", "SAVE", "RESTORE", "ERASE", "LOAD" };
	string cores[16] = { "PRETO", "AZUL", "VERDE", "CYAN","VERMELHO", "ROXO", "AMARELO", "BRANCO", "CINZENTO", "AZUL_CLARO", "VERDE_CLARO", "CYAN_CLARO", "VERMELHO_CLARO", "COR_DE_ROSA", "AMARELO_CLARO", "BRANCO_CLARO" };

	istringstream si(line);
	string palavra, cor = "NULL", edif = "NULL", colonia = "NULL", nome = "NULL";
	int i1 = -1, i2 = -1, n_colonia = -1;
	char letra;
	si >> palavra;

	for (int i = 0; i < 21; i++)
	{
		if (palavra==key[i])
		{
			switch (i)
			{
			case 0: //foco
			{
				i1 = i2 = -1;;
				si >> i1 >> i2;
				if (i1<0 || i1 >conf->getDimX() || i2 <0 || i2 > conf->getDimY())
				{
					cout << "Sintaxe: foco { linha(0-" << conf->getDimX() << ") } { coluna (0-" << conf->getDimY() << ") }" << endl;
					return 0;
				}
				else
				{
					conf->setFocoX(i1);
					conf->setFocoY(i2);
					mostrar_mapa(conf);
					return 1;
				}
				break;
			}
			case 1: //zoomout
			{
				i1 = -1;
				si >> i1;
				if (i1 < 0 || i1>4)
				{
					cout << "Sintaxe: zoomout { n(0-4) }" << endl;
					return 0;
				}
				else
				{
					conf->setZoom(i1);
					mostrar_mapa(conf);
					return 1;
				}
			}
			case 2://setmoedas
			{
				i1 = -1;
				cor = "NULL";
				si >> cor;
				si >> i1;

				if (cor == "NULL" || i1==-1 || i1>MaxMoedas)
				{
					cout << "Sintaxe: setmoedas { cor } { num (0-" << MaxMoedas << ") }" << endl;
					return 0;
				}

				for (int i = 0; i<16; i++)
				{
					if (cores[i] == cor)
					{
						n_colonia = i;
						break;
					}
				}

				if (n_colonia > conf->getTamVecC())
				{
					cout << "Colonia inexistente" << endl;
				}

				if (i == 16)
				{
					cout << "Sintaxe: setmoedas { cor } { num (0-" << MaxMoedas << ") }" << endl;
					return 0;
				}

				conf->getColonia(n_colonia)->alteraMoedas(i1);
				mostrar_mapa(conf);
				return 1;
			}
			case 3: //build
			{
				i1 = i2 = -1;
				edif = "NULL";
				si >> edif;
				si >> i1 >> i2;
				if (i1<0 || i1>conf->getDimX() || i2<0 || i2 > conf->getDimY() || edif=="NULL")
				{
					cout << "Sintaxe: build { edif } { linha (0-" << conf->getDimX() << ") } {coluna (0-" << conf->getDimY() << ") }" << endl;
					return 0;
				}
				else
				{
					letra = edif[0];
					if (conf->getColonia(1)->addEdif(i1, i2, letra) == false)
					{
						return 0;
					}
					else
					{
						mostrar_mapa(conf);
						return 1;
					}
				}
			}
			case 4: //list
			{
				cor = "NULL";
				si >> cor;

				if (cor == "NULL")
				{
					cout << "Sintaxe: list { cor }" << endl;
					return 0;
				}

				for (int i = 0; i<16; i++)
				{
					if (cores[i] == cor)
					{
						n_colonia = i;

						if (n_colonia > conf->getTamVecC())
						{
							cout << "Colonia Inexistente" << endl;
							return 0;
						}
						else
						{
							conf->getColonia(n_colonia)->toString();
							return 1;
						}
					}
				}
				cout << "Sintaxe: list { cor }" << endl;
				return 0;
			}
			case 5: //listp
			{
				letra = 'º';
				si >> letra;

				if (letra == 'º')
				{
					cout << "Sintaxe: listp { letra correspondente ao perfil (A-Z) ou (a-z) } " << endl;
					return 0;
				}

				for (int i = 0; i < conf->getTamVecP(); i++)
				{
					if (conf->getLetraPerfil(i) == letra)
					{
						conf->getPerfil(letra)->toString();
						return 1;
					}
				}
				
				cout << "Perfil inexistente" << endl;
			}
			case 6://listallp
			{
				for (i = 0; i < conf->getTamVecP(); i++)
				{
					conf->getPerfil(conf->getLetraPerfil(i))->toString();
				}
				return 1;
			}
			case 7: //mkbuild
			{
				i1 = i2 = -1;
				edif = "NULL";
				colonia = "NULL";
				si >> edif;
				si >> i1 >> i2;
				si >> colonia;
				if (i1<0 || i1>conf->getDimX() || i2<0 || i2 > conf->getDimY() || edif == "NULL" || colonia=="NULL")
				{
					cout << "Sintaxe: mkbuild { edif } { linha (0-" << conf->getDimX() << ") } {coluna (0-" << conf->getDimY() << ") } { colonia (cor) }" << endl;
					return 0;
				}

				n_colonia = NULL;

				for (int i = 1; i < 16; i++)
				{
					if (colonia == cores[i])
					{
						n_colonia = i;
						break;
					}
				}

				if (n_colonia == NULL || n_colonia == 0 || n_colonia > conf->getTamVecC())
				{
					cout << "Colonia inexistente" << endl;
				}

				letra = edif[0];

				if (conf->getColonia(n_colonia)->addEdif(i1, i2, letra) == 0)
				{
					return 0;
				}
				else
				{
					mostrar_mapa(conf);
					return 1;
				}
			}
			case 8: //repair
			{
				i1 = -1;
				si >> i1;

				if (i1<0 || i1 > conf->getColonia(1)->getTamEdificio())
				{
					cout << "Sintaxe: repair { eid (0-" << conf->getColonia(1)->getTamEdificio()-1 << ") }" << endl;
					return 0;
				}

				if (i1 >= conf->getColonia(1)->getTamEdificio())
				{
					cout << "Edificio inexistente" << endl;
					return 0;
				}
				conf->getColonia(1)->getEdificio(i1)->repara(conf->getColonia(1),conf);
				return 1;
			}
			case 9: //upgrade
			{
				i1 = -1;
				si >> i1;

				if (i1<0 || i1 > conf->getColonia(1)->getTamEdificio())
				{
					cout << "Sintaxe: upgrade { eid (0-" << conf->getColonia(1)->getTamEdificio()-1 << ") }" << endl;
					return 0;
				}

				if (i1 >= conf->getColonia(1)->getTamEdificio())
				{
					cout << "Edificio inexistente" << endl;
					return 0;
				}
				if (conf->getColonia(1)->getEdificio(i1)->upgrade(conf->getColonia(1)) == 1)
				{
					mostrar_mapa(conf);
					return 1;
				}
				return 0;
			}
			case 10://sell
			{
				i1 = -1;
				si >> i1;

				if (i1<0 || i1 > conf->getColonia(1)->getTamEdificio())
				{
					cout << "Sintaxe: sell { eid (0-" << conf->getColonia(1)->getTamEdificio() << ") }" << endl;
					return 0;
				}

				if (i1 >= conf->getColonia(1)->getTamEdificio())
				{
					cout << "Edificio inexistente" << endl;
					return 0;
				}
				if (conf->getColonia(1)->sellEdif(i1) == 1)
				{
					mostrar_mapa(conf);
					return 1;
				}

				return 0;
			}
			case 11://ser
			{
				i1 = -1;
				letra = 'º';
				si >> i1 >> letra;
				if (i1 == -1 || letra == 'º')
				{
					cout << "Sintaxe: ser { num (num>0) } { letra correspondente ao perfil (A-Z) ou (a-z) }" << endl;
					return 0;
				}

				for (int i = 0; i < i1; i++)
				{
					if (conf->getColonia(1)->addSer(conf->getPerfil(letra)) == false)
					{
						cout << "Nao foi possivel criar ser" << endl;
						return 0;
					}	
				}
				mostrar_mapa(conf);
				return 1;
			}
			case 12://next
			{
				conf->novaIteracao();
				mostrar_mapa(conf);
				if (conf->verifFim()){}
					//FIM DO JOGO


				return 1;
			}
			case 13://nextn
			{
				i1 = -1;
				si >> i1;

				if (i1 < 0)
				{
					cout << "Sintaxe: nextn { num (num>0) }" << endl;
					return 0;
				}

				for (i = 0; i < i1; i++)
				{
					conf->novaIteracao();
					mostrar_mapa(conf);
					if (conf->verifFim()){}
						//FIM DO JOGO
				}
				return 1;
			}
			case 14://ataca
			{
				conf->getColonia(1)->setFlagRecolhe(0);
				conf->getColonia(1)->setFlagAtaca(1);
				return 1;
			}
			case 15://recolhe
			{
				conf->getColonia(1)->setFlagAtaca(0);
				conf->getColonia(1)->setFlagRecolhe(1);
				return 1;
			}
			case 16://fim
			{
				for (int i = 0; i < saves->size(); i++) {
					if ((*saves)[i]->getNome() == conf->getNome()) {
						saves->erase(saves->begin() + i);
						conf->~Configuracao();
					}

				}
				system("cls");
				cout << "Terminou o jogo" << endl;

				for (int i = 0; i < saves->size(); i++) {
					cout << i << " - " << (*saves)[i]->getNome() << endl;

				}

				int op;
				do {
					cout << "Escolha um save para continuar entre 1 - " << saves->size()+1 << " ou 0 para sair!" << endl;
					cin >> op;
				} while (op<0 || op>saves->size());

				if (op == 0) {
					for (int i = 0; i < saves->size(); i++) {
						(*saves)[i]->~Configuracao();
						exit(0);
					}
				}
				else
					conf = (*saves)[op - 1];

				return 1;
			}
			case 17://save
			{
				nome = "NULL";
				si >> nome;
				if (nome == "NULL")
				{
					cout << "Sintaxe: save { nome do save }" << endl;
					return 0;
				}
				bool checkNome = true;;
				for (int i = 0; i < saves->size(); i++) {
					if ((*saves)[i]->getNome() == nome)
						checkNome = false;
				}
				if (checkNome){
					Configuracao * novo = new Configuracao();
					novo->setNome(nome);
					novo->copia(conf);
					saves->push_back(novo);

				}
				return 1;
			}
			case 18://restore
			{
				nome = "NULL";
				si >> nome;
				if (nome == "NULL")
				{
					cout << "Sintaxe: restore { nome do save }" << endl;
					return 0;
				}
				for (int i = 0; i < saves->size(); i++) {
					if ((*saves)[i]->getNome() == nome)
						conf = (*saves)[i];
				}
				mostrar_mapa(conf);
				return 1;
			}
			case 19://erase
			{
				nome = "NULL";
				si >> nome;
				if (nome == "NULL")
				{
					cout << "Sintaxe: erase { nome do save }" << endl;
					return 0;
				}
				for (int i = 0; i < saves->size(); i++) {
					if ((*saves)[i]->getNome() == nome) {
						(*saves)[i]->~Configuracao();
						saves->erase(saves->begin() + i);
					}
				}
				return 1;
			}
			case 20://load
			{
				break;
			}
			}
		}
	}
	return 0;
}

void simulacao(Configuracao * conf, vector<Configuracao *> * saves)
{
	string linha;

	do
	{
		getline(cin, linha);

		for (int i = 0; linha[i] != '\0'; i++)
		{
			linha[i] = toupper(linha[i]);
		}
		Consola::setTextSize(8, 16);
		if (!interpeta_simulacao(linha, conf, saves))
		{
			cout << "Comando de Simulacao Invalido!" << endl;
		}

	} while (linha != "FIM");
}

bool geraCarateristicas(Perfil * p, Configuracao * c) {
	int numcar = rand() % (c->getTamListaCar() - 1 + 1) + 1;
		//rand() % c->getTamListaCar()-1;
	Caracteristica * novaCar = c->getCar(numcar);
	if(p->getCustoForcaT() + novaCar->getCusto_forca() < 10)
		p->addCar(novaCar);
	else 
		return false;

	return true;

}

void copiarPerfil(Perfil * p1, Perfil * p2, Perfil * p3, Configuracao * c) {
	int r1, r2, r3; 
	 
	r1 = rand() % (c->getTamVecP() - 0 + 1) + 0;
	do {
		r2 = rand() % (c->getTamVecP() - 0 + 1) + 0;
	} while (r1!=r2);
	do {
		r3 = rand() % (c->getTamVecP() - 0 + 1) + 0;
	} while (r1 != r3 && r2 != r3);


	for (int i = 0; i < c->getPerfilId(r1)->getTamVecC(); i++) {
		p1->addCar(c->getPerfilId(r1)->getCaracteristica(i));
	}
	for (int i = 0; i < c->getPerfilId(r2)->getTamVecC(); i++) {
		p2->addCar(c->getPerfilId(r2)->getCaracteristica(i));
	}
	for (int i = 0; i < c->getPerfilId(r3)->getTamVecC(); i++) {
		p3->addCar(c->getPerfilId(r3)->getCaracteristica(i));
	}


}

int main()
{
	Perfil * p;
	srand(static_cast<unsigned int>(time(NULL)));
	
	vector<Configuracao *> Saves;

	Configuracao * conf = new Configuracao();
	Saves.push_back(conf);
	
	do {
		cout << "Configure o jogo: " << endl;
		config(conf);
	} while (!conf->verifica());
	
	char l='A';
	conf->novoPerfil_PC(l);

	p = conf->getPerfil_PC(l);

	conf->getPerfil_PC(l)->addCar(1, conf);
	while (geraCarateristicas(p, conf));

	l++;
	conf->novoPerfil_PC(l);
	p = conf->getPerfil_PC(l);
	while (geraCarateristicas(p, conf));

	l+=2;
	conf->novoPerfil_PC(l);
	Perfil * p1 = conf->getPerfil_PC(l);
	l++;
	conf->novoPerfil_PC(l);
	Perfil * p2 = conf->getPerfil_PC(l);
	l++;
	conf->novoPerfil_PC(l);
	Perfil * p3 = conf->getPerfil_PC(l);

	copiarPerfil(p1, p2, p3, conf);






	while (geraCarateristicas(p, conf));
	
	for (int i = 1; i <= conf->getTamVecC() ; i++) {
		conf->getColonia(i)->setMoedas(conf->getMoedas());
		if (conf->getColonia(i)->getCastelo()->getCoorX() == -1 && conf->getColonia(i)->getCastelo()->getCoorY() == -1)
		{
			conf->getColonia(i)->iniciarCastelo();
		}
		else {
			conf->getColonia(i)->colocaCasteloMapa();
		}
	}

	
	/*=====================Simulacao===================*/
	mostrar_mapa(conf);
	simulacao(conf, &Saves);
	cout << "Prima qualquer tecla para sair" << endl;
	getchar();
	return 0;
}

