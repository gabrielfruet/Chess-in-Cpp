#include "pch.h"
#include <iostream>
#include <conio.h>
#include "tabuleiro.hpp"
#include "menu.hpp"

#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13

Menu::Menu() {
	opcao = 0;
	menuinterfaceORG = importar("menu.txt");
	menuinterface = menuinterfaceORG;
}
void Menu::printMenu() {
	menuinterface = menuinterfaceORG;

	copySeta();

	for (unsigned char i = 0; i < 36; i++) {
		std::cout << menuinterface[i] << std::endl;
	}
}
void Menu::copySeta() {
	//LINHA 21
	//COLUNA 85;

	menuinterface[21 + (opcao * 2)][85] = '<';
	menuinterface[21 + (opcao * 2)][86] = '-';
	menuinterface[21 + (opcao * 2)][87] = '-';
	menuinterface[21 + (opcao * 2)][88] = '+';
}

void Menu::startMenu() { 
	char comando = 0;
	
	while ((opcao != 3)||(comando != ENTER)){
		system("CLS");
		printMenu();
		comando = getch();
		switch (comando) {
		case KEY_UP:
			if (opcao > 0) {
				opcao--;
			}
			break;
		case KEY_DOWN:
			if (opcao < 3) {
				opcao++;
			}
			break;
		default:

			break;
		}
		if (comando == ENTER) {
			startOpcao();
		}
	} ;

	startOpcao();
}

void Menu::startOpcao() {
	switch (opcao) {
	case 0: {
		Tabuleiro tabuleiro;
		tabuleiro.game();
	}break;
	case 1:

		break;
	case 2:{
		Ajuda ajuda;
		ajuda.startAjuda();
	}break;
	default:
		break;
	}
}

Ajuda::Ajuda() {
	ajudainterface = importar("ajuda.txt");
}

void Ajuda::printAjuda(){
	for (unsigned char i = 0; i < 36; i++) {
		std::cout << ajudainterface[i] << std::endl;;
	}
}

void Ajuda::startAjuda() {
	char comando = 0;
	while (comando != ENTER) {
		system("CLS");
		printAjuda();
		comando = getch();
	}
}