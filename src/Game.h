#pragma once

#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#include "Input.h"
#include "Graphics.h"
#include "Globals.h"
#include "Scene.h"
#include "Menu.h"
#include "Ranking.h"
#include "Credits.h"
#include "emyl.h"




#define GS_LOGO		1
#define GS_MENU		2
#define GS_PLAY		3
#define GS_PAUSE	4
#define GS_GAMEOVER 5
#define GS_RANKING	6
#define GS_CREDITS	7



class CGame{
    public:
		CGame();
		~CGame();

        bool Init();
        void GameLoop();
        void End();

    private:
        void draw();

		void posaMusicaMenu();
		void posaMusicaGame(bool init);

		CInput*			input;
		CScene*			escena;
		CGraphics*		graphics;
		CSoundManager*  soundman;
		CMenu*			menu;
		CRanking*		ranking;
		CCredits*		credits;

		emyl::stream* menuMusic;
		emyl::stream* gameMusic;

        int gameState;      
		bool bExit;
		bool soActiu;
};
