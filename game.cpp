#include "pch.h"
#include <iostream>
#include <conio.h>
#include "tabuleiro.hpp"
#include "verif.hpp"


void Tabuleiro::game() {
	


	unsigned char posAtual = 0;
	unsigned char posFutura = 0;
	Time timeAtual = Time::Branco;
	unsigned char indice = 20;

	do {
		
		print_game(indice);
		std::cout << "Jogada do ";
		switch (timeAtual) {
		case Time::Branco:
			std::cout << "Branco: ";
		break;
		case Time::Preto: 
			std::cout << "Preto: ";
		}

		std::string mov;
		getline(std::cin, mov);
		std::cout << mov << std::endl;

		movimentacao(mov, posAtual, posFutura);

		while (tabuleiro[posAtual].recTime() != timeAtual) {
			std::cout << "Vez do outro time!";
			getline(std::cin, mov);
			std::cout << mov << std::endl;
			movimentacao(mov, posAtual, posFutura);			
		}
		indice = moverPeca(posAtual, posFutura);
		print_game(indice);
		while ((indice > 1) && (indice < 7)) {
			std::cout << "Jogada invalida!";
			getline(std::cin, mov);
			std::cout << mov << std::endl;
			movimentacao(mov, posAtual, posFutura);
			print_game(indice);
			while (tabuleiro[posAtual].recTime() != timeAtual) {
				std::cout << "Vez do outro time!";
				getline(std::cin, mov);
				std::cout << mov << std::endl;
				movimentacao(mov, posAtual, posFutura);
			}
			indice = moverPeca(posAtual, posFutura);
		}

		push_move(mov);

		switch (timeAtual) {
		case Time::Branco:
			timeAtual = Time::Preto;
			break;
		case Time::Preto:
			timeAtual = Time::Branco;
		}
		verificaVencedor();

		if (verificaPeao() != 64) {
			print_game(0);
			transformaPeao(verificaPeao());
		}
	} while (recVencedor() == Time::Nulo);
}