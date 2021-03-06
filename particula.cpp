#include "particula.h"
#include "vetor.h"

istream& operator>> (istream& is, registroParticula& n) // fun��o para "ensinar" o cout a l� o registro com as particulas
{
	is.getline(n.nome,20,':');
	is >> n.atual.x;
	is >> n.atual.y;
	is >> n.sistema;
	if (n.sistema == 'P') {
		is >> n.vetor.pol;
	}
	if (n.sistema == 'C') {
		is >> n.vetor.car;
	}
	is >> n.cor;
	return is;
}

void cortar(char* nome) // fun��o para mostrar apenas o sobrenome da particula
{
	int i = 0;
	while (nome[i] != ' ') { // procura a posi��o do Space dentro do nome
		++i;
	}
	cout << nome + (i + 1) << " "; // exibi o nome apartir da posi��o depois do espa�o
}