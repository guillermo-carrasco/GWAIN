#pragma once

#include "Globals.h"
#include "Models.h"
#include "Enemic.h"
#include <cmath>


#define RADI_BALES 20.0f

class CEnemicVerd : public CEnemic
{
	public:
		CEnemicVerd(void);
		~CEnemicVerd(void);

		int getTipus();
		void init(void* foo);
		void update(float time);
		void repBala();

};
