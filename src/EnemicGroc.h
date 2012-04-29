#pragma once

#include "Globals.h"
#include "Models.h"
#include "Enemic.h"
#include "stdlib.h"
#include "time.h"
#include <cmath>


#define EGS_MOVE 1
#define EGS_WAIT 2
#define EGS_FADO 3
#define EGS_FADI 4

#define FADE_TIME 1.5f
#define MOVE_TIME 5.0f
#define WAIT_TIME 0.5f


class CEnemicGroc : public CEnemic
{
	public:
		CEnemicGroc(void);
		~CEnemicGroc(void);

		int getTipus();
		void init(void* foo);
		void update(float time);
		void draw();
		void repBala();

	private:
		float timeAcum, timeToDraw;
		int estat;
		bool visible;
};
