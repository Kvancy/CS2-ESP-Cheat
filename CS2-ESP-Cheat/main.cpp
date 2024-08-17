#include "kWindow.h"
#include "kGame.h"
#include "kPlayerPawn.h"
#define isWorldwide 1
#if isWorldwide
#define WINDOWNAME "Counter-Strike 2"
#else
define WINDOWNAME "反恐精英：全球攻势"
#endif
kWindow* window = nullptr;
kGame* game = nullptr;
kRender* render = nullptr;

int main()
{
    window = new kWindow(WINDOWNAME);
    game = new kGame(TEXT("cs2.exe"), window->getRect());
	window->msgLoop(game);	
}
	