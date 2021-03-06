#include "cor.h"

istream& operator>> (istream& is, enumCor& c) // função para "ensinar" o cout a lê a enumeração com as cores
{
	int num;
	is >> num;
	c = (enumCor)num;
	return is;
}