#pragma once

#include "Globals.h"
#include "Models.h"
#include "BBox.h"
#include "Vector3.h"
#include "ParticleSystem.h"


enum {
	ENEMIC_LILA,
	ENEMIC_BLAU,
	ENEMIC_VERD,
	ENEMIC_GROC,
	ENEMIC_VERM,
	ENEMIC_VEMF,
	ENEMIC_BOLA,
	ENEMIC_CREA,
	NUM_ENEMICS
};


class CEnemic
{
	public:
		CEnemic(void);
		~CEnemic(void);

		virtual void init(void* data) = 0;
		virtual int  getTipus() = 0;		
		virtual void update(float time) = 0;
		virtual void repBala() = 0;
		virtual void draw();

		void randomVel();
		CBBox getBB(void);
		int getPower();
		int getPunts();
		void mor();
		bool esViu();
		void getPos(float pos[3]);
		void setPos(float px, float py, float pz);
		
	protected:
		CVector3 pos;
		CVector3 vel;
		CVector3 acc;
		float angleDir;
		float w, h;
		float mv;

		int power, life, punts;

		float color1[3];
		float color2[3];
		unsigned int model;
		CModels* modelador;

		float moveAcum;
		int timeR, time0;
};
