#include "GestorScene.h"
#include "Scene.h"


CGestorScene* CGestorScene::m_pInstance = 0;


CGestorScene::CGestorScene(void)
{
}

CGestorScene::~CGestorScene(void)
{
}

CGestorScene* CGestorScene::pGetInstance()
{
	if (CGestorScene::m_pInstance == 0)
	{
		CGestorScene::m_pInstance = new CGestorScene();
	}
	return CGestorScene::m_pInstance;
}


void CGestorScene::init() {
	std::fstream dades;
	dades.open("./data/escena.txt", std::ios::in);

	for (int i = 0; i < NUM_ENEMICS; i++) {
		std::string s;
		float f0;
		int fm, fr;
		dades >> s >> f0 >> fm >> fr;
		e_timeToCreate[i] = f0;
		e_timeMin[i] = fm;
		e_timeRange[i] = fr;
	}
	char c;
	dades >> c;
	for (int i = 0; i < NUM_OBJECTES; i++) {
		std::string s;
		float t;
		dades >> s >> t;
		o_timeFirst[i] = t;
	}
	dades >> o_timeMin >> o_timeRange >> o_timeToCreate;
	
	dades.close();

	soundman = CSoundManager::pGetInstance();
}



void CGestorScene::update(float time) {

	//actualitzem les creacions d'enemics
	for (int i = 0; i < NUM_ENEMICS; i++) {
		e_timeToCreate[i] -= time;
		if (e_timeToCreate[i] < 0.0f) {
			creaEnemic(i);
		}
	}

	//anem avançan el primer instant en que crearíem l'objecte iessim
	for (int i = 0; i < NUM_OBJECTES; i++) {
		if (o_timeFirst[i] > 0.0f) o_timeFirst[i] -= time;
	}
	//i si cal creem un objecte
	o_timeToCreate -= time;
	if (o_timeToCreate < 0.0f) {
		creaObjecte();
	}
}


void CGestorScene::creaEnemic(int tipus) {
	//l'escena te enemics limitats
	CScene* scn = CScene::pGetInstance();
	if (scn->getNumEnemics() >= MAX_ENEMICS) return;

	float pos[3];
	scn->buscaPosicioLliure(pos);

	switch(tipus) {
		case ENEMIC_LILA: {
			CEnemicLila* e = new CEnemicLila();
			float v = float(rand()%6-3)+15.0f;
			e->init((void*)&v);
			e->setPos(pos[0], pos[1], pos[2]);
			scn->afegirEnemic(e);
			}
			break;
		case ENEMIC_BLAU: {
			CEnemicBlau* e = new CEnemicBlau();
			e->init(0);
			e->setPos(pos[0], pos[1], pos[2]);
			scn->afegirEnemic(e);
			}
			break;
		case ENEMIC_VERD: {
			CEnemicVerd* e = new CEnemicVerd();
			e->init(0);
			e->setPos(pos[0], pos[1], pos[2]);
			scn->afegirEnemic(e);
			}
			break;
		case ENEMIC_GROC: {
			CEnemicGroc* e = new CEnemicGroc();
			e->init(0);
			e->setPos(pos[0], pos[1], pos[2]);
			scn->afegirEnemic(e);
			}
			break;
		case ENEMIC_VERM: {
			CEnemicVermell* e = new CEnemicVermell();
			e->init(0);
			e->setPos(pos[0], pos[1], pos[2]);
			scn->afegirEnemic(e);
			}
			break;
		case ENEMIC_VEMF: {
			CEnemicVermellFill* e = new CEnemicVermellFill();
			float v = float(rand()%6-3)+10.0f;
			e->init((void*)&v);
			e->setPos(pos[0], pos[1], pos[2]);
			scn->afegirEnemic(e);
			}
			break;
		case ENEMIC_BOLA: {
			CEnemicEnergyBall* e = new CEnemicEnergyBall();
			e->init(0);
			e->setPos(pos[0], pos[1], pos[2]);
			scn->afegirEnemic(e);
			}
			break;
		case ENEMIC_CREA: {
			CEnemicCreador* e = new CEnemicCreador();
			int ecre = rand()%NUM_CREADORS;
			e->init((void*)&ecre);
			e->setPos(pos[0], pos[1], pos[2]);
			scn->afegirEnemic(e);
			}
			break;
		default:
			break;
	}

	e_timeToCreate[tipus] = float(rand()%e_timeRange[tipus] + e_timeMin[tipus]);
	
	if (tipus == ENEMIC_CREA) soundman->play(SO_NOUCREADOR, pos[0], pos[1], pos[2]);
	//else soundman->play(SO_NOUENEMIC, pos[0], pos[1], pos[2]);   <-- massa rallant XD

	return;
}

void CGestorScene::creaObjecte() {
	//si encara no podem crear-ne d'aquells no fem res
	int tipus = rand()%NUM_OBJECTES;
	if (o_timeFirst[tipus] > 0.0f) return;

	//creem l'objecte i l'inserim a l'escena
	CScene* scn = CScene::pGetInstance();
	float pos[3];
	scn->buscaPosicioLliure(pos);
	CObjecte* obj = new CObjecte();
	obj->init(tipus);
	obj->setPos(pos[0], pos[1], pos[2]);
	scn->afegirObjecte(obj);
	
	//recalculem un nou temps
	o_timeToCreate = float(rand()%o_timeRange + o_timeMin);

	soundman->play(SO_NOUOBJECTE, pos[0], pos[1], pos[2]);

	return;
}
