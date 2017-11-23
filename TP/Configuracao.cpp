#include "stdafx.h"
#include "Configuracao.h"

Configuracao::Configuracao()
{
	dimX = 0;
	dimY = 0;
	moedas = 0;
	zoom = 1;
	focoX = 0;
	focoY = 0;
	
	//lista_car()->Lista_Caracteristica();
	ListaCar.push_back(new Bandeira());
	ListaCar.push_back(new Superior());
	ListaCar.push_back(new PeleDura());
	ListaCar.push_back(new Armadura());
	ListaCar.push_back(new Faca());
	ListaCar.push_back(new Espada());
	ListaCar.push_back(new Agressao());
	ListaCar.push_back(new Ecologico());
	ListaCar.push_back(new HeatSeeker());
	ListaCar.push_back(new BuildSeeker());
	ListaCar.push_back(new Walker());
	ListaCar.push_back(new Remedio());
	ListaCar.push_back(new SecondChance());
	ListaCar.push_back(new Pistola());


	ListaEd.push_back(new Castelo());
	ListaEd.push_back(new Quinta());
	ListaEd.push_back(new Torre());
}

Configuracao::~Configuracao()
{
	for (int i = 0; i < VecC.size(); i++) {
		VecC[i]->~Colonia();
	}

}

void Configuracao::criaMapa()
{
	mapa = new celula*[dimX];
	for (int i = 0; i < dimY; i++)
	{
		mapa[i] = new celula[dimY];
	}

	VecC.push_back(new Colonia(this));
}

int Configuracao::getZoom() const
{
	return zoom;
}

string Configuracao::getNome() const
{
	return nome_save;
}

void Configuracao::setZoom(int z)
{
	zoom = z;
}

int Configuracao::getFocoX() const
{
	return focoX;
}

void Configuracao::setFocoX(int x)
{
	focoX = x;
}

int Configuracao::getFocoY() const
{
	return focoY;
}

void Configuracao::setFocoY(int y)
{
	focoY = y;
}

celula * Configuracao::getPosMapa(int x, int y)
{
	return &mapa[x][y];
}

void Configuracao::setPosMapa(int x, int y,char c, int cor)
{
	mapa[x][y].setCor(cor);
	mapa[x][y].setLetra(c);
}

/*Lista_Caracteristica Configuracao::getListaCar()
{
	return *lista_car;
}*/

void Configuracao::novoPerfil(char c)
{
	VecP.push_back(new Perfil(c));
}

void Configuracao::novoPerfil_PC(char c)
{
	VecP_PC.push_back(new Perfil(c));
}


int Configuracao::getDimX() const
{
	return dimX;
}

int Configuracao::getDimY() const
{
	return dimY;
}

int Configuracao::getMoedas() const
{
	return moedas;
}

void Configuracao::setDimX(int x)
{
	dimX = x;
}

void Configuracao::setDimY(int y)
{
	dimY = y;
}

void Configuracao::setMoedas(int m)
{
	moedas = m;
}

void Configuracao::setNome(string m)
{
	nome_save = m;
}

void Configuracao::novaColonia()
{
	VecC.push_back(new Colonia(this));
}

int Configuracao::getTamVecC()
{
	return static_cast<int>(VecC.size());
}

Colonia * Configuracao::getColonia(int cor)
{
	for (int i = 0; i < VecC.size(); i++)
	{
		if (VecC[i]->getCor() == cor)
		{
			return VecC[i];
		}
	}
	return nullptr;
}

Colonia * Configuracao::getColoniaPos(int pos)
{
	return VecC[pos];
}

int Configuracao::getTamVecP()
{
	return static_cast<int>(VecP.size());
}

int Configuracao::getTamVecP_PC()
{
	return static_cast<int>(VecP_PC.size());
}


Perfil * Configuracao::getPerfil(char c)
{
	for (int i = 0; i < VecP.size(); i++)
	{
		if (VecP[i]->getLetra() == c)
		{
			return VecP[i];
		}
	}
	cout << "Perfil inexistente" << endl;
	return nullptr;
}
Perfil * Configuracao::getPerfil_PC(char c)
{
	for (int i = 0; i < VecP_PC.size(); i++)
	{
		if (VecP_PC[i]->getLetra() == c)
		{
			return VecP_PC[i];
		}
	}
	cout << "Perfil inexistente" << endl;
	return nullptr;
}

char Configuracao::getLetraPerfil(int a)
{
	return VecP[a]->getLetra();
}

