#pragma once
#include "pch.h"
#include <array>
#include <string>
#include "imports.hpp"

class Menu {
private:
	int opcao;
	std::array <std::string, 36> menuinterface;
	std::array <std::string, 36> menuinterfaceORG;
public:
	Menu();
	void copySeta();
	void printMenu();
	void startMenu();
	void startOpcao();
};

class Ajuda {
private:
	std::array <std::string, 36> ajudainterface;
public:
	Ajuda();
	void printAjuda();
	void startAjuda();
};