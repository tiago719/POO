#pragma once
#include "ser.h"
#include "Edificio.h"


class celula {
	char letra;
	int cor;
	Ser * ser;
	Edificio * edi;
public:
	celula(); 
	
	char getLetra() const;
	
	int getCor() const;

	Ser * getSer() const;

	Edificio * getEdificio() const;
	
	void setLetra(char letra);
	
	void setCor(int c);

	void setSer(Ser * s);

	void setEdificio(Edificio * ed);

	void limpaCelula();



};