#ifndef __VETOR_H__
#define __VETOR_H__

#include <iostream>
using namespace std;

	// Declara��es de tipos:

struct registroPol // registro com coordenadas polares
{
	float ang, mag;
};

struct registroCar // registro com coordenadas cartesianas
{
	float px, py;
};

union uniaoVetor // uni�o com coordenadas polares e coordenadas cartesianas
{
	registroPol pol;
	registroCar car;
};

struct registroCoord // registro com as coordenadas atuais da particula
{
	float x, y;
};

	// Prot�tipos de fun��es:

registroCoord deslocamento(registroCoord, uniaoVetor, char); // prot�tipo da fun��o que desloca a particula, somando a posi��o atual mais o vetor

registroCoord deslocamentoCar(registroCoord, registroCar); // prot�tipo da fun��o de deslocamento no sistema cartesiano

registroCoord deslocamentoPol(registroCoord, registroPol); // prot�tipo da fun��o de deslocamento no sistema polar

istream& operator>> (istream&, registroPol&); // prot�tipo da fun��o para "ensinar" o cout a l� o registro com as cordenadas polares

istream& operator>> (istream&, registroCar&); // prot�tipo da fun��o para "ensinar" o cout a l� o registro com as cordenadas cartesinas

uniaoVetor inversao(uniaoVetor, char, bool); // prot�tipo da fun��o para inverter o vetor

#endif