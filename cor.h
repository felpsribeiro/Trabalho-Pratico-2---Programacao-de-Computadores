#ifndef __COR_H__
#define __COR_H__

#include <iostream>
using namespace std;

// Declara��es de tipos:

enum enumCor { azul, amarelo, branco, vermelho, verde };

// Prot�tipos de fun��es:

istream& operator>> (istream&, enumCor&);

#endif