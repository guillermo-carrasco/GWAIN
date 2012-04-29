#pragma once

#include "Globals.h"
#include "Models.h"
#include "Enemic.h"
#include "stdlib.h"
#include "time.h"
#include <cmath>



class CEnemicVermellFill : public CEnemic
{
	public:
		CEnemicVermellFill(void);
		~CEnemicVermellFill(void);

		int getTipus();
		void init(void* v);
		void update(float time);
		void repBala();

	private:
		void novaVel(void);

};
