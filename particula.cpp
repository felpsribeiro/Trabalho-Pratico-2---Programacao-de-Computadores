#include "particula.h"
#include "vetor.h"

istream& operator>> (istream& is, registroParticula& n) // função para "ensinar" o cout a lê o registro com as particulas
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

void cortar(char* nome) // função para mostrar apenas o sobrenome da particula
{
	int i = 0;
	while (nome[i] != ' ') { // procura a posição do Space dentro do nome
		++i;
	}
	cout << nome + (i + 1) << " "; // exibi o nome apartir da posição depois do espaço
}