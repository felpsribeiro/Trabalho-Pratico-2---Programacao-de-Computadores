#ifndef __COR_H__
#define __COR_H__

#include <iostream>
using namespace std;

// Declarações de tipos:

enum enumCor { azul, amarelo, branco, vermelho, verde };

// Protótipos de funções:

istream& operator>> (istream&, enumCor&);

#endif