#pragma once

#include "emyl.h"


enum {
	SO_INICI,
	SO_GAMEOVER,
	SO_MENU,
	SO_BALA,
	SO_PLAYERHIT,
	SO_PLAYERMOR,
	SO_NOUENEMIC,
	SO_NOUCREADOR,
	SO_NOUOBJECTE,
	SO_ENEMICHIT,
	SO_ENEMICMOR,
	SO_AGAFAOBJ,
	SO_BOMBA,
	NUM_SONS
};


class CSoundManager
{
	public:		
		~CSoundManager(void);
		static CSoundManager* pGetInstance();

		void loadSound(int so, char* file);
		void loadSounds();
		void play(int so);
		void play(int so, float x, float y, float z);
		void stopAll();
		void setListener(float x, float y, float z, 
						 float dx, float dy, float dz,
						 float ux, float uy, float uz); 

	private:
		CSoundManager(void);

		static CSoundManager *m_pInstance;
		emyl::manager *soundman; 
		emyl::sound*   sons[NUM_SONS];		
};
