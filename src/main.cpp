#include "stdafx.hpp"
#include "main.hpp"


//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
int main(int argc, char *argv[])
{

#ifdef _DEBUG
	system("chcp 1250"); // codepage win-1250 for polish characters in command line

	std::cout
		<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl
		<< " �ADOWANIE PLIK�W / TEKSTUR / OBIEKT�W LUB WYWO�YWANIE FUNKCJI �ADUJ�CYCH W.W. " << std::endl
		<< "      NIE ROBI� TEGO W KONSTRUKTORACH KLAS->OPENGL NIE ZAINICJOWANY FUNCKJ�    " << std::endl
		<< "glutInit - NIE ZWRACA WSKA�NIK�W NA PAMI�� DO NICH => NIE �ADUJE ICH DO PAMI�CI" << std::endl
		<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
#endif

	CGame Game;

	Game.Init(argc, argv);

	return 0;
}
