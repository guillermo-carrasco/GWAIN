#pragma once

#include "Globals.h"
#include "Models.h"
#include "Enemic.h"
#include <cmath>


class CEnemicBlau : public CEnemic
{
	public:
		CEnemicBlau(void);
		~CEnemicBlau(void);

		int getTipus();
		void init(void* foo);
		void update(float time);
		void repBala();

};
