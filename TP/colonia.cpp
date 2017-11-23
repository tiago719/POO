#include "stdafx.h"
#include "colonia.h"
#include "celula.h"
#include "Consola.h"

int Colonia::cont = 1;

Colonia::Colonia(Configuracao * conf)
{
	this->conf = conf;
	int a, b;
	idEd =0;
	cor = cont++;
	do
	{
		a = rand() % conf->getDimX();
		b = rand() % conf->getDimY();
	} while (conf->getPosMapa(a, b)->getLetra() != '0');
	Edificio * novo = new Castelo(this, a, b, idEd);
	ed.push_back(novo);
	idEd++;
	conf->setPosMapa(a, b, 'C', cor);
	conf->getPosMapa(a, b)->setEdificio(novo);
	flag_ataca = 0;
	flag_recolhe = 0;
}

Colonia::~Colonia()
{
	for (int i = 0; i < this->se.size(); i++) {
		se[i]->~Ser();
		se.erase(se.begin() + i);
	}
	for (int i = 0; i < this->ed.size(); i++) {
//		ed[i].~Edificio();
		ed.erase(ed.begin() + i);
	}

}

bool Colonia::getFlagAtaca()
{
	return flag_ataca;
}

void Colonia::setFlagAtaca(bool f)
{
	flag_ataca = f;
}

bool Colonia::getFlagRecolhe()
{
	return flag_recolhe;
}

void Colonia::setFlagRecolhe(bool f)
{
	flag_recolhe = f;
}

int Colonia::getCoorxSer(int id) const
{
	return se[id]->getCoorX();
}

int Colonia::getCoorySer(int id) const
{
	return se[id]->getCoorY();
}

int Colonia::getCoorxEd(int id) const
{
	return ed[id]->getCoorX();
}

int Colonia::getCooryEd(int id) const
{
	return ed[id]->getCoorY();
}

void Colonia::iniciarCastelo() {
	int x, y;
	do {
		x = rand() % conf->getDimX();
		y = rand() % conf->getDimY();
	} while(conf->getPosMapa(x,y)->getLetra() != '0');
	conf->getPosMapa(x, y)->setLetra('C');
	conf->getPosMapa(x, y)->setCor(this->cor);
	setCoorCasteloX(x);
	setCoorCasteloY(y);
}

ostream& operator<<(ostream &o, Edificio * e)
{
	ostringstream s;

	e->toString(s);

	o << s.str();

	return o;
}

ostream& operator<<(ostream &o, Ser &ser)
{
	ostringstream s;

	ser.toString(s);

	o << s.str();

	return o;
}

string Colonia::toString() const {
	ostringstream os;

	cout << "Colonia: " << cor << endl;
	cout << "Lista de Edeficios: " << endl;

	for (int i = 0; i < ed.size(); i++)
	{
		cout << ed[i] << endl;
	}
	
	cout << "Lista de Seres: " << endl;
	for (int i = 0; i < se.size(); i++)
	{
		cout << *se[i] << endl;
	}
	return os.str();
}

int Colonia::getCor() const
{
	return cor;
}

Edificio * Colonia::getCastelo() const
{
	return ed[0];
}

int Colonia::getMoedas() const
{
	return moedas;
}

bool Colonia::mudarCoorCastelo(int x, int y)
{
	
	bool flag = ed[0]->mudarCoord(x, y, conf, this);
	if (!flag)
		cout << "Nao foi possivel mudar o castelo para as coordenadas dadas" << endl;
	return flag;
}

