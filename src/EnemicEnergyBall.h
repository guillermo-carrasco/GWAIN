#pragma once

#include "Globals.h"
#include "Models.h"
#include "Enemic.h"
#include <cmath>


class CEnemicEnergyBall : public CEnemic
{
	public:
		CEnemicEnergyBall(void);
		~CEnemicEnergyBall(void);

		int getTipus();
		void init(void* foo);
		void update(float time);
		void repBala();

};
