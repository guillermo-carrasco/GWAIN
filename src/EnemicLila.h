#pragma once

#include "Globals.h"
#include "Models.h"
#include "Enemic.h"
#include "stdlib.h"
#include "time.h"
#include <cmath>



class CEnemicLila : public CEnemic
{
	public:
		CEnemicLila(void);
		~CEnemicLila(void);

		int getTipus();
		void init(void* v);
		void update(float time);
		void repBala();

};
