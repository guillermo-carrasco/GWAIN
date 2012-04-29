#include "Input.h"



CInput* CInput::m_pInstance = 0;

CInput::CInput() {
	DoExit = false;
	m_pSettings = CSettings::pGetInstance();	

	//inicialment no tenim cap tecla premuda
	for (int i = 0; i < Nkeys; i++) keys[i] = KEY_OFF;	
}

CInput::~CInput() { 
	m_pInstance = NULL; 
}

CInput* CInput::pGetInstance() {
	if(m_pInstance == NULL)
		m_pInstance = new CInput();

	return m_pInstance;
}

void CInput::update() {
	//Les tecles que anteriorment estaven en RELEASED passen a OFF
	//Les tecles que anteriorment estaven en PRESSED passen a ON
	for (int i = 0; i < Nkeys; i++) keys[i] = keys[i] & 0xFFFD;

    //Quan premem una tecla passa a PRESSED i quan la deixem anar a RELEASED
	
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				for (int i = 0; i < Nkeys; i++) {
					if( event.key.keysym.sym == m_pSettings->Keyboard[i]) {
						keys[i] = KEY_PRESSED;
					}
				}
			break;
			case SDL_KEYUP:
				for (int i = 0; i < Nkeys; i++) {
					if( event.key.keysym.sym == m_pSettings->Keyboard[i]) {
						keys[i] = KEY_RELEASED;
					}
				}
			break;
			case SDL_QUIT:
				DoExit = true;
				keys[kEsc] = KEY_PRESSED;
				break;
			default:
			break;
		}
   	}

	m_GlobalTime = ((float)SDL_GetTicks())/1000.0f;
	
}

float CInput::getGlobalTime() { 
	return m_GlobalTime;
}

bool  CInput::bExit() { 
	return DoExit || keys[kEsc]; 
}

//Comprovem si una tecla esta premuda
bool CInput::check(unsigned char key) {
    return keys[key] == KEY_ON || keys[key] == KEY_PRESSED;    
}

//Comprovem si acabem de premer una tecla
bool CInput::checkPress(unsigned char key) {
    return keys[key] == KEY_PRESSED;
}

//Comprovem si acabem de deixar anar una tecla
bool CInput::checkRelease(unsigned char key) {
    return keys[key] == KEY_RELEASED;
}
