#include "stdafx.h"
#include "colonia.h"

void Edificio::toString(ostringstream & os) const
{
	os << "Edificio: " << nome << "\t Eid: " << idEd << "\t Nivel: " << nivel << "\t coorX: " << x << " coorY: " << y << "\t Saude: " << saude << "\t Ataque: " << ataque << "\t Defesa: " << defesa << endl;
}

void Edificio::repara(Colonia * col, Configuracao * conf)
{
	int c = conf->getEdbyLetra(getLetra())->getCusto()*(conf->getEdbyLetra(getLetra())->getSaude() - getSaude()) / conf->getEdbyLetra(getLetra())->getSaude();
	if (col->getMoedas() > c) 
	{
		col->setMoedas(col->getMoedas() - c);
		setSaude(getSaudeInicial());
		return;
	}
	else
	{
		cout << "A colonia nao possui moedas suficientes" << endl;
		return;
	}
}

void Edificio::copia(Edificio * c)
{
	this->ataque = c->ataque;
	this->col = c->col;
	this->custo = c->custo;
	this->defesa = c->defesa;
	this->idEd = c->idEd;
	this->letra = c->letra;
	this->nivel = c->nivel;
	this->nome = c->nome;
	this->saude = c->saude;
	this->saude_inicial = c->saude_inicial;
	this->x = c->x;
	this->y= c->y;
}





Colonia * Edificio::getColonia()
{
	return col;
}

Castelo::Castelo(Colonia * c,int coorX, int coorY, int idEd) : Edificio(c,50, 10, 'C', coorX, coorY, idEd) {}

Castelo::Castelo() : Edificio('C', 0, 50, 10, 0) {}

Quinta::Quinta(Colonia * c,int coorX, int coorY, int idEd) : Edificio(c,20, 10,'Q', coorX, coorY, idEd) {}

Quinta::Quinta() : Edificio('Q', 20, 20, 10, 0) {}

Torre::Torre(Colonia * c,int coorX, int coorY, int idEd) : Edificio(c,20, 10, 'T', coorX, coorY, idEd) {}

Torre::Torre() : Edificio('T', 30, 20, 10, 3) {}

Edificio::Edificio(Colonia * c,int s, int d, char l, int coorX, int coorY, int id):col(c), letra(l), x(coorX), y(coorY), saude(s), defesa(d), nivel(0), idEd(id)
{
	if (letra == 'C')
	{
		nome = "Castelo";
	}
	else
		if (letra == 'Q')
		{
			nome = "Quinta";
		}
		else
			if (letra == 'T')
			{
				nome = "Torre";
			}
}

Edificio::Edificio(char l, int c, int s, int d, int a): letra(l), saude(s), defesa(d), custo(c), ataque(a) {}

Edificio::~Edificio()
{
	col->removeEd(this);
}

int Edificio::getIdEd() const
{
	return idEd;
}

void Edificio::setIdEd(int a)
{
	idEd = a;
}

int Edificio::getCoorX() const
{
	return x;
}

int Edificio::getCoorY() const
{
	return y;
}

void Edificio::setCoorX(int a)
{
	x = a;
}

void Edificio::setCoorY(int b)
{
	y=b;
}

void Edificio::atVida(int b)
{
	saude += b;
}

int Edificio::getCusto() const
{
	return custo;
}

int Edificio::getSaude() const
{
	return saude;
}

void Edificio::setSaude(int s)
{
	saude = s;
}

int Edificio::getSaudeInicial() const
{
	return saude_inicial;
}

char Edificio::getLetra() const
{
	return letra;
}

int Edificio::getNivel() const
{
	return nivel;
}

void Edificio::setNivel(int n)
{
	nivel = n;
}

int Edificio::getDefesa()
{
	return defesa;
}

void Edificio::setDefesa(int d)
{
	defesa = d;
}

int Edificio::getAtaque()
{
	return ataque;
}

void Edificio::setAtaque(int a)
{
	ataque = a;
}

bool Castelo::mudarCoord(int x, int y, Configuracao * conf, Colonia * c)
{
	if (conf->getPosMapa(x,y)->getLetra() == '0') 
	{
		conf->setPosMapa(getCoorX(), getCoorY(), '0', 0);
		conf->setPosMapa(x, y, 'C', c->getCor());
		setCoorX(x);
		setCoorY(y);
		return true;
	}
	else {
		return false;
	}
}

bool Castelo::upgrade(Colonia * col)
{
	cout << "O castelo nao pode ser melhorado" << endl;
	return 0;
}


void Castelo::novaIteracao(Colonia * col, Configuracao * conf)
{
}

bool Castelo::sell(Colonia * col, Configuracao * conf)
{
	cout << "O catelo nao pode ser vendido" << endl;
	return false;
}

bool Quinta::mudarCoord(int x, int y, Configuracao * conf, Colonia * c)
{
	return false;
}

bool Quinta::upgrade(Colonia * col)
{
	if (col->getMoedas() >= 10)
	{
		col->setMoedas(col->getMoedas() - 10);
		setNivel(getNivel() + 1);
		setDefesa(getDefesa() + 1);
		return 1;
	}
	else
	{
		cout << "A colonia nao tem moedas suficientes" << endl;
		return 0;
	}
}
void Quinta::novaIteracao(Colonia * col, Configuracao * conf)
{
	col->setMoedas(col->getMoedas() + getNivel() + 2);
}
bool Quinta::sell(Colonia * col, Configuracao * conf)
{
	col->setMoedas(col->getMoedas() + (conf->getEdbyLetra('Q')->getCusto() / 2) + (getNivel() * 10)/2);
	conf->setPosMapa(getCoorX(), getCoorY(), '0', 0);
	return 1;
}

bool Torre::mudarCoord(int x, int y, Configuracao * conf, Colonia * c) 
{ 
	return false;
}

bool Torre::upgrade(Colonia * col)
{
	if (col->getMoedas() >= 10)
	{
		col->setMoedas(col->getMoedas() - 10);
		setNivel(getNivel() + 1);
		setAtaque(getAtaque() + 1);
		setDefesa(getDefesa() + 2);
		return 1;
	}
	else
	{
		cout << "A colonia nao tem moedas suficientes" << endl;
		return 0;
	}
}

void Torre::novaIteracao(Colonia * col, Configuracao * conf)
{
	Ser * s = conf->SerVizinho(col,this->x, this->y, 2);
	if (s != nullptr) {
		conf->edif_ser(this, s);
	}
}

bool Torre::sell(Colonia * col, Configuracao * conf)
{
	col->setMoedas(col->getMoedas() + (conf->getEdbyLetra('T')->getCusto() / 2) + (getNivel() * 10)/2);
	conf->setPosMapa(getCoorX(), getCoorY(), '0', 0);
	return 1;
}

Edificio * Castelo::copiaNovo(Edificio * c) {
	Castelo * a = new Castelo();
	a->copia(c);
	return a;
}

Edificio * Quinta::copiaNovo(Edificio * c) {
	Quinta * a = new Quinta();
	a->copia(c);
	return a;
}

Edificio * Torre::copiaNovo(Edificio * c) {
	Torre * a = new Torre();
	a->copia(c);
	return a;
}



/*Edificio::~Edificio() {
	col->removeEd(this);
}*/
