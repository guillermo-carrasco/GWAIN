#include "EnemicGroc.h"
#include "Scene.h"


CEnemicGroc::CEnemicGroc(void)
{
}


CEnemicGroc::~CEnemicGroc(void)
{
}


void CEnemicGroc::init(void* foo) {
	model = M_ENEM5;
	angleDir = 0.0f;
	w = h = 1.5f;
	power = 2;
	punts = 500;
	life = 5;
	mv = 40.0f;
	color1[0] = 1.0f;
	color1[1] = 1.0f;
	color1[2] = 0.1f;
	color2[0] = 1.0f;
	color2[1] = 1.0f;
	color2[2] = 0.5f;

	estat = EGS_WAIT;
	timeAcum = WAIT_TIME;
	timeToDraw = 0.3f;
	visible = true;
}


void CEnemicGroc::update(float time) {
	timeAcum -= time;

	switch(estat) {
		case EGS_WAIT:
			if (timeAcum < 0.0f) {
				float ppos[3];
				bool vis;
				CScene::pGetInstance()->getPlayerPos(ppos, vis);
				vel.setVector(ppos[0], ppos[1], ppos[2]);
				vel -= pos;
				vel.normalize();
				vel = vel*mv;
				estat = EGS_MOVE;
				timeAcum = MOVE_TIME;
			}
			break;
		case EGS_MOVE:
			pos += vel*time;
			if (timeAcum < 0.0f) {
				int r = rand()%5;
				if (r != 0) {
					estat = EGS_WAIT;
					timeAcum = WAIT_TIME;
				}
				else {
					estat = EGS_FADO;
					timeAcum = FADE_TIME;
				}
			}
			break;
		case EGS_FADO:
			timeToDraw -= time;
			if (timeToDraw < 0.0f) visible = !visible;

			if (timeAcum < 0.0f) {
				int w, h;
				CScene::pGetInstance()->getBounds(w, h);
				pos.setVector(float(rand()%w-w/2), 
							  0.0f, 
							  float(rand()%h-h/2));
				estat = EGS_FADI;
				timeAcum = FADE_TIME;
			}
			break;
		case EGS_FADI:
			timeToDraw -= time;
			if (timeToDraw < 0.0f) visible = !visible;

			if (timeAcum < 0.0f) {
				estat = EGS_WAIT;
				visible = true;
			}
			break;
		default:
			break;
	}
}


void CEnemicGroc::repBala() {
	if (estat == EGS_MOVE || estat == EGS_WAIT) life--;
	if (life <= 0) mor();
}


void CEnemicGroc::draw(void) {
	if (visible) {
		CEnemic::draw();
	}
}

int CEnemicGroc::getTipus() {
	return ENEMIC_GROC;
}
