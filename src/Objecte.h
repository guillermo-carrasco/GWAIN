#pragma once

#include "Globals.h"
#include "TextureManager.h"
#include "Models.h"
#include "BBox.h"
#include "Vector3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum {
	OBJ_1VIDA,
	OBJ_SALUT,
	OBJ_POWER,
	OBJ_SPEED,
	OBJ_BOMBA,
	OBJ_INVIS,
	OBJ_INVEN,
	NUM_OBJECTES	
};


#define OBJ_TIME_RANGE  1800
#define OBJ_TIME_MIN    1000

typedef struct {
	float l, r, t, b;
} TexPos ;


class CObjecte
{
	public:
		CObjecte(void);
		~CObjecte(void);

		void init(int tip);
		void update(float time);
		void draw();

		int  getTipus();
		CBBox getBB(void);
		void setPos(float px, float py, float pz);
		void getPos(float p[3]);

	protected:
		void novaVel();

		CVector3 pos;
		CVector3 vel;
		CVector3 acc;
		float w, h;
		float angleDir;
		float timeacum;
		TexPos tp;

		int tipus;
		GLuint textura;
		CModels* modelador;
};
