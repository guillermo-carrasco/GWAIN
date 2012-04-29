#include "EnemicVermellFill.h"


CEnemicVermellFill::CEnemicVermellFill(void)
{
}


CEnemicVermellFill::~CEnemicVermellFill(void)
{
}


void CEnemicVermellFill::init(void* v) {
	mv = *((float*)v);
	model = M_ENEM7;
	w = h = 1.0f;
	power = 1;
	punts = 25;
	life = 1;
	timeR = 800;
	time0 = 400;
	color1[0] = 1.0f;
	color1[1] = 0.1f;
	color1[2] = 0.1f;
	color2[0] = 1.0f;
	color2[1] = 0.4f;
	color2[2] = 0.2f;

	randomVel();
}


void CEnemicVermellFill::update(float time) {
	moveAcum -= 1000.0f*time;
	if (moveAcum < 0) randomVel();
	pos += vel/10.0f;
}


void CEnemicVermellFill::repBala() {
	life--;
	mor();
}

int CEnemicVermellFill::getTipus() {
	return ENEMIC_VEMF;
}
