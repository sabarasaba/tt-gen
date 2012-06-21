#pragma once
#include "TrueTable.h"
#include "Expression.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;
using std::string;


string expression = "";
//expression = "((A|B)&(B|C))";

int main(int argc, char* argv[])
{
	if (argc == 0)
	{
		std::cout << "GTDV - Generador Tablas de Verdad" << std::endl;
		std::cout << std::endl;
		std::cout << "Operadores validos:" << std::endl;
		std::cout << " * '|' => Operador Or" << std::endl;
		std::cout << " * '&' => Operador And" << std::endl;
		std::cout << " * '%' => Operador Xor" << std::endl;
		std::cout << " * '~' => Operador Not" << std::endl;
		std::cout << " * '>' => Operador de Implicación" << std::endl;
		std::cout << " * '#' => Operador de Pierce" << std::endl;
		std::cout << " * '@' => Operador de Sheffer" << std::endl;
		std::cout << std::endl;
		std::cout << "Ingrese expresión: " << std::endl;
		std::cin >> expression;
		std::cout << std::endl;
	}

	if (argc == 1)
	{
		expression = argv[1];
	}
	if (argc > 1)

		for (int i = 2; i < argc; i++)
		{
			/*
			switch(argv[i])
			{
			case "-htm":
					std::cout << "Export to HTM" << std::endl;
				break;
			case "-xls":
					std::cout << "Export to XLS" << std::endl;
				break;
			case "-txt":
					std::cout << "Export to TXT" << std::endl;
				break;
			case "-?":
				std::cout << "Genera una tabla de verdad a partir de una expresión." << std::endl;
				std::cout << std::endl;
				std::cout << "GTDV [expresión] [-htm] [-xls] [-txt]" << std::endl;
				std::cout << std::endl;
				std::cout << "-htm      Exporta la tabla de verdad generada a un archivo htm" << std::endl;
				std::cout << "-xls      Exporta la tabla de verdad generada a un archivo xls" << std::endl;
				std::cout << "-txt      Exporta la tabla de verdad generada a un archivo txt" << std::endl;
				std::cout << std::endl;
				std::cout << "Ejemplo: GTDV ((A|B)&(B|C)) -htm" << std::endl;
				std::cout << std::endl;
				break;
			}
			*/
				
		}

	Expression *Exp = new Expression(expression);
	TrueTable *TT;

	if (Exp->Valid())
	{
		std::cout << "Expresion Valida" << std::endl;

		TT = new TrueTable(expression, Exp->GetExpressions());
		TT->DoLogic();
		TT->PrintTable();
	}
	else
	{
		Exp->PrintErrors();
	}


	Exp->~Expression();
	TT->~TrueTable();

	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}