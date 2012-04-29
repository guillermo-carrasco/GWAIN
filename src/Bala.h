#pragma once


#include "Globals.h"
#include "Models.h"
#include <cmath>


#define VEL_BALA	250.0f


class CBala
{
	public:
		CBala(float angle, float _x, float _z);
		~CBala(void);
		
		void step(float time);
		void draw();

		float x, z;
		float vx, vz;
		float angle;
};
