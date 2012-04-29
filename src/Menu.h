#pragma once

#include "Globals.h"
#include <iostream>
#include <SDL/SDL.h>
#include <cmath>
#include "Input.h"
#include "Models.h"
#include "emyl.h"
#include "TextureManager.h"
#include "SoundManager.h"


#define MB_PLAY		1
#define MB_NEWGAME	2
#define MB_RANKING	3
#define MB_CREDITS	4
#define MB_EXIT		5
#define MB_NONE		-1


class CMenu {

	public:
		CMenu();
		~CMenu();

        static CMenu* pGetInstance();
        void init();
		void reset();
		void setContinuar(bool c);
		int	update(float time);
        void draw();


	private:

        struct Posicio{
            float posx;
            float posy;
            float posz;
        };
        
        struct Opcio {
           int opcio;
           GLuint textureA;
		   GLuint textureD;
        };

        Posicio menu_posicions[5];
		Opcio menu_opcions[5];
		CInput* input;
        CModels* models;

		CTextureManager* texman;
		emyl::sound* soMenu;

        int opcio_actual, imatge_fons;
		bool continuar;
        static CMenu* m_pInstance;

};
