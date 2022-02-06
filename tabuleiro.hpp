#pragma once
#include "pch.h"
#include <vector>
#include <string>

enum class Time : unsigned char {
	Branco, Preto, Nulo
};
enum class Tipo : unsigned char {
	Rainha, Rei, Bispo, Peao, Torre, Cavalo, Nulo
};

class Quadrado {
private:
	Time time;
	Tipo tipo;
	unsigned char pos;
public:
	Quadrado(Time time, Tipo tipo, unsigned char pos);
	Time recTime();
	Tipo recTipo();
	unsigned char recPos();
	std::string recuperaNome();
	std::string recuperaTime();
	void mudaTipo(Tipo mudanca);
	void setPos(const unsigned char& posFutura);
};

class Tabuleiro {
private:
	std::vector<Quadrado> tabuleiro;
	std::array <std::string, 36> interfacetabu;
	std::array <std::string, 36> interfacetabuORG;
	std::vector <std::string> oldmoves;
	Time vencedor;

public:
	Tabuleiro();
	unsigned char moverPeca(const unsigned char& posAtual, const unsigned char& posFutura);
	void copyPecas();
	void printInterface();
	void copyFB(const unsigned char& indice);
	void print_game(const unsigned char& indice);
	void game();
	void push_move(std::string mov);
	void copyMoves();
	void verificaVencedor();
	void transformaPeao(unsigned char posicao);
	int verificaPeao();
	Time recVencedor();
};