bool Configuracao::eliminaPerfil(char c)
{
	for (int i = 0; i < VecP.size(); i++)
	{
		if (VecP[i]->getLetra() == c)
		{
			delete VecP[i];
			VecP.erase(VecP.begin() + i);
			return true;
		}
	}
	return false;
}

bool Configuracao::verifica()
{
	if (dimX > 0 && dimY > 0 && moedas > 0)
	{
		if (getTamVecP() != 5)
		{
			cout << "Tem de definir 5 perfis antes de continuar" << endl;
			return false;
		}
		return true;
	}
	else
	{
		cout << "Faltam configuracoes essenciais" << endl;
		return false;
	}
}

Caracteristica * Configuracao::getCar(int id)
{
	for (int i = 0; i < ListaCar.size(); i++)
	{
		if (ListaCar[i]->getId() == id)
		{
			return ListaCar[i];
		}
	}
	return nullptr;
}

int Configuracao::getTamLisEd()
{
	return static_cast<int>(ListaEd.size());
}

Edificio * Configuracao::getEd(int a)
{
	for (int i = 0; i < ListaEd.size(); i++)
	{
		if (a == i)
		{
			return ListaEd[i];
		}
	}
	return nullptr;
}

void Configuracao::MoveSer(Ser * s, int xdest, int ydest)
{
	int x, y, x_best, y_best,temp, dist_best = -1;
	x = x_best = s->getCoorX();
	y = y_best = s->getCoorY();

	if (calcula_dist(x, y, xdest, ydest) == 1)//ja esta ao lado
		return;
	int cont = -1;
	if (checkMovimento(x + 1, y, this)) {
		temp = calcula_dist(x + 1, y, xdest, ydest);
		if (temp < dist_best || dist_best < 0) {
			dist_best = temp;
			x_best = x + 1;
			y_best = y;
		}
	}
	if (checkMovimento(x - 1, y, this)) {
		temp = calcula_dist(x - 1, y, xdest, ydest);
		if (temp < dist_best || dist_best < 0) {
			dist_best = temp;
			x_best = x - 1;
			y_best = y;
		}
	}
	if (checkMovimento(x, y + 1, this)) {
		temp = calcula_dist(x, y + 1, xdest, ydest);

		if (temp< dist_best || dist_best < 0) {
			dist_best = temp;
			x_best = x;
			y_best = y + 1;
		}
	}
	if (checkMovimento(x, y - 1, this)) {
		temp = calcula_dist(x, y - 1, xdest, ydest);
		if (temp < dist_best || dist_best < 0) {
			dist_best = temp;
			x_best = x;
			y_best = y - 1;
		}
	}
	if (checkMovimento(x + 1, y + 1, this)) {
		temp = calcula_dist(x + 1, y + 1, xdest, ydest);
		if (temp < dist_best || dist_best < 0) {
			dist_best = temp;
			x_best = x + 1;
			y_best = y + 1;
		}
	}
	if (checkMovimento(x + 1, y - 1, this)) {
		temp = calcula_dist(x + 1, y - 1, xdest, ydest);
		if (temp < dist_best || dist_best < 0) {
			dist_best = temp;
			x_best = x + 1;
			y_best = y - 1;
		}
	}
	if (checkMovimento(x - 1, y + 1, this)) {
		temp = calcula_dist(x - 1, y + 1, xdest, ydest);
		if (temp< dist_best || dist_best < 0) {
			dist_best = temp;
			x_best = x - 1;
			y_best = y + 1;
		}
	}
	if (checkMovimento(x - 1, y - 1, this)) {
		temp = calcula_dist(x - 1, y - 1, xdest, ydest);
		if (temp < dist_best || dist_best < 0) {
			dist_best = temp;
			x_best = x - 1;
			y_best = y - 1;
		}
	}

	if (dist_best < 0)
		;//esta encurralado
	else 
		mudarCoordSer(s, x, y, x_best, y_best, this);

}

void Configuracao::fazMaxSeres(Colonia * c, int i) {
	int cont = 0;
	Perfil * p;
	do {
		p = this->getPerfilId_PC(rand() % this->getTamVecP_PC());

		if (c->getMoedas() > p->getCustoT()){
			c->addSer(p);
			cont = 0;
		}
		else
			cont++;
	} while (cont < 5 && --i > 0);
}


