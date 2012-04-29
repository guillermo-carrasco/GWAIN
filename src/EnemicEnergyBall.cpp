#include "EnemicEnergyBall.h"
#include "Scene.h"


CEnemicEnergyBall::CEnemicEnergyBall(void)
{
}


CEnemicEnergyBall::~CEnemicEnergyBall(void)
{
}


void CEnemicEnergyBall::init(void* foo) {
	model = M_ENEM4;
	w = h = 0.5f;
	power = -1;
	punts = 1000;
	life = 1;
	mv = 40.0f;
	timeR = 100;
	time0 = 100;
	color1[0] = 0.1f;
	color1[1] = 0.4f;
	color1[2] = 1.0f;
	color2[0] = 0.3f;
	color2[1] = 0.8f;
	color2[2] = 1.0f;
}


void CEnemicEnergyBall::update(float time) {
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
}


void CEnemicEnergyBall::repBala() {
	life--;
	if (life <= 0) mor();
}

int CEnemicEnergyBall::getTipus() {
	return ENEMIC_BOLA;
}
