#include "stdafx.hpp"
#include "main.hpp"

#include "tools/math.hpp"


//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
int main(int argc, char *argv[])
{
	system("chcp 1250"); // strona kodowa do polskich znaków w cmd

#ifdef _DEBUG
	std::cout
		<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl
		<< " £ADOWANIE PLIKÓW / TEKSTUR / OBIEKTÓW LUB WYWO£YWANIE FUNKCJI £ADUJ¥CYCH W.W. " << std::endl
		<< "      NIE ROBIÆ TEGO W KONSTRUKTORACH KLAS->OPENGL NIE ZAINICJOWANY FUNCKJ¥    " << std::endl
		<< "glutInit - NIE ZWRACA WSKANIKÓW NA PAMIÊÆ DO NICH => NIE £ADUJE ICH DO PAMIÊCI" << std::endl
		<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
#endif

	CGame Game;

	Game.Init(argc, argv);

	//std::cin.get();
	return 0;
}
