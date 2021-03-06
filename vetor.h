#ifndef __VETOR_H__
#define __VETOR_H__

#include <iostream>
using namespace std;

	// Declarações de tipos:

struct registroPol // registro com coordenadas polares
{
	float ang, mag;
};

struct registroCar // registro com coordenadas cartesianas
{
	float px, py;
};

union uniaoVetor // união com coordenadas polares e coordenadas cartesianas
{
	registroPol pol;
	registroCar car;
};

struct registroCoord // registro com as coordenadas atuais da particula
{
	float x, y;
};

	// Protótipos de funções:

registroCoord deslocamento(registroCoord, uniaoVetor, char); // protótipo da função que desloca a particula, somando a posição atual mais o vetor

registroCoord deslocamentoCar(registroCoord, registroCar); // protótipo da função de deslocamento no sistema cartesiano

registroCoord deslocamentoPol(registroCoord, registroPol); // protótipo da função de deslocamento no sistema polar

istream& operator>> (istream&, registroPol&); // protótipo da função para "ensinar" o cout a lê o registro com as cordenadas polares

istream& operator>> (istream&, registroCar&); // protótipo da função para "ensinar" o cout a lê o registro com as cordenadas cartesinas

uniaoVetor inversao(uniaoVetor, char, bool); // protótipo da função para inverter o vetor

#endif