bool Colonia::addSer(Perfil * p)
{
	if (getCastelo()->getLetra() == 'C')
	{
		if (moedas >= p->getCustoT())
		{
			moedas -= p->getCustoT();
			Ser * novo = new Ser(p, this, conf, getCastelo()->getCoorX(), getCastelo()->getCoorY(), Consola::BRANCO);
			se.push_back(novo);
			return true;		
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Nao pode construir seres sem castelo" << endl;
		return 0;
	}
}

Edificio * Colonia::getEdificio(int i)
{
	return ed[i];
}

int Colonia::getTamEdificio()
{
	return static_cast<int>(ed.size());
}

Ser * Colonia::getSer(int i)
{
	return se[i];
}

int Colonia::getTamSer()
{
	return static_cast<int>(se.size());
}

void Colonia::setMoedas(int num) {
	moedas = num;
}

void Colonia::setCoorCasteloX(int num)
{
	ed[0]->setCoorX(num);
}

void Colonia::setCoorCasteloY(int num)
{
	ed[0]->setCoorY(num);
}

void Colonia::alteraMoedas(int num) {
	moedas += num;
}

void Colonia::colocaCasteloMapa()
{
	conf->getPosMapa(ed[0]->getCoorX(), ed[0]->getCoorY())->setCor(cor);
	conf->getPosMapa(ed[0]->getCoorX(), ed[0]->getCoorY())->setCor(cor);
}

bool Colonia::addEdif(int x, int y, char letra)
{
	if (getCastelo()->getLetra() == 'C')
	{
		if (conf->getPosMapa(x, y)->getLetra() == '0')
		{
			if (abs(x - getCastelo()->getCoorX()) < 11 && abs(y - getCastelo()->getCoorY() < 11))
			{
				for (int i = 0; i < conf->getTamLisEd(); i++)
				{
					if (conf->getEd(i)->getLetra() == letra)
					{
						switch (i)
						{
						case 0:
						{
							cout << "A colonia ja possui um castelo" << endl;
							return false;
						}
						case 1:
							if (conf->getEd(i)->getCusto() < moedas)
							{
								moedas -= conf->getEd(i)->getCusto();
								Edificio * novo = new Quinta(this, x, y, idEd);
								ed.push_back(novo);
								idEd++;
								conf->getPosMapa(x, y)->setLetra('Q');
								conf->getPosMapa(x, y)->setCor(cor);
								conf->getPosMapa(x, y)->setEdificio(novo);
								return true;
							}
							else
							{
								cout << "A colonia nao tem moedas suficientes" << endl;
								return false;
							}
						case 2:
							if (conf->getEd(i)->getCusto() < moedas)
							{
								moedas -= conf->getEd(i)->getCusto();
								Edificio * novo = new Torre(this, x, y, idEd);
								ed.push_back(novo);
								idEd++;
								conf->getPosMapa(x, y)->setLetra('T');
								conf->getPosMapa(x, y)->setCor(cor);
								conf->getPosMapa(x, y)->setEdificio(novo);
								return true;
							}
							else
							{
								cout << "A colonia nao tem moedas suficientes" << endl;
								return false;
							}
						}
					}
				}
			}
			else
			{
				cout << "O edificio deve estar a menos de 10 posicoes de distancia do castelo" << endl;
				return false;
			}

		}
		else
		{
			cout << "Posicao ocupada" << endl;
			return false;
		}
	}

	else
	{
		cout << "Nao pode construir edificios sem castelo" << endl;
		return false;
	}
	return false;
}

bool Colonia::sellEdif(int eid)
{
	if (ed[eid]->sell(this, conf) == 1)
	{
		ed.erase(ed.begin() + eid);
		for (int i = 0; i < ed.size(); i++)
		{
			ed[i]->setIdEd(i);
		}
		return 1;
	}

	return 0;
}

void Colonia::nova_iteracao_edif()
{
	for (int i = 0; i < ed.size(); i++)
	{
		ed[i]->novaIteracao(this, conf);
	}
}

void Colonia::nova_iteracao_ser()
{
	for (int i = 0; i < se.size(); i++) 
	{
		se[i]->novaJogada(conf);
		if (se[i]->getCoorX() == getCastelo()->getCoorX() && se[i]->getCoorY() == getCastelo()->getCoorY())
		{
			setMoedas(getMoedas() + 1);
			if (se[i]->getVidaAtual() < se[i]->getVidaMax())
			{
				se[i]->setVidaAtual(se[i]->getVidaAtual() + 1);
			}
		}

	}
}

void Colonia::nova_iteracao_mortos()
{
	for (int i = 0; i < ed.size(); i++)
	{
		if (ed[i]->getSaude() <= 0)
		{
			conf->setPosMapa(ed[i]->getCoorX(), ed[i]->getCoorY(), '0', 0);
			conf->getPosMapa(se[i]->getCoorX(), se[i]->getCoorY())->setEdificio(nullptr);
			ed[i]->~Edificio();
		}
	}

	for (int i = 0; i < se.size(); i++)
	{
		if (se[i]->getVidaAtual() <= 0)
		{
			if (se[i]->getCar(13) != nullptr)
			{
				if (se[i]->getCar(13)->getFlag() == 0)
				{
					se[i]->getCar(13)->setFlag(1);
					conf->setPosMapa(se[i]->getCoorX(), se[i]->getCoorY(), '0', 0);
					conf->getPosMapa(se[i]->getCoorX(), se[i]->getCoorY())->setSer(nullptr);
				}
				else
				{
					conf->setPosMapa(se[i]->getCoorX(), se[i]->getCoorY(), '0', 0);
					conf->getPosMapa(se[i]->getCoorX(), se[i]->getCoorY())->setSer(nullptr);
					se[i]->~Ser();
				}
			}	
			else
			{
				conf->setPosMapa(se[i]->getCoorX(), se[i]->getCoorY(), '0', 0);
				conf->getPosMapa(se[i]->getCoorX(), se[i]->getCoorY())->setSer(nullptr);
				se[i]->~Ser();
			}
		}
		
	}
}

int Colonia::procuraSer(Ser * s)
{
	for (int i = 0; i < se.size(); i++) {
		if (se[i] == s)
			return i;
	}
	return -1;
}

void Colonia::removeSer(Ser * s)
{
	conf->getPosMapa(s->getCoorX(), s->getCoorY())->limpaCelula();
	int a = procuraSer(s);
	if (a != -1)
		se.erase(se.begin() + procuraSer(s));
}

int Colonia::procuraEd(Edificio * e)
{
	for (int i = 0; i < ed.size(); i++) {
		if (ed[i] == e)
			return i;
	}
	return -1;
}

void Colonia::removeEd(Edificio * e)
{
	int a = procuraEd(e);
	if (a != -1)
	{
		ed.erase(ed.begin() + procuraEd(e));
	}
}

void Colonia::addEdifVec(Edificio * c)
{
	this->ed.push_back(c);
}

void Colonia::addSerfVec(Ser * c)
{
	this->se.push_back(c);

}

