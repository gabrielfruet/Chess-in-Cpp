#include "pch.h"
#include <iostream>
#include <conio.h>
#include "tabuleiro.hpp"
#include "calc.hpp"
#include "verif.hpp"
#include "imports.hpp"



//FUNCOES QUADRADO
Quadrado::Quadrado(Time time, Tipo tipo, unsigned char pos) : time(time), tipo(tipo), pos(pos) {
	
}
Time Quadrado::recTime() {
	return time;
}
Tipo Quadrado::recTipo() {
	return tipo;
}
unsigned char Quadrado::recPos() {
	return pos;
}
void Quadrado::setPos(const unsigned char &posFutura) {
	pos = posFutura;
}
std::string Quadrado::recuperaNome() {
	switch (tipo) {
	case Tipo::Bispo:
		return "Bispo";
		break;
	case Tipo::Cavalo:
		return "Cavalo";
		break;
	case Tipo::Nulo:
		return "";
		break;
	case Tipo::Peao:
		return "Peao";
		break;
	case Tipo::Rainha:
		return "Rainha";
		break;
	case Tipo::Rei:
		return "Rei";
		break;
	case Tipo::Torre:
		return "Torre";
		break;
	}
}
std::string Quadrado::recuperaTime() {
	switch (time) {
	case Time::Branco: {
		return "Branco";
	}break;
	case Time::Preto: {
		return "Preto";
	}
	}
}
void Quadrado::mudaTipo(Tipo mudanca){
	tipo = mudanca;
}

//FUNCOES DO TABULEIRO
Tabuleiro::Tabuleiro() {
	tabuleiro.push_back(Quadrado(Time::Preto, Tipo::Torre, 0));
	tabuleiro.push_back(Quadrado(Time::Preto, Tipo::Cavalo, 1));
	tabuleiro.push_back(Quadrado(Time::Preto, Tipo::Bispo, 2));
	tabuleiro.push_back(Quadrado(Time::Preto, Tipo::Rei, 3));
	tabuleiro.push_back(Quadrado(Time::Preto, Tipo::Rainha, 4));
	tabuleiro.push_back(Quadrado(Time::Preto, Tipo::Bispo, 5));
	tabuleiro.push_back(Quadrado(Time::Preto, Tipo::Cavalo, 6));
	tabuleiro.push_back(Quadrado(Time::Preto, Tipo::Torre, 7));

	for (unsigned char i = 8; i < 16; i++) {
		tabuleiro.push_back(Quadrado(Time::Preto, Tipo::Peao, i));
	}

	for (unsigned char i = 16; i < 48; i++) {
		tabuleiro.push_back(Quadrado(Time::Nulo, Tipo::Nulo, i));
	}

	for (unsigned char i = 48; i < 56; i++) {
		tabuleiro.push_back(Quadrado(Time::Branco, Tipo::Peao, i));
	}
	tabuleiro.push_back(Quadrado(Time::Branco, Tipo::Torre, 56));
	tabuleiro.push_back(Quadrado(Time::Branco, Tipo::Cavalo, 57));
	tabuleiro.push_back(Quadrado(Time::Branco, Tipo::Bispo, 58));
	tabuleiro.push_back(Quadrado(Time::Branco, Tipo::Rei, 59));
	tabuleiro.push_back(Quadrado(Time::Branco, Tipo::Rainha, 60));
	tabuleiro.push_back(Quadrado(Time::Branco, Tipo::Bispo, 61));
	tabuleiro.push_back(Quadrado(Time::Branco, Tipo::Cavalo, 62));
	tabuleiro.push_back(Quadrado(Time::Branco, Tipo::Torre, 63));

	if (tabuleiro.size() > 64) {
		std::cout << "TABULEIRO TAMANHO EXCEDIDO";
	}

	interfacetabu = importar("tabuleiro.txt");
	interfacetabuORG = interfacetabu;
	vencedor = Time::Nulo;
}

