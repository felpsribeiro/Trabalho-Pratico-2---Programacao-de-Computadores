#include "cor.h"

istream& operator>> (istream& is, enumCor& c) // fun��o para "ensinar" o cout a l� a enumera��o com as cores
{
	int num;
	is >> num;
	c = (enumCor)num;
	return is;
}