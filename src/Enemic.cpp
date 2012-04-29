#include "Enemic.h"
#include "Scene.h"


CEnemic::CEnemic(void)
{
	modelador = CModels::pGetInstance();
}

CEnemic::~CEnemic(void)
{
}

void CEnemic::update(float time) {
}


void CEnemic::draw() {
	glPushMatrix();
		glTranslatef(pos.getX(), 0.0f, pos.getZ());
		glRotatef(angleDir, 0.0f, 1.0f, 0.0f);
		modelador->dibuixa(model);
	glPopMatrix();
}

CBBox CEnemic::getBB(void) {
	CBBox bb;
	bb.left = pos.getX() - w;
	bb.right = pos.getX() + w;
	bb.top = pos.getZ() + h;
	bb.bottom = pos.getZ() - h;
	return bb;
}


int CEnemic::getPower(void) {
	return power;
}

int CEnemic::getPunts(void) {
	return punts;
}

bool CEnemic::esViu(void) {
	return life > 0;
}

void CEnemic::setPos(float px, float py, float pz) {
	pos.setVector(px, py, pz);
}

void CEnemic::getPos(float p[3]) {
	pos.getValues(p);
}

void CEnemic::mor() {
	CParticleSystem* p = new CParticleSystem();
	p->setTipus(PS_ONCE, 0.0f, PT_DOT, 0, 3.0f);
	p->setColor(color1, 1, true);
	p->setColor(color2, 1, false);
	p->setFading(1.0, 0.5f);
	p->setPosition(pos.getX(), pos.getY(), pos.getZ());
	p->setDirection(0.0f, 0.0f, -1.0f, 360.0f, 360.0f, 20.0f, 10.0f);
	p->init(16);
	CScene::pGetInstance()->afegirParticules(p);
}

void CEnemic::randomVel(void) {
	moveAcum = float(rand()%timeR + time0);
	int velx = rand()%1000-500;
	int velz = rand()%1000-500;
	vel.setVector(mv*(float(velx)/1000.0f), 
				  0.0f,
				  mv*(float(velz)/1000.0f));
	angleDir = (180.0f/M_PI)*atan(vel.getZ()/vel.getX());
	if (vel.getZ() < 0.0f) angleDir += 180.0f;
}

