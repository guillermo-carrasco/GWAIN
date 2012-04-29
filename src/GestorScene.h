#pragma once

#include "Enemic.h"
#include "EnemicLila.h"
#include "EnemicBlau.h"
#include "EnemicVermell.h"
#include "EnemicVermellFill.h"
#include "EnemicVerd.h"
#include "EnemicGroc.h"
#include "EnemicEnergyBall.h"
#include "EnemicCreador.h"
#include "Objecte.h"
#include "SoundManager.h"
#include <fstream>



class CGestorScene
{
	public:
		~CGestorScene(void);

		static CGestorScene* pGetInstance();

		void init();
		void update(float time);

	private:
		CGestorScene();

		static CGestorScene* m_pInstance;

		CSoundManager* soundman;

		void creaEnemic(int tipus);
		void creaObjecte();
		
		int		e_timeMin[NUM_ENEMICS];
		int		e_timeRange[NUM_ENEMICS];
		float	e_timeToCreate[NUM_ENEMICS];

		float	o_timeFirst[NUM_OBJECTES];
		int		o_timeMin;
		int		o_timeRange;
		float	o_timeToCreate;
};
