#pragma once

#include "Globals.h"
#include "Models.h"
#include "Enemic.h"
#include "EnemicVermellFill.h"
#include <cmath>


#define RADI_VISTA 25.0f


class CEnemicVermell : public CEnemic
{
	public:
		CEnemicVermell(void);
		~CEnemicVermell(void);

		int getTipus();
		void init(void* foo);
		void update(float time);
		void repBala();
};
