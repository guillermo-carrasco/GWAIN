#include "EnemicCreador.h"

CEnemicCreador::CEnemicCreador(void)
{
}

CEnemicCreador::~CEnemicCreador(void)
{
}

void CEnemicCreador::init(void* v) {
	tipusCreador = *((int*)v);
	mv = 0.0f;
	model = M_ENEMC;
	timeR = 600;
	time0 = 100;
	w = h = 3.0f;
	power = 1;
	punts = 10000;
	life = 200;
	switch(tipusCreador) {
		case ENCRE_LILA:
			color1[0] = 0.64f;
			color1[1] = 0.44f;
			color1[2] = 0.86f;
			color2[0] = 0.25f;
			color2[1] = 0.05f;
			color2[2] = 0.47f;
			break;
		case ENCRE_BLAU:
			color1[0] = 0.0f;
			color1[1] = 0.7f;
			color1[2] = 1.0f;
			color2[0] = 0.2f;
			color2[1] = 0.8f;
			color2[2] = 1.0f;
			break;
		case ENCRE_VERD:
			color1[0] = 0.3f;
			color1[1] = 1.0f;
			color1[2] = 0.3f;
			color2[0] = 0.5f;
			color2[1] = 1.0f;
			color2[2] = 0.5f;
			break;
		default:
			color1[0] = 1.0f;
			color1[1] = 1.0f;
			color1[2] = 1.0f;
			color2[0] = 1.0f;
			color2[1] = 1.0f;
			color2[2] = 1.0f;
			break;
	}
	color1[0] = 0.64f;
	color1[1] = 0.44f;
	color1[2] = 0.86f;
	color2[0] = 0.25f;
	color2[1] = 0.05f;
	color2[2] = 0.47f;

	createTime = 1000.0f;
}


void CEnemicCreador::update(float time) {
	createTime -= 1000.0f*time;
	if (createTime < 0) {
		createTime = float(rand()%TIME_RANGE+TIME_MIN);
		int rafega = rand()%PROB_RAF;
		int nombre = 1;
		if (rafega == 0) nombre = rand()%RAF_RANGE + RAF_MIN;
		CScene* scn = CScene::pGetInstance();
		for (int i = 0; i < nombre; i++) {
			if (scn->getNumEnemics() >= MAX_ENEMICS) break;
			float anglePos = float(rand()%6283)/1000.0f;
			float cospos = cos(anglePos);
			float sinpos = sin(anglePos);

			switch(tipusCreador) {
				case ENCRE_LILA: {
					CEnemicLila* el = new CEnemicLila();
					float vvel = 12.0f;
					el->init((void*)&vvel);
					el->setPos(pos.getX()+sinpos, 0.0f, pos.getZ()+cospos);
					scn->afegirEnemic(el);
					}
					break;
				case ENCRE_BLAU: {
					CEnemicBlau* eb = new CEnemicBlau();
					eb->init(0);
					eb->setPos(pos.getX()+sinpos, 0.0f, pos.getZ()+cospos);
					scn->afegirEnemic(eb);
					}
					break;
				case ENCRE_VERD: {
					CEnemicVerd* ev = new CEnemicVerd();
					ev->init(0);
					ev->setPos(pos.getX()+sinpos, 0.0f, pos.getZ()+cospos);
					scn->afegirEnemic(ev);
					}
					break;
				default:
					break;
			}
		}
	}
}


void CEnemicCreador::repBala() {
	life--;
	if (life < 0) mor();
}

int CEnemicCreador::getTipus() {
	return ENEMIC_CREA;
}

