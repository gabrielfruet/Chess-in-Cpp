#include "pch.h"
#include <iostream>
#include "verif.hpp"
#include "calc.hpp"


bool verificaPosExist(unsigned char posicao) {
	if ((posicao < 0) || (posicao > 64)) {
		return false;
	}return true;
}

unsigned char verificaPosOcup(unsigned char posFutura, Time time, std::vector<Quadrado> tabuleiro) {
	if (time == tabuleiro[posFutura].recTime()) {
		return 0;
	}
	if (Time::Nulo == tabuleiro[posFutura].recTime()) {
		return 1;
	}
	return 2;
}

unsigned char retornaTipo(Tipo tipo) {

		/*
		7 - COMEU BISPO
		8 - COMEU REI
		9 - COMEU RAINHA
		10 - COMEU PEAO
		11 - COMEU CAVALO
		12 - COMEU TORRE*/

	switch (tipo) {
	case (Tipo::Bispo):
		std::cout << "BISPO";
		return 7;
		break;
	case (Tipo::Rei):
		std::cout << "REI";
		return 8;
		break;
	case (Tipo::Rainha):
		std::cout << "RAINHA";
		return 9;
		break;
	case (Tipo::Peao):
		std::cout << "PEAO";
		return 10;
		break;
	case (Tipo::Cavalo):
		std::cout << "CAVALO";
		return 11;
		break;
	case(Tipo::Torre):
		std::cout << "TORRE";
		return 12;
		break;
	}
}

void movimentacao(std::string& mov, unsigned char& posAtual, unsigned char& posFutura) {
	mov[1] = toupper(mov[1]);
	mov[4] = toupper(mov[4]);
	posAtual = arrayP(8, mov[0] - 49, mov[1] - 65);
	posFutura = arrayP(8, mov[3] - 49, mov[4] - 65);
}