#include "stdafx.hpp"
#include "main.hpp"





//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
int main(int argc, char *argv[])
{
	CGame Game;

	Game.Init(argc, argv);

	return 0;
}
