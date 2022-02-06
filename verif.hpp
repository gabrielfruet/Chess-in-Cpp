#pragma once
#include "pch.h"
#include <vector>
#include "tabuleiro.hpp"


bool verificaPosExist(unsigned char posicao);
unsigned char verificaPosOcup(unsigned char posFutura, Time time, std::vector<Quadrado> tabuleiro);
unsigned char retornaTipo(Tipo tipo);
void movimentacao(std::string& mov, unsigned char& posAtual, unsigned char& posFutura);
