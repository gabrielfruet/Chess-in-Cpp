#include "pch.h"
#include <stdio.h>
#include <iostream> 
#include <fstream>
#include "windows.h"
#include "tabuleiro.hpp"
#include "imports.hpp"

//36 LINHAS

std::array <std::string, 36> importar(std::string nome) {
	std::ifstream INTERFACE;

	INTERFACE.open(nome);

	char aux[36][256];
	std::array <std::string, 36> interface;

	for (char i = 0; i < 36; i++) {
		getline(INTERFACE, interface[i]);
	}
	return interface;
}



