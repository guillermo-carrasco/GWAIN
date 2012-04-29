#pragma once

#include "Globals.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define	MAX_PARTICLES	1000

#define PS_LOOP		1
#define PS_ONCE		2
#define PS_TIMED	3

#define PT_DOT		1
#define PT_LINE		2
#define PT_TEX		3


typedef struct						// Create A Structure For Particle
{
	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	r0;						// Red Value
	float	g0;						// Green Value
	float	b0;						// Blue Value
	float	rf;						// Red Value
	float	gf;						// Green Value
	float	bf;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// X Gravity
	float	yg;						// Y Gravity
	float	zg;						// Z Gravity
	float	xs;						// X size
	float	ys;						// Y size
	float	zs;						// Z size
}
Particle;							// Particles Structure


class CParticleSystem
{
	public:
		CParticleSystem(void);
		~CParticleSystem(void);

		void setTipus(int tipus, float lifetime, int tipusP, GLuint tex, float mida);
		void setColor(float *color, int n, bool ini);
		void setFading(float fr, float f0);
		void setPosition(float x, float y, float z);
		void setDirection(float dx, float dy, float dz, float angXY,
						  float angZ, float velR, float v0);
		void setRotacio(float rot);
		
		void init(int numparts);
		void initParticle(int i);

		void update(float time);
		void draw(void);
		bool isActive();

	private:
		Particle particle[MAX_PARTICLES];	// Particle Array (Room For Particle Info)
		GLuint textura;
		bool actiu;
		int numParts;
		int tipusPart;
		int tipusEmisor;
		float totalTime;

		float posX, posY, posZ;
		float dirX, dirY, dirZ;
		float angleXY, angleZ, rotacio;
		float velRange, vel0;
		float size;

		float *colorsI;
		int numColorsI;
		float *colorsF;
		int numColorsF;
		float fadeR, fade0;
};
