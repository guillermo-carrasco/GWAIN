#include "SoundManager.h"

CSoundManager::CSoundManager(void)
{
}

CSoundManager::~CSoundManager(void)
{
}

CSoundManager* CSoundManager::m_pInstance = 0;

CSoundManager* CSoundManager::pGetInstance() {
	if (CSoundManager::m_pInstance == 0)
	{
		CSoundManager::m_pInstance = new CSoundManager();
	}
	return CSoundManager::m_pInstance;
}

void CSoundManager::loadSounds() {
	soundman = emyl::manager::get_instance();
	this->setListener(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f); 

	loadSound(SO_INICI, "./data/sounds/start.ogg");
	loadSound(SO_GAMEOVER, "./data/sounds/gameover.ogg");
	loadSound(SO_MENU, "./data/sounds/menu.ogg");

	//sons no atenuats
	for(int i = SO_INICI; i <= SO_MENU; i++) {
		ALuint source = sons[i]->get_source();
		alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
		alSourcef(source, AL_MAX_DISTANCE, 0.0f);
	}

	loadSound(SO_BALA, "./data/sounds/bala.ogg");
	loadSound(SO_PLAYERHIT, "./data/sounds/mal.ogg");
	loadSound(SO_PLAYERMOR, "./data/sounds/mor.ogg");

	loadSound(SO_NOUENEMIC, "./data/sounds/nouenemic.ogg");
	loadSound(SO_NOUCREADOR, "./data/sounds/noucreador.ogg");
	loadSound(SO_NOUOBJECTE, "./data/sounds/nouobjecte.ogg");

	loadSound(SO_ENEMICHIT, "./data/sounds/hitenemic.ogg");
	loadSound(SO_ENEMICMOR, "./data/sounds/morenemic.ogg");

	loadSound(SO_AGAFAOBJ, "./data/sounds/agafaobjecte.ogg");
	loadSound(SO_BOMBA, "./data/sounds/bomba.ogg");

	//sons atenuats
	for(int i = SO_BALA; i <= SO_BOMBA; i++) {
		ALuint source = sons[i]->get_source();
		alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
		alSourcef(source, AL_MAX_DISTANCE, 0.0f);
	}
}


void CSoundManager::play(int so) {
	sons[so]->play();
}

void CSoundManager::play(int so, float x, float y, float z) {
	sons[so]->set_position(x, y, z);
	sons[so]->play();
}

void CSoundManager::stopAll() {
	for (int i = 0; i < NUM_SONS; i++) {
		sons[i]->stop();
	}
}

void CSoundManager::loadSound(int so, char* file) {
	sons[so] = new emyl::sound();
	ALuint buffer = soundman->get_buffer(file);
	sons[so]->set_source();
	sons[so]->set_buffer(buffer);
}

void CSoundManager::setListener(float x, float y, float z, 
				 float dx, float dy, float dz,
				 float ux, float uy, float uz) 
{
	float pos[3] = {x, y, z};
	float orient[6] = {dx, dy, dz, ux, uy, uz};
	alListenerfv(AL_POSITION, pos);
	alListenerfv(AL_ORIENTATION, orient);
}


