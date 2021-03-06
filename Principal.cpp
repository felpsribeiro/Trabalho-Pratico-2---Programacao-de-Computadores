#include <iostream>
#include "particula.h"
#include "vetor.h"
#include "cor.h"
#include <random>
using namespace std;

int main()
{
	system("chcp 1252 >nul");

	int i,h; // v�riaveis auxiliares que seram usadas dentro dos la�os de repeti��o
	registroParticula particula[10]; //declara��o do vetor de registro que guardar� as particulas

/* Exemplo de entrada para 10 particulas:
Alan Turing: 790 101 P 40.0 20.0 0
Ada Lovelace: 480 76 P 138.0 25.0 1
Donald Knuth: 210 563 C 19.0 23.2 2
Peter Naur: 451 421 P 284.0 30.0 3
Ken Thompson: 630 46 C -22.1 14.3 4
Von Neumann: 100 500 P 89.0 17.9 0
Dennis Ritchie: 58 325 C 28.0 -25.0 1
Bjarne Stroustrup: 128 211 C -24.5 -25.9 2
Brian Kernighan: 2 182 C 35.5 2.6 3
Leslie Lamport: 737 555 P 149.0 18.2 4

*/

	for (i = 0; i < 10; ++i) { // l� as 10 particulas
		cin >> particula[i];
		cin.get();
	}

	cout << "\nSimula��o\n---------\n";

	random_device rand; 

	int passoComColisao = 0; // variavel que guarda o n�mero de passos com colis�es
	int passos = 0; // variavel que guarda o n�mero total de passos
	int a; // varaiavel que guarda o valor do primeiro sorteio
	int b; // varaiavel que guarda o valor do segundo sorteio
	registroResultado resultado[100]; // registro que guarda as informa��es dos passos que houveram coli�es
	int totalColisoes = 0; //armazena o n�mero total de colis�es

	while (!resultado[99].quantParticulas) { // enquanto o (registro)resultado de n� 100 tiver a quant de colis�es igual a 0, se repete o la�o 
		++passos; // indica a passagem do passo

		a = (rand() % 10) + 1; // gera o primeiro n� aleat�rio que representa a quant de particulas q seram alteradas de posi��o

		cout << "#" << passos << ": " << a << " ( ";

		registroParticula* * enderecos = new registroParticula* [a]; // cria um rgistro din�mico de ponteiros que armazenaram os endere�os das particulas alteradas

		for (i = 0; i < a; ++i) { // altera a posi��o de a (primeiro n� sorteado) particulas 
			b = rand() % 10; // sorteia a particula de 0 a 9 que ter� a posi��o alterada

			cout << b << " ";

			enderecos[i] = &particula[b]; // guarda o endere�o da particula sorteada
			enderecos[i]->atual = deslocamento(enderecos[i]->atual, enderecos[i]->vetor, enderecos[i]->sistema); // altera o valor da posi��o da particula

			if (particula[b].atual.x >= 800 || particula[b].atual.x <= 0 || particula[b].atual.y >= 600 || particula[b].atual.y <= 0) { // se a nova posi��o gerou alguma colis�o
				if (particula[b].atual.x >= 800 || particula[b].atual.x <= 0) { //se colidiu nas laterais
					enderecos[i]->vetor = inversao(enderecos[i]->vetor, enderecos[i]->sistema, true); // altera o vetor da particula para ela voltar para o espa�o de confinamento
					++totalColisoes; // registra que houve colis�o
				}
				if (particula[b].atual.y >= 600 || particula[b].atual.y <= 0) { //se colidiu em cima ou baixo
					enderecos[i]->vetor = inversao(enderecos[i]->vetor, enderecos[i]->sistema, false); // altera o vetor da particula para ela voltar para o espa�o de confinamento
					++totalColisoes; // registra que houve colis�o
				}
				resultado[passoComColisao].particulas[resultado[passoComColisao].quantParticulas] = &particula[b]; // salva o endere�o da particula que houve a colis�o
				++resultado[passoComColisao].quantParticulas; // soma uma colis�o no determinado (registro)resultado
			}
		}

		if (resultado[passoComColisao].quantParticulas) { // se tiver ocorrido alguma colis�o
			cout << ") = " << resultado[passoComColisao].quantParticulas << " ( ";
			
			for (i = 0; i < resultado[passoComColisao].quantParticulas; ++i)
				cortar(resultado[passoComColisao].particulas[i]->nome); // exibi o sobrenome da particula
			cout << ")\n";

			++passoComColisao; // no pr�ximo ciclo de repeti��o, os resultados seram guardados no pr�ximo (registro)resultado
		}

		else { // se n�o tiver ocorrido nenhuma colis�o
			cout << ") = 0\n"; 
			++resultado[passoComColisao].distanciaPassos; // se n�o houve colis�o, aumenta a dist�ncia entre uma colis�o e outra
		}

		delete[] enderecos; // apaga a mem�ria din�mica utilizada
	}
	// apresenta os resultados 

	cout << fixed;
	cout.precision(6);
	
	cout << "\nResultados\n----------\n"
		<< "Colis�es: " << totalColisoes << endl // total de colis�es
		<< "Colis�es por passo: " << float(totalColisoes) / passos << endl // n� m�dio de particulas que colidiram a cada passo
		<< "M�dia de passos entre as colis�es: "; 
	
	float media = 0;
	int totalAzul = 0, totalAmarelo = 0, totalBranco = 0, totalVermelho = 0, totalVerde = 0;
	
	for (i = 0; i <= 98; ++i) { // calcula o n� m�dio de passos entre uma colis�o e outra e calcula o n� de colis�es para cada cor de particula
		media += resultado[i+1].distanciaPassos; // soma as 99 dist�ncias de passos entre uma colis�o e outra 

		for (h = 0; h < resultado[i].quantParticulas; ++h) {
			if (resultado[i].particulas[h]->cor == azul) // se a cor da particula que colidiu for azul
				++totalAzul; // registra 1 no total de azuis
			else if (resultado[i].particulas[h]->cor == amarelo) // repete o mesmo procedimento para as outras cores
				++totalAmarelo;
			else if (resultado[i].particulas[h]->cor == branco)
				++totalBranco;
			else if (resultado[i].particulas[h]->cor == vermelho)
				++totalVermelho;
			else if (resultado[i].particulas[h]->cor == verde)
				++totalVerde;
		}
	}
	media /= 99; // n� m�dio de passos entre uma colis�o e outra

	cout.precision(5);

	cout << media << endl 
		<< "Colis�es por cor: " // n� de colis�es para cada cor de particula
		<< "Azul(" << totalAzul << ") "
		<< "Amarelo(" << totalAmarelo << ") "
		<< "Branco(" << totalBranco << ") "
		<< "Vermelho(" << totalVermelho << ") "
		<< "Verde(" << totalVerde << ")"
		<< endl;
} // fim do programa