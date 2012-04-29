#include "EnemicVermell.h"
#include "Scene.h"


CEnemicVermell::CEnemicVermell(void)
{
}


CEnemicVermell::~CEnemicVermell(void)
{
}


void CEnemicVermell::init(void* foo) {
	model = M_ENEM6;
	w = h = 2.5f;
	angleDir = 0.0f;
	power = 5;
	punts = 100;
	life = 5;
	mv = 20.0f;
	timeR = 1000;
	time0 = 2000;
	color1[0] = 1.0f;
	color1[1] = 0.1f;
	color1[2] = 0.1f;
	color2[0] = 1.0f;
	color2[1] = 0.4f;
	color2[2] = 0.2f;
}


void CEnemicVermell::update(float time) {
	float p[3];
	bool vis;
	CScene::pGetInstance()->getPlayerPos(p, vis);
	if (vis && getBB().circle(p[0], p[2], RADI_VISTA)) {
		CVector3 dir(p[0], p[1], p[2]);
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


void CEnemicVermell::repBala() {
	life--;
	if (life <= 0) {
		float venli = 4.5f;
		for (int i = 0; i < 5; i++) {
			CEnemicVermellFill* evf = new CEnemicVermellFill();
			evf->init((void*)&venli);
			evf->setPos(pos.getX(), pos.getY(), pos.getZ());
			CScene::pGetInstance()->afegirEnemic(evf);
		}
		mor();
	}
}

int CEnemicVermell::getTipus() {
	return ENEMIC_VERM;
}
