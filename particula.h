#ifndef __PARTICULA_H__
#define __PARTICULA_H__

#include <iostream>
#include "vetor.h"
#include "cor.h"
using namespace std;

// Declara��es de tipos:

struct registroParticula
{
	char nome[20];
	registroCoord atual;
	char sistema;
	uniaoVetor vetor;
	enumCor cor;
};

struct registroResultado 
{
	int quantParticulas = 0;
	registroParticula* particulas[10];
	int distanciaPassos = 1;
};

// Prot�tipos de fun��es:

istream& operator>> (istream&, registroParticula&);

void cortar(char* nome);

#endif