unsigned char Tabuleiro::moverPeca(const unsigned char &posAtual, const unsigned char &posFutura) {
	/*INDICE
	1-MOVEU PARA POSICAO VAZIA
	2-POSICAO INEXISTENTE
	3-POSICAO VAZIA
	4-ALIADO NA POSICAO FUTURA
	5-MOVIMENTACAO NAO CORRESPONDE
	6-PECA NO CAMINHO
	7-COMEU BISPO
	8-COMEU REI
	9-COMEU RAINHA
	10-COMEU PEAO
	11-COMEU CAVALO
	12-COMEU TORRE*/

	int rowA = arrayL(8, posAtual);
	int rowF = arrayL(8, posFutura);
	int colA = arrayC(8, posAtual);
	int colF = arrayC(8, posFutura);

	if (!verificaPosExist(posFutura)) {
		//std::cout << "POSFUT";
		return 2;
	}

	if (!verificaPosExist(posAtual)) {
		//std::cout << "POSATUAL";
		return 2;
	}

	if (posAtual == posFutura) {
		//std::cout << "POSATUAL == POSFUTURA";
		return 2;
	}

	if (tabuleiro[posAtual].recTipo() == Tipo::Nulo) {
		return 3;
	}

	if (verificaPosOcup(posFutura, tabuleiro[posAtual].recTime(), tabuleiro) == 0) {
		return 4;
	}

	//INICIALIZANDO VARIAVEIS;
	enum Sentidos : unsigned char { Diagonal, Horizontal, Vertical };
	Sentidos sentido;
	int posVer = '\0';
	int posHor = '\0';
	int sigVer = '\0';
	int sigHor = '\0';

	switch (tabuleiro[posAtual].recTipo()) {
	case (Tipo::Peao):{
		unsigned char Comer = 0;
		if (tabuleiro[posFutura].recTipo() != Tipo::Nulo) {
			Comer = 1;
		}

		unsigned char aux;

		if (tabuleiro[posAtual].recTime() == Time::Branco) {
			aux = 6;
			if (posAtual < posFutura) { 
				return 5;
			}
		}
		else {
			aux = 1;
			if (posAtual > posFutura) {
				return 5;
			}
		}

		switch (Comer) {
		case 1:
			if (abs(rowF - rowA) != abs(colF - colA)) {
				return 5;
			}
			if (abs(rowF - rowA) > 1) {
				return 5;
			}
			break;
		case 0:
			if (abs(rowF - rowA) == abs(colF - colA)) {
				return 5;
			}
			if (rowA == aux) {
				if (abs(rowA - rowF) > 2) {
					return 5;
				}

				if (posAtual > posFutura) {
					for (short int i = rowF - 1; i < rowA; i++) {
						if (tabuleiro[arrayP(8, i, colA)].recTipo() != Tipo::Nulo) {
							return 6;
						}
					}
				}
				else {
					for (short int i = rowA + 1; i < rowF; i++) {
						if (tabuleiro[arrayP(8, i, colA)].recTipo() != Tipo::Nulo) {
							return 6;
						}
					}
				}
			}
			else {
				if (abs(rowA - rowF) > 1) {
					return 5;
				}
			}
		}
	}
			break;
	case (Tipo::Rainha):
		sentido = Diagonal;

		if (abs(rowF - rowA) != abs(colF - colA)) {
			sentido = Horizontal;
			if (rowA != rowF) {
				sentido = Vertical;
				if (colA!= colF) {
					return 5;
				}
			}
		}
		switch (sentido) {
		case Diagonal:
			posVer = rowA - rowF;
			posHor = colA - colF;
			sigVer = posVer / abs(posVer);
			sigHor = posHor / abs(posHor);

			for (short int i = 1; i < abs(posHor); i++) {
				if (tabuleiro[posAtual - 8*(i * sigVer) - (i * sigHor)].recTipo() != Tipo::Nulo) {
					return 6;
				}
			}
			break;
		case Horizontal:
			if (posAtual > posFutura) {
				for (int j = colF + 1; j < colA; j++) {
					if (tabuleiro[arrayP(8, rowA, j)].recTime() != Time::Nulo) {
						return 6;
					}
				}
			}
			else {
				for (int j = colA - 1; j < colF; j++) {
					if (tabuleiro[arrayP(8, rowA, j)].recTime() != Time::Nulo) {
						return 6;
					}
				}
			}
			break;
		case Vertical:
			if (rowA > rowF) {
				for (int i = rowF + 1; i < rowA; i++) {
					if (tabuleiro[arrayP(8, i,colA)].recTime() != Time::Nulo) {
						return 6;
					}
				}
			}
			else {
				for (int i = rowA - 1; i < rowF; i++) {
					if (tabuleiro[arrayP(8, i, colA)].recTime() != Time::Nulo) {
						return 6;
					}
				}
			}
			break;
		}


			break;
	case (Tipo::Rei):
		//VERIFICA SE A POSICAO CORRESPONDE
		if ((abs(rowA - rowF) > 1) || (abs(colA - colF) > 1)) {
			return 5;
		}
			break;
	case (Tipo::Cavalo):
		if ((abs(rowA - rowF) != 2)&&(abs(colA - colF) != 2)) {
			return 5;
		}
		if ((abs(rowA - rowF) == 2)) {
			if (abs(colA - colF) != 1) {
				return 5;
			}
		}
		else if (abs(colA - colF) == 2) {
			if (abs(rowA - rowF) != 1) {
				return 5;
			}
		}
			break;
	case(Tipo::Torre):
		//VERIFICA SE ESTA NA LOGICA DA POSICAO E O RESPECTIVO SENTIDO
		if (rowA != rowF) {
			sentido = Vertical;
			if (colA != colF) {
				return 5;
			}
		}
		else if(colA != colF) {
			sentido = Horizontal;
			if (rowA != rowF) {
				return 5;
			}
		}
		//FILTA POR SENTIDO
		switch (sentido) {
		case Horizontal:
			if (posAtual > posFutura) {
				for (int j = colF + 1; j < colA; j++) {
					if (tabuleiro[arrayP(8, rowA, j)].recTime() != Time::Nulo) {
						return 6;
					}
				}
			}
			else {
				for (int j = colA - 1; j < colF; j++) {
					if (tabuleiro[arrayP(8, rowA, j)].recTime() != Time::Nulo) {
						return 6;
					}
				}
			}
			break;
		case Vertical:
			if (rowA > rowF) {
				for (int i = rowF + 1; i < rowA; i++) {
					if (tabuleiro[arrayP(8, i, colA)].recTime() != Time::Nulo) {
						return 6;
					}
				}
			}
			else {
				for (int i = rowA - 1; i < rowF; i++) {
					if (tabuleiro[arrayP(8, i, colA)].recTime() != Time::Nulo) {
						return 6;
					}
				}
			}
			break;
		}
			break;
	case (Tipo::Bispo):
		if (abs(rowF - rowA) != abs(colF - colA)) {
			return 5;
		}

		posVer = rowA - rowF;
		posHor = colA - colF;
		sigVer = posVer / abs(posVer);
		sigHor = posHor / abs(posHor);

		for (short int i = 1; i < abs(posHor); i++) {
			if (tabuleiro[posAtual - 8 * (i * sigVer) - (i * sigHor)].recTipo() != Tipo::Nulo) {
				return 6;
			}
		}
	}

	//Mudando posicoes
	if (verificaPosOcup(posFutura, tabuleiro[posAtual].recTime(), tabuleiro) == 2) {
		Tipo retorno = tabuleiro[posFutura].recTipo();
		tabuleiro[posAtual].setPos(posFutura);
		tabuleiro[posFutura] = tabuleiro[posAtual];
		tabuleiro[posAtual] = Quadrado(Time::Nulo, Tipo::Nulo, posAtual);
		return retornaTipo(retorno);
	}
	else {
		tabuleiro[posAtual].setPos(posFutura);
		tabuleiro[posFutura] = tabuleiro[posAtual];
		tabuleiro[posAtual] = Quadrado(Time::Nulo, Tipo::Nulo, posAtual);
		return 1;
	}
	

}
void Tabuleiro::copyPecas() {
	for (unsigned char i = 0; i < 8; i++) {
		for (unsigned char j = 0; j < 8; j++) {
			unsigned char k = 0;
			for (char c : tabuleiro[arrayP(8, i, j)].recuperaNome()) {
				interfacetabu[5 + (4 * i)][(8 + k) + (j * 16) + (15 - tabuleiro[arrayP(8, i, j)].recuperaNome().size())/2 ] = c;
				k++;
			}
			switch (tabuleiro[arrayP(8, i, j)].recTime()) {
			case Time::Branco: {
				interfacetabu[6 + (4 * i)][(15) + (j * 16)] = 'B';
			}break;
			case Time::Preto: {
				interfacetabu[6 + (4 * i)][(15) + (j * 16)] = 'P';
			}break;
			default: {

			}break;

			}
		}
	}
}
void Tabuleiro::printInterface() {
	for (unsigned char i = 0; i < 36; i++) {
		std::cout << interfacetabu[i] << std::endl;
		
	}
}
void Tabuleiro::copyFB(const unsigned char& indice) {
	/*INDICE
	1-MOVEU PARA POSICAO VAZIA
	2-POSICAO INEXISTENTE
	3-POSICAO VAZIA
	4-ALIADO NA POSICAO FUTURA
	5-MOVIMENTACAO NAO CORRESPONDE
	6-PECA NO CAMINHO
	7-COMEU BISPO
	8-COMEU REI
	9-COMEU RAINHA
	10-COMEU PEAO
	11-COMEU CAVALO
	12-COMEU TORRE*/

	//COLUNA INICIAL = 137;
	//LINHA INICIAL = 27; 
	if (indice == 20) {
		return;
	}

	if (indice > 6) { 
		std::string comeu = "Comeu um";
		std::string peca;
		char prefix = NULL;
		switch (indice) {
			
		case 7:
			peca = " Bispo!";
			break;
		case 8:
			peca = " Rei!";
			break;
		case 9:
			peca = " Rainha!";
			prefix = 'a';
			break;
		case 10:
			peca = " Peao!";
			break;
		case 11:
			peca = " Cavalo!";
			break;
		case 12:
			peca = " Torre!";
			break;
		}
		char k = 0;

		for (char c : comeu + prefix + peca) {
			if (c != '\0') {
				interfacetabu[30][137 + (27 - (comeu + prefix + peca).size()) / 2 + k] = c;
				k++;
			}

		}
	}
	switch (indice) {
	case 0: {
		char k = 0;
		for (char c : "Escolha no que seu") {
			if (c != '\0') {
				interfacetabu[27][137 + (27 - 19) / 2 + k] = c;
				k++;
			}

		}
		k = 0;
		for (char c : "peao ira se transformar") {
			if (c != '\0') {
				interfacetabu[28][137 + (27 - 21) / 2 + k] = c;
				k++;
			}

		}
		k = 0;
		for (char c : "1-BISPO") {
			if (c != '\0') {
				interfacetabu[30][137 + (27 - 8) / 2 + k] = c;
				k++;
			}

		}
		k = 0;
		for (char c : "2-RAINHA") {
			if (c != '\0') {
				interfacetabu[31][137 + (27 - 9) / 2 + k] = c;
				k++;
			}

		}
		k = 0;
		for (char c : "3-CAVALO") {
			if (c != '\0') {
				interfacetabu[32][137 + (27 - 9) / 2 + k] = c;
				k++;
			}

		}
		k = 0;
		for (char c : "4-TORRE") {
			if (c != '\0') {
				interfacetabu[33][137 + (27 - 8) / 2 + k] = c;
				k++;
			}

		}
	}break;
	case 1:{
		char k = 0;
		for (char c : "Movimento realizado") {
			if (c != '\0') {
				interfacetabu[29][137 + (27 - 19) / 2 + k] = c;
				k++;
			}
			
		}

		k = 0;
		for (char c : "com sucesso!") {
			if (c != '\0') {
				interfacetabu[30][137 + (27 - 13) / 2 + k] = c;
				k++;
			}
			
		}
		
	}break;
	case 2: {
		char k = 0;
		for (char c : "Posicao inexistente!") {
			if (c != '\0') {
				interfacetabu[30][137 + (27 - 18) / 2 + k] = c;
				k++;
			}
			
		}
	}break;
	case 3: {
		char k = 0;
		for (char c : "Posicao atual vazia!") {
			if (c != '\0') {
				interfacetabu[30][137 + (27 - 19) / 2 + k] = c;
				k++;
			}
			
		}
	}break;
	case 4:{
		char k = 0;
		for (char c : "Aliado na posicao!") {
			if (c != '\0') {
				interfacetabu[30][137 + (27 - 19) / 2 + k] = c;
				k++;
			}
			
		}
	}break;
	case 5: {
		char k = 0;
		for (char c : "Movimento nao pertence") {
			if (c != '\0') {
				interfacetabu[29][137 + (27 - 20) / 2 + k] = c;
				k++;
			}
			
		}
		k = 0;
		for (char c : "a peca escolhida!") {
			if (c != '\0') {
				interfacetabu[30][137 + (27 - 16) / 2 + k] = c;
				k++;
			}
			
		}
	}break;
	case 6: {
		char k = 0;
		for (char c : "Peca no caminho!") {
			if (c != '\0') {
				interfacetabu[30][137 + (27 - 15) / 2 + k] = c;
				k++;
			}
			
		}
	}break;
	default:
		
		break;

	}
}
void Tabuleiro::print_game(const unsigned char& indice) {

	system("CLS");
	interfacetabu = interfacetabuORG;
	copyMoves();
	copyPecas();
	copyFB(indice);
	printInterface();
}
void Tabuleiro::copyMoves() {
	for (unsigned char i = 0; i < oldmoves.size(); i++) {
		unsigned char k = 0;
		if (i < 19) {
			for (char c : oldmoves[oldmoves.size() - 1 - i]) {
				interfacetabu[4 + i][143 + k] = c;
				k++;
			}
		}else if (i < 39) {
			for (char c : oldmoves[oldmoves.size() - 1 - i]) {
				interfacetabu[4 + (19 - i)][155 + k] = c;
				k++;
			}
		}
		else {
			return;
		}
		
	}
}
void Tabuleiro::push_move(std::string mov) {
	oldmoves.push_back(mov);
}
void Tabuleiro::verificaVencedor() {
	bool ReiBrancoVivo = false;
	bool ReiPretoVivo = false;
	for (unsigned char i = 0; i < 64; i++) {
		if (tabuleiro[i].recTipo() == Tipo::Rei) {
			if (tabuleiro[i].recTime() == Time::Branco) {
				ReiBrancoVivo = true;
			}
			else if (tabuleiro[i].recTime() == Time::Preto) {
				ReiPretoVivo = true;
			}
		}
		
	}
	if (!ReiBrancoVivo) {
		vencedor = Time::Preto;
		return;
	}
	if (!ReiPretoVivo) {
		vencedor = Time::Branco;
		return;
	}
}
void Tabuleiro::transformaPeao(unsigned char posicao) {
	int escolhido;
	do {
		escolhido = getch();
	} while ((escolhido <= 4) && (escolhido >= 1));
	switch (escolhido) {
	case 1:{
		tabuleiro[posicao].mudaTipo(Tipo::Bispo);
	}break;
	case 2:{
		tabuleiro[posicao].mudaTipo(Tipo::Rainha);
	}break;
	case 3:{
		tabuleiro[posicao].mudaTipo(Tipo::Cavalo);
	}break;
	case 4:{
		tabuleiro[posicao].mudaTipo(Tipo::Torre);
	}break;
	}
}
int Tabuleiro::verificaPeao() {
	for (unsigned char i = 0; i < 64; i++) {
		if (tabuleiro[i].recTipo() == Tipo::Peao) {
			return i;
		}
		if (i == 7) {
			i = 55;
		}
	}
	return 64;
}
Time Tabuleiro::recVencedor() {
	return vencedor;
}