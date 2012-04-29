#include "EnemicVerd.h"
#include "Scene.h"


CEnemicVerd::CEnemicVerd(void)
{
}


CEnemicVerd::~CEnemicVerd(void)
{
}


void CEnemicVerd::init(void* foo) {
	model = M_ENEM3;
	w = h = 1.5f;
	angleDir = 0.0f;
	power = 3;
	punts = 200;
	life = 3;
	mv = 20.0f;
	timeR = 200;
	time0 = 200;
	color1[0] = 0.3f;
	color1[1] = 1.0f;
	color1[2] = 0.3f;
	color2[0] = 0.5f;
	color2[1] = 1.0f;
	color2[2] = 0.5f;
}


void CEnemicVerd::update(float time) {
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
	
	/**mes complicat pel tema de les bales*/
	std::vector<CBala*> bales = CScene::pGetInstance()->getVectorBales();
	for (unsigned int i = 0; i < bales.size(); i++) {
		CBBox bb = getBB();
		if (bb.circle(bales[i]->x, bales[i]->z, RADI_BALES)) {
			CVector3 v1(bales[i]->x, 0.0f, bales[i]->z);
			CVector3 norm = v1^pos;
			float cosv = v1*pos;
			if (norm.getY() >= 0.0f && cosv >= 0.0f) { 
				vel.addVector(-bales[i]->vz, 0.0f, bales[i]->vx);
			}
			else if (cosv >= 0.0f)	{
				vel.addVector(bales[i]->vz, 0.0f, -bales[i]->vx);
			}
		}
	}
	vel.normalize();
	pos += vel*time*mv;
	angleDir = (180.0f/M_PI)*atan(vel.getZ()/vel.getX());
}


void CEnemicVerd::repBala() {
	life--;
	if (life <= 0) mor();
}

int CEnemicVerd::getTipus() {
	return ENEMIC_VERD;
}
