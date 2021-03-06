
#include "vetor.h"
#include <cmath>

const float PI = 3.14159f; // contate com o valor de Pi

registroCoord deslocamento(registroCoord ponto, uniaoVetor vetor, char tipo) // função que desloca a particula, somando a posição mais o vetor
{
	registroCoord nova;
	if (tipo == 'P') { // se a particula for do sistema Polar
		nova = deslocamentoPol(ponto, vetor.pol); // chama a função de deslocamento de polar
	}
	else if (tipo == 'C') { // se a particula for do sistema Cartesiano
		nova = deslocamentoCar(ponto, vetor.car); // chama a função de deslocamento de cartesiano
	}
	return (nova);
}

registroCoord deslocamentoPol(registroCoord ponto, registroPol vetor) // função de deslocamento no sistema polar
{
	registroCoord nova;
	nova.x = ponto.x + vetor.mag * cos(vetor.ang * PI / 180); // soma a coordenada de x inicial com o deslocamento em x
	nova.y = ponto.y - vetor.mag * sin(vetor.ang * PI / 180); // soma a coordenada de y inicial com o deslocamento em y
	return nova;
}

registroCoord deslocamentoCar(registroCoord ponto, registroCar vetor) // função de deslocamento no sistema cartesiano
{
	registroCoord nova;
	nova.x = ponto.x + vetor.px; // soma a coordenada de x inicial com o deslocamento em x
	nova.y = ponto.y - vetor.py; // soma a coordenada de y inicial com o deslocamento em y
	return nova;
}

istream& operator>> (istream& is, registroPol& p) // função para "ensinar" o cout a lê o registro com as cordenadas polares
{
	is >> p.ang;
	is >> p.mag;
	return is;
}

istream& operator>> (istream& is, registroCar& p) // função para "ensinar" o cout a lê o registro com as cordenadas cartesinas
{
	is >> p.px;
	is >> p.py;
	return is;
}

uniaoVetor inversao(uniaoVetor entrada, char sistema,bool paredes) // função para inverter o vetor
{
    if (sistema == 'C' && paredes) { // se a particula estiver no sistema cartesino e bater nas laterais (saiu no eixo x)
		entrada.car.px *= -1;
		return entrada;
	}
	if (sistema == 'C' && !paredes) { // se a particula estiver no sistema cartesino e bater em cima ou em baixo (saiu no eixo y)
		entrada.car.py *= -1;
		return entrada;
	}


	if (sistema == 'P') { // se a particula estiver no sistema polar 

		float dy = entrada.pol.mag * sin(entrada.pol.ang * PI / 180); // acha o equivalente de y em cartesiano
		float dx = entrada.pol.mag * cos(entrada.pol.ang * PI / 180); //  acha o equivalente de x em cartesiano

	    if (paredes) // a colisão foi nas laterais (saiu no eixo x)
			entrada.pol.ang = atan2(dy, -1 * dx) * 180 / PI;

		if (!paredes) // a colisão foi em cima ou em baixo (saiu no eixo y)
			entrada.pol.ang = atan2(-1 * dy, dx) * 180 / PI;

		if (entrada.pol.ang < 0) // caso o ângulo esteja negativo, convete-o para seu equivalente positivo
			entrada.pol.ang += 360; // ângulo replementar

		return entrada;
	}
}