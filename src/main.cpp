#include "stdafx.hpp"
#include "main.hpp"

#include "tools/math.hpp"



//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
int main(int argc, char *argv[])
{
	CGame Game;

	Game.Init(argc, argv);

	std::cin.get();
	return 0;
}
