#include "stdafx.hpp"
#include "main.hpp"

#include "tools/math.hpp"


//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
int main(int argc, char *argv[])
{
	system("chcp 1250"); // strona kodowa do polskich znak�w w cmd

#ifdef _DEBUG
	std::cout
		<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl
		<< " �ADOWANIE PLIK�W / TEKSTUR / OBIEKT�W LUB WYWO�YWANIE FUNKCJI �ADUJ�CYCH W.W. " << std::endl
		<< "      NIE ROBI� TEGO W KONSTRUKTORACH KLAS->OPENGL NIE ZAINICJOWANY FUNCKJ�    " << std::endl
		<< "glutInit - NIE ZWRACA WSKA�NIK�W NA PAMI�� DO NICH => NIE �ADUJE ICH DO PAMI�CI" << std::endl
		<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
#endif

	CGame Game;

	Game.Init(argc, argv);

	//std::cin.get();
	return 0;
}