void Configuracao::fazMaxEdificio(Colonia * c, int i) {

	int x, y, cont=0;
	do {

		do {
			//x = rand() % (dimX - 0 + 1) + 0;

			int max = c->getCastelo()->getCoorX() + 10, min = c->getCastelo()->getCoorX() - 10;
			

			x = rand() % (max - min + 1) + min;

		} while (x<0 || x>this->dimX);
		do {
			//y = rand() % (dimY - 0 + 1) + 0;
			int max = c->getCastelo()->getCoorY() + 10, min = c->getCastelo()->getCoorY() - 10;

			y = rand() % (max - min + 1) + min;
		} while (y<0 || y>this->dimY);

		int edRand = rand() % 1;
		if (edRand == 0) {
			char a = this->ListaEd[1]->getLetra();

			if (c->getMoedas() > this->ListaEd[1]->getCusto()) {
				char a = this->ListaEd[1]->getLetra();
				c->addEdif(x, y, this->ListaEd[1]->getLetra());
				
			}
			else if (c->getMoedas() > this->ListaEd[2]->getCusto())
			{
				c->addEdif(x, y, this->ListaEd[2]->getLetra());
			}
		}
		else {
			if (c->getMoedas() > this->ListaEd[2]->getCusto())
			{
				c->addEdif(x, y, this->ListaEd[2]->getLetra());
			}

			else if (c->getMoedas() > this->ListaEd[1]->getCusto()) 
			{
				c->addEdif(x, y, this->ListaEd[1]->getLetra());
			}
			
		}
	} while (cont < 5 && --i > 0);

}




void Configuracao::novaIteracao()
{
	int ra;
	for (int i = 1; i < VecC.size(); i++)
	{

		ra = rand() % 1;

		if (ra == 0) {
			int numSeres=VecC[i]->getTamSer();
			if (numSeres == 0) {
				fazMaxSeres(VecC[i], 1);
			}
			if (VecC[i]->getMoedas() > 50) {
				fazMaxEdificio(VecC[i], 1);

			}
			else if (VecC[i]->getMoedas() > 20) {
				fazMaxSeres(VecC[i], 1);


			}
		}
		else if (ra == 1) {
			if (VecC[0]->getTamSer() > VecC[i]->getTamSer())
				fazMaxSeres(VecC[i], VecC[0]->getTamSer() - VecC[i]->getTamSer());
			if (VecC[0]->getTamEdificio() > VecC[i]->getTamEdificio())
				fazMaxEdificio(VecC[i], VecC[0]->getTamEdificio() - VecC[i]->getTamEdificio());

		}

		if (VecC[i]->getTamSer() > VecC[0]->getTamSer() * 0.8)
			VecC[i]->setFlagAtaca(true);
		else {
			VecC[i]->setFlagAtaca(false);
			fazMaxSeres(VecC[i], 100);

		}

/*

		if (VecC[i]->getTamSer() == 0) {
			int a = rand() % VecP.size();
			VecC[i]->addSer(VecP[a]);
		}*/
	}

	
	for (int i = 0; i < VecC.size(); i++)
	{
		VecC[i]->nova_iteracao_edif();
	}

	for (int i = 0; i < VecC.size(); i++)
	{
		VecC[i]->nova_iteracao_ser();
	}

	for (int i = 0; i < VecC.size(); i++)
	{
		VecC[i]->nova_iteracao_mortos();
	}

	for (int i = 0; i < VecC.size(); i++)
	{
		if (VecC[i]->getTamEdificio() == 0 && VecC[i]->getTamSer() == 0)
		{
			VecC[i]->~Colonia();
			VecC.erase(VecC.begin() + i);
		}
	}
	
}

bool Configuracao::verifFim()
{
	if (VecC.size() == 0)
	{
		cout << "Foram eliminadas varias colonias na mesma iteracao. O jogo termina sem vencedores!" << endl;
		return true;

	}

	else if (VecC.size() == 1)
	{
		cout << "A colonia " << VecC[0]->getCor() << " e a vencedora" << endl;
		return true;

	}
	return false;
}

Perfil * Configuracao::getPerfilId(int x)
{
	return VecP[x];
}
Perfil * Configuracao::getPerfilId_PC(int x)
{
	return VecP_PC[x];
}

void Configuracao::mudarCoordSer(Ser * s, int x, int y, int xnovo, int ynovo, Configuracao * conf) {
	if (conf->mapa[xnovo][ynovo].getLetra() == 'C')
	{
		conf->mapa[x][y].limpaCelula();
		conf->mapa[xnovo][ynovo].setSer(s);
		conf->mapa[xnovo][ynovo].setLetra('C');
	}

	else if (conf->mapa[x][y].getLetra() != 'C')
	{
		conf->mapa[x][y].limpaCelula();
		conf->mapa[xnovo][ynovo].setSer(s);
	}	
	else
	{
		conf->mapa[xnovo][ynovo].setSer(s);
	}
	s->setX(xnovo);
	s->setY(ynovo);
}

