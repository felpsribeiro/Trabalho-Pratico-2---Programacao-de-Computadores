#include <iostream>
#include "particula.h"
#include "vetor.h"
#include "cor.h"
#include <random>
using namespace std;

int main()
{
	system("chcp 1252 >nul");

	int i,h; // váriaveis auxiliares que seram usadas dentro dos laços de repetição
	registroParticula particula[10]; //declaração do vetor de registro que guardará as particulas

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

	for (i = 0; i < 10; ++i) { // lê as 10 particulas
		cin >> particula[i];
		cin.get();
	}

	cout << "\nSimulação\n---------\n";

	random_device rand; 

	int passoComColisao = 0; // variavel que guarda o número de passos com colisões
	int passos = 0; // variavel que guarda o número total de passos
	int a; // varaiavel que guarda o valor do primeiro sorteio
	int b; // varaiavel que guarda o valor do segundo sorteio
	registroResultado resultado[100]; // registro que guarda as informações dos passos que houveram coliões
	int totalColisoes = 0; //armazena o número total de colisões

	while (!resultado[99].quantParticulas) { // enquanto o (registro)resultado de nº 100 tiver a quant de colisões igual a 0, se repete o laço 
		++passos; // indica a passagem do passo

		a = (rand() % 10) + 1; // gera o primeiro nº aleatório que representa a quant de particulas q seram alteradas de posição

		cout << "#" << passos << ": " << a << " ( ";

		registroParticula* * enderecos = new registroParticula* [a]; // cria um rgistro dinâmico de ponteiros que armazenaram os endereços das particulas alteradas

		for (i = 0; i < a; ++i) { // altera a posição de a (primeiro nº sorteado) particulas 
			b = rand() % 10; // sorteia a particula de 0 a 9 que terá a posição alterada

			cout << b << " ";

			enderecos[i] = &particula[b]; // guarda o endereço da particula sorteada
			enderecos[i]->atual = deslocamento(enderecos[i]->atual, enderecos[i]->vetor, enderecos[i]->sistema); // altera o valor da posição da particula

			if (particula[b].atual.x >= 800 || particula[b].atual.x <= 0 || particula[b].atual.y >= 600 || particula[b].atual.y <= 0) { // se a nova posição gerou alguma colisão
				if (particula[b].atual.x >= 800 || particula[b].atual.x <= 0) { //se colidiu nas laterais
					enderecos[i]->vetor = inversao(enderecos[i]->vetor, enderecos[i]->sistema, true); // altera o vetor da particula para ela voltar para o espaço de confinamento
					++totalColisoes; // registra que houve colisão
				}
				if (particula[b].atual.y >= 600 || particula[b].atual.y <= 0) { //se colidiu em cima ou baixo
					enderecos[i]->vetor = inversao(enderecos[i]->vetor, enderecos[i]->sistema, false); // altera o vetor da particula para ela voltar para o espaço de confinamento
					++totalColisoes; // registra que houve colisão
				}
				resultado[passoComColisao].particulas[resultado[passoComColisao].quantParticulas] = &particula[b]; // salva o endereço da particula que houve a colisão
				++resultado[passoComColisao].quantParticulas; // soma uma colisão no determinado (registro)resultado
			}
		}

		if (resultado[passoComColisao].quantParticulas) { // se tiver ocorrido alguma colisão
			cout << ") = " << resultado[passoComColisao].quantParticulas << " ( ";
			
			for (i = 0; i < resultado[passoComColisao].quantParticulas; ++i)
				cortar(resultado[passoComColisao].particulas[i]->nome); // exibi o sobrenome da particula
			cout << ")\n";

			++passoComColisao; // no próximo ciclo de repetição, os resultados seram guardados no próximo (registro)resultado
		}

		else { // se não tiver ocorrido nenhuma colisão
			cout << ") = 0\n"; 
			++resultado[passoComColisao].distanciaPassos; // se não houve colisão, aumenta a distância entre uma colisão e outra
		}

		delete[] enderecos; // apaga a memória dinâmica utilizada
	}
	// apresenta os resultados 

	cout << fixed;
	cout.precision(6);
	
	cout << "\nResultados\n----------\n"
		<< "Colisões: " << totalColisoes << endl // total de colisões
		<< "Colisões por passo: " << float(totalColisoes) / passos << endl // nº médio de particulas que colidiram a cada passo
		<< "Média de passos entre as colisões: "; 
	
	float media = 0;
	int totalAzul = 0, totalAmarelo = 0, totalBranco = 0, totalVermelho = 0, totalVerde = 0;
	
	for (i = 0; i <= 98; ++i) { // calcula o nº médio de passos entre uma colisão e outra e calcula o nº de colisões para cada cor de particula
		media += resultado[i+1].distanciaPassos; // soma as 99 distâncias de passos entre uma colisão e outra 

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
	media /= 99; // nº médio de passos entre uma colisão e outra

	cout.precision(5);

	cout << media << endl 
		<< "Colisões por cor: " // nº de colisões para cada cor de particula
		<< "Azul(" << totalAzul << ") "
		<< "Amarelo(" << totalAmarelo << ") "
		<< "Branco(" << totalBranco << ") "
		<< "Vermelho(" << totalVermelho << ") "
		<< "Verde(" << totalVerde << ")"
		<< endl;
} // fim do programa