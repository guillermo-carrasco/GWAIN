#include "Objecte.h"

CObjecte::CObjecte(void)
{
}

CObjecte::~CObjecte(void)
{
}


void CObjecte::init(int tip) {
	tipus = tip;
	w = h = 3.0f;
	novaVel();
	modelador = CModels::pGetInstance();
	textura = CTextureManager::pGetInstance()->loadTexture("objectes");
	switch(tip) {
		case OBJ_1VIDA:
			tp.l = 0.0f;
			tp.r = 0.25f;
			tp.t = 0.0f;
			tp.b = 0.5f;
			break;
		case OBJ_SALUT:
			tp.l = 0.0f;
			tp.r = 0.25f;
			tp.t = 0.5f;
			tp.b = 1.0f;
			break;
		case OBJ_POWER:
			tp.l = 0.25f;
			tp.r = 0.5f;
			tp.t = 0.0f;
			tp.b = 0.5f;
			break;
		case OBJ_SPEED:
			tp.l = 0.75f;
			tp.r = 1.0f;
			tp.t = 0.0f;
			tp.b = 0.5f;
			break;
		case OBJ_BOMBA:
			tp.l = 0.25f;
			tp.r = 0.5f;
			tp.t = 0.5f;
			tp.b = 1.0f;
			break;
		case OBJ_INVIS:
			tp.l = 0.5f;
			tp.r = 0.75f;
			tp.t = 0.0f;
			tp.b = 0.5f;
			break;
		case OBJ_INVEN:
			tp.l = 0.5f;
			tp.r = 0.75f;
			tp.t = 0.5f;
			tp.b = 1.0f;
			break;
		default:
			break;
	}
}


void CObjecte::update(float time) {
	timeacum -= 1000.0f*time;
	if (timeacum < 0) novaVel();
	pos += vel/10.0f;
}


void CObjecte::novaVel(void) {
	timeacum = float(rand()%OBJ_TIME_RANGE + OBJ_TIME_MIN);
	int x = rand()%1000-500;
	int z = rand()%1000-500;
	vel.setVector(2.0f*(float(x)/1000.0f), 
				  0.0f,
				  2.0f*(float(z)/1000.0f));
	angleDir = (180.0f/M_PI)*atan(vel.getZ()/vel.getX());
	if (vel.getZ() < 0.0f) angleDir += 180.0f;
}


void CObjecte::draw() {
	glPushMatrix();
		glTranslatef(pos.getX(), pos.getY(), pos.getZ());
		glRotatef(angleDir, 0.0f, 1.0f, 0.0f);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura);
		glColor3f(1.0f, 1.0f, 1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_QUADS);
			glTexCoord2f(tp.l, tp.t); glVertex3f( w, h, 0.0f);
			glTexCoord2f(tp.l, tp.b); glVertex3f( w, -h, 0.0f);
			glTexCoord2f(tp.r, tp.b); glVertex3f(-w, -h, 0.0f);
			glTexCoord2f(tp.r, tp.t); glVertex3f(-w, h, 0.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		modelador->dibuixa(M_OBJS);

	glPopMatrix();
}


int CObjecte::getTipus() {
	return tipus;
}


CBBox CObjecte::getBB(void) {
	CBBox bb;
	bb.left = pos.getX() - w;
	bb.right = pos.getX() + w;
	bb.top = pos.getZ() + h;
	bb.bottom = pos.getZ() - h;
	return bb;
}

void CObjecte::setPos(float px, float py, float pz) {
	pos.setVector(px, py, pz);
}

void CObjecte::getPos(float p[3]) {
	pos.getValues(p);
}