Edificio * Configuracao::getEdbyLetra(char l)
{
	for (int i = 0; i < ListaEd.size(); i++)
	{
		if (ListaEd[i]->getLetra() == l)
		{
			return ListaEd[i];
		}
	}
	return nullptr;
}

int Configuracao::getTamListaCar()
{
	return static_cast<int>(ListaCar.size());
}

Ser * Configuracao::SerVizinho(Colonia * col,int x, int y, int a)
{
	vector<Ser *> s;
	for (int i = 1; i <= a; i++) {
		if (mapa[x - i][y - i].getSer() != nullptr && mapa[x - i][y - i].getSer()->getColonia()!=col)
			s.push_back(mapa[x - i][y - i].getSer());
		if (mapa[x][y - i].getSer() != nullptr && mapa[x][y - i].getSer()->getColonia() != col)
			s.push_back(mapa[x][y - i].getSer());
		if (mapa[x + i][y - i].getSer() != nullptr && mapa[x + i][y - i].getSer()->getColonia() != col)
			s.push_back(mapa[x + i][y - i].getSer());
		if (mapa[x - i][y].getSer() != nullptr && mapa[x - i][y].getSer()->getColonia() != col)
			s.push_back(mapa[x - i][y].getSer());
		if (mapa[x + i][y].getSer() != nullptr && mapa[x + i][y].getSer()->getColonia() != col)
			s.push_back(mapa[x + i][y].getSer());
		if (mapa[x + i][y + i].getSer() != nullptr && mapa[x + i][y + i].getSer()->getColonia() != col)
			s.push_back(mapa[x + i][y + i].getSer());
		if (mapa[x][y + i].getSer() != nullptr && mapa[x][y + i].getSer()->getColonia() != col)
			s.push_back(mapa[x][y + i].getSer());
		if (mapa[x - i][y + i].getSer() != nullptr && mapa[x - i][y + i].getSer()->getColonia() != col)
			s.push_back(mapa[x - i][y + i].getSer());
	}
	
	if (s.size() == 0)
		return nullptr;
	else return s[rand() % s.size()];

}

Edificio * Configuracao::EdificioVizinho(Ser * ser,int x, int y)
{
	vector<Edificio *> s;
	if (mapa[x - 1][y - 1].getEdificio() != nullptr && ser->getColonia()!=mapa[x-1][y-1].getEdificio()->getColonia())
		s.push_back(mapa[x - 1][y - 1].getEdificio());
	if (mapa[x][y - 1].getEdificio() != nullptr && ser->getColonia() != mapa[x][y - 1].getEdificio()->getColonia())
		s.push_back(mapa[x][y - 1].getEdificio());
	if (mapa[x + 1][y - 1].getEdificio() != nullptr && ser->getColonia() != mapa[x + 1][y - 1].getEdificio()->getColonia())
		s.push_back(mapa[x + 1][y - 1].getEdificio());
	if (mapa[x - 1][y].getEdificio() != nullptr && ser->getColonia() != mapa[x - 1][y].getEdificio()->getColonia())
		s.push_back(mapa[x - 1][y].getEdificio());
	if (mapa[x + 1][y].getEdificio() != nullptr && ser->getColonia() != mapa[x + 1][y].getEdificio()->getColonia())
		s.push_back(mapa[x + 1][y].getEdificio());
	if (mapa[x+1][y+1].getEdificio() != nullptr && ser->getColonia() != mapa[x + 1][y + 1].getEdificio()->getColonia())
		s.push_back(mapa[x + 1][y + 1].getEdificio());
	if (mapa[x][y + 1].getEdificio() != nullptr && ser->getColonia() != mapa[x][y + 1].getEdificio()->getColonia())
		s.push_back(mapa[x][y + 1].getEdificio());
	if (mapa[x - 1][y + 1].getEdificio() != nullptr && ser->getColonia() != mapa[x - 1][y + 1].getEdificio()->getColonia())
		s.push_back(mapa[x - 1][y + 1].getEdificio());

	if (s.size() == 0)
		return nullptr;
	else 
		return s[rand() % s.size()];

}

bool Configuracao::checkMovimento(int x, int y, Configuracao * conf)
{
	if (conf->mapa[x][y].getEdificio() != nullptr || conf->mapa[x][y].getSer() != nullptr)
		return false;
	return true;
}

int Configuracao::calcula_dist(int x, int y, int xdest, int ydest)
{
	int cont = 0;
	do {
		if (x < xdest)
			x = x + 1;
		else if (x > xdest)
			x = x - 1;

		if (y < ydest)
			y = y + 1;
		else if(y > ydest)
			y = y - 1;
		cont++;
	} while (x != xdest || y != ydest);
	return cont;
}

