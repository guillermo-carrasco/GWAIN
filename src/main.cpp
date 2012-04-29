#include <iostream>
#include "Game.h"
//#include "Globals.h"
//#include "SDL/SDL.h"

int main(int argc, char *argv[]){
    
	CGame CGame;

    if (!CGame.Init())
        std::cerr << "Joc no iniciat" << std::endl;
    else CGame.GameLoop();

	CGame.End();

	return 0;
}
