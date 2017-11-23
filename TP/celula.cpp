#include "stdafx.h"
#include "celula.h"
#include "consola.h"

celula::celula() : letra('0'), cor(0), ser(nullptr), edi(nullptr) {}

char celula::getLetra() const {
	return letra;
}
int celula::getCor() const {
	return cor;
}
Ser * celula::getSer() const
{
	try
	{
		return ser;

	}
	catch (const std::exception&)
	{

	}
}
Edificio * celula::getEdificio() const
{
	try
	{
		return edi;
	}
	catch (const std::exception&)
	{

	}
}
void celula::setLetra(char letra) {
	this->letra = letra;
}
void celula::setCor(int c) {
	cor = c;
}

void celula::setSer(Ser * s)
{
	if (s == nullptr)
	{
		ser = nullptr;
		return;
	}
	if (s->getFlagBandeira() == 1)
	{
		cor = s->getColonia()->getCor();
	}
	else
	{
		cor = Consola::BRANCO;
	}
	ser = s;
	letra = s->getLetra();
	
}

void celula::setEdificio(Edificio * ed)
{
	edi = ed;
}

void celula::limpaCelula()
{
	letra = '0';
	cor = 0;
	ser = nullptr;
	edi = nullptr;
}
