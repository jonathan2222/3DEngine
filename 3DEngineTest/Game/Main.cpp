#include <crtdbg.h>
#include "NodeGame.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	NodeGame game;
	game.run();
	return 0;
}