#include "Bala.h"
#include "Globals.h"



CBala::CBala(float anglerad, float _x, float _z)
{
	x = _x;
	z = _z;
	vx = VEL_BALA*sin(anglerad);
	vz = VEL_BALA*cos(anglerad);
	angle = anglerad*180.0f/M_PI;
}

CBala::~CBala(void)
{
}

void CBala::step(float time) {
	x += time*vx;
	z += time*vz;
}

void CBala::draw() {
	glPushMatrix();
		glTranslatef(x, 0, z);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		CModels::pGetInstance()->dibuixa(M_BALA);
	glPopMatrix();
}