void Configuracao::ser_edif(Ser * a, Edificio * b)
{
	for (int i = 0; i < a->getTamCarM(); i++) {
		if (a->getCarM(i)->getFlag() && a->getCarM(i)->getId() == 6)
			a->setAtaqueBonus(3);

	}
	if (a->getAtaque() > getEdbyLetra( b->getLetra())->getDefesa())
	{
		b->setSaude(b->getSaude() - (a->getAtaque() - getEdbyLetra(b->getLetra())->getDefesa()));
	}
	else
	{
		a->setVidaAtual(a->getVidaAtual() - 1);
	}
}

void Configuracao::ser_ser(Ser * a, Ser * b)
{
	for (int i = 0; i < a->getTamCarM(); i++) {
		if (a->getCarM(i)->getFlag() && a->getCarM(i)->getId() == 6){
			a->setAtaqueBonus(3);
			a->getCarM(i)->setContEspada(-1);
		}

	}
	if (a->getAtaque() > b->getDefesa())
	{
		b->setVidaAtual(b->getVidaAtual() - (a->getAtaque() - b->getDefesa()));
	}
	else
	{
		a->setVidaAtual(a->getVidaAtual() - 1);
	}
}

void Configuracao::edif_ser(Edificio * a, Ser * b)
{
	if (getEdbyLetra(a->getLetra())->getAtaque() > b->getDefesa())
	{
		b->setVidaAtual(b->getVidaAtual() - (getEdbyLetra(a->getLetra())->getAtaque() - b->getDefesa()));
	}
	else
	{
		a->setSaude(a->getSaude() - 1);
	}
}

void Configuracao::copia(Configuracao * c) {
	this->dimX = c->dimX;
	this->dimY = c->dimY;
	this->focoX = c->focoX;
	this->focoY = c->focoY;
	this->zoom = c->zoom;
	this->moedas = c->moedas;

	this->criaMapa();
	Colonia * novaC;
	for (int i = 0; i < c->VecC.size(); i++) {//colonias
		if(i!=0){
			novaC = new Colonia(this);
			this->VecC.push_back(novaC);
		}
		else
			novaC = VecC[0];
		//vector<Colonia *> novo;
		int tam = VecC[i]->getTamEdificio();
		for (int o = 0; o <  tam; o++) {//edificio
			Edificio * edAnt = c->VecC[i]->getEdificio(o);
			Edificio * novoE = edAnt;

			novoE->copiaNovo(edAnt);

			novaC->addEdifVec(novoE);

			//novaC->addEdif(edAnt->getCoorX(), edAnt->getCoorY(), edAnt->getLetra());

			//memcpy(novoE, edAnt, sizeof(Edificio));

		}
		tam = VecC[i]->getTamSer();
		for (int o = 0; o < tam; o++) {//seres
			Ser * edAnt = c->VecC[i]->getSer(o);
			Ser * novoE = edAnt;

			vector <Caracteristica *> carM;
			for (int z = 0; z < edAnt->getTamCarM(); i++) {
				carM.push_back(edAnt->getCarM(i));
			}

			novoE->copia(edAnt, novaC, &carM);
			novaC->addSerfVec(novoE);

			//memcpy(novoE, edAnt, sizeof(Edificio));

		}

	}

	for (int i = 0; i < c->VecP.size(); i++) {//perfil
		Perfil * novaC = new Perfil(c->getPerfilId(i)->getLetra());
		this->VecP.push_back(novaC);
		for (int o = 0; o < c->getTamVecP(); o++) {
			novaC->addCar(c->VecP[i]->getCaracteristica(o)->getId(), this);
		}
	}

	for (int i = 0; i < VecC.size(); i++) {//perfil
		for (int o = 0; o < VecC[i]->getTamSer(); o++) {
			Ser * s = VecC[i]->getSer(o);
			celula * cel = &mapa[s->getCoorX()][s->getCoorY()];
			cel->setSer(s);
			cel->setEdificio(nullptr);
			cel->setLetra(s->getLetra());
			cel->setCor(s->getColonia()->getCor());
		}
		for (int o = 0; o < VecC[i]->getTamEdificio(); o++) {
			Edificio * s = VecC[i]->getEdificio(o);
			celula * cel = &mapa[s->getCoorX()][s->getCoorY()];
			cel->setSer(nullptr);
			cel->setEdificio(s);
			cel->setLetra(s->getLetra());
			cel->setCor(s->getColonia()->getCor());
		}

	}
	//TODO: falta atualizar o mapa todo

}

