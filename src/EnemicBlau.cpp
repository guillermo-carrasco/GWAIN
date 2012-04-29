#include "EnemicBlau.h"
#include "Scene.h"


CEnemicBlau::CEnemicBlau(void)
{
}


CEnemicBlau::~CEnemicBlau(void)
{
}


void CEnemicBlau::init(void* foo) {
	angleDir = 0.0f;
	model = M_ENEM2;
	w = h = 1.5f;
	power = 2;
	punts = 10;
	life = 1;
	mv = 30.0f;
	timeR = 200;
	time0 = 200;
	color1[0] = 0.0f;
	color1[1] = 0.7f;
	color1[2] = 1.0f;
	color2[0] = 0.2f;
	color2[1] = 0.8f;
	color2[2] = 1.0f;
}


void CEnemicBlau::update(float time) {
	float p[3];
	bool vis;
	CScene::pGetInstance()->getPlayerPos(p, vis);
	CVector3 dir(p[0], p[1], p[2]);
	if (vis) {
		dir -= pos;
		dir.normalize();
		vel = dir*mv;
	}
	else {
		moveAcum -= 1000.0f*time;
		if (moveAcum < 0.0f) randomVel();
	}
	pos += vel*time;
	angleDir = (180.0f/M_PI)*atan(vel.getZ()/vel.getX());
}


void CEnemicBlau::repBala() {
	life--;
	if (life <= 0) mor();
}


int CEnemicBlau::getTipus() {
	return ENEMIC_BLAU;
}