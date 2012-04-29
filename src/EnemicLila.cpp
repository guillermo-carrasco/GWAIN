#include "EnemicLila.h"


CEnemicLila::CEnemicLila(void)
{
}


CEnemicLila::~CEnemicLila(void)
{
}


void CEnemicLila::init(void* v) {
	mv = *((float*)v);
	model = M_ENEM1;
	timeR = 600;
	time0 = 300;
	w = h = 1.8f;
	power = 1;
	punts = 5;
	life = 1;
	color1[0] = 0.64f;
	color1[1] = 0.44f;
	color1[2] = 0.86f;
	color2[0] = 0.25f;
	color2[1] = 0.05f;
	color2[2] = 0.47f;

	randomVel();
}


void CEnemicLila::update(float time) {
	moveAcum -= 1000.0f*time;
	if (moveAcum < 0) randomVel();
	pos += vel/10.0f;
}


void CEnemicLila::repBala() {
	life--;
	mor();
}

int CEnemicLila::getTipus() {
	return ENEMIC_LILA;
}

