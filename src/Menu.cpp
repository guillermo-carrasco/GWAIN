#include "Menu.h"

CMenu* CMenu::m_pInstance = 0;

CMenu::CMenu(){
}

CMenu::~CMenu(){
}

void CMenu::init(){

    input = CInput::pGetInstance();
	texman = CTextureManager::pGetInstance();

	//Carreguem les textures
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

    menu_opcions[0].opcio = MB_PLAY;
    menu_opcions[0].textureA = texman->loadTexture("Acontinuar");
	menu_opcions[0].textureD = texman->loadTexture("Dcontinuar");
    menu_opcions[1].opcio = MB_NEWGAME;
    menu_opcions[1].textureA = texman->loadTexture("Anova");
	menu_opcions[1].textureD = texman->loadTexture("Dnova");
    menu_opcions[2].opcio = MB_CREDITS;
    menu_opcions[2].textureA = texman->loadTexture("Acredits");
	menu_opcions[2].textureD = texman->loadTexture("Dcredits");
    menu_opcions[3].opcio = MB_EXIT;
    menu_opcions[3].textureA = texman->loadTexture("Asortir");
	menu_opcions[3].textureD = texman->loadTexture("Dsortir");
    menu_opcions[4].opcio = MB_RANKING;
    menu_opcions[4].textureA = texman->loadTexture("Apuntuacions");
	menu_opcions[4].textureD = texman->loadTexture("Dpuntuacions");

	imatge_fons = texman->loadTexture("titol");

	//Inicialització del array de posicions predefinides
    menu_posicions[0].posx = 0;
    menu_posicions[0].posy = -4;
    menu_posicions[0].posz = -14;
    menu_posicions[1].posx = 8;
    menu_posicions[1].posy = -3;
    menu_posicions[1].posz = -18;
    menu_posicions[2].posx = 5;
    menu_posicions[2].posy = -1;
    menu_posicions[2].posz = -20;
    menu_posicions[3].posx = -5;
    menu_posicions[3].posy = -1;
    menu_posicions[3].posz = -20;
    menu_posicions[4].posx = -8;
    menu_posicions[4].posy = -3;
    menu_posicions[4].posz = -18;

	continuar = false;
	opcio_actual = 1;
}

void CMenu::reset() {
	if (continuar) opcio_actual = 0;
	else opcio_actual = 1;
}

void CMenu::setContinuar(bool c) {
	continuar = c;
}

CMenu* CMenu::pGetInstance(){
	if (CMenu::m_pInstance == 0)
	{
		m_pInstance = new CMenu();
	}
	return m_pInstance;
}

int CMenu::update(float time) {

    //Actualitzem la opció actual
    if (input->checkPress(kLeft)) {
        if(opcio_actual - 1 < 0) opcio_actual = 4;
        else --opcio_actual;
		CSoundManager::pGetInstance()->play(SO_MENU);
        SDL_Delay(300);
    }

    else if (input->checkPress(kRight)) {
        opcio_actual = (opcio_actual + 1)%5;
        SDL_Delay(300);
		CSoundManager::pGetInstance()->play(SO_MENU);
    }

	if (input->checkPress(kEsc)) return MB_EXIT;
	if (input->checkPress(kEnter)) {
		if (opcio_actual == 0 && !continuar) {
			return MB_NONE;
		}
		else return menu_opcions[opcio_actual].opcio;
	}
	return MB_NONE;
}



void CMenu::draw(){

	//definicio de la matriu de projeccio en ortho per al fons
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, RES_H, 0, RES_V, 1, 30);

    //definicio de la matriu de models
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	glLoadIdentity(); 

	//Imatge de fons
	glTranslatef(0.0f, 0.0f, -20.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, imatge_fons);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, float(RES_V), 0.0f);
		glTexCoord2f(0.0f, 0.75f); glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.75f); glVertex3f(float(RES_H), 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(float(RES_H), float(RES_V), 0.0f);
	glEnd();   

	//posem perspectiva
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.33, 0.1, 150.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	int aux = opcio_actual;
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(menu_posicions[i].posx, menu_posicions[i].posy, menu_posicions[i].posz);
		if (aux == opcio_actual) glBindTexture(GL_TEXTURE_2D,menu_opcions[aux].textureA);
		else glBindTexture(GL_TEXTURE_2D,menu_opcions[aux].textureD);
		if (aux == 0 && !continuar) glBindTexture(GL_TEXTURE_2D,menu_opcions[aux].textureD);
        glBegin (GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f, 1.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(4.0f, 1.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(4.0f, -1.0f, 0.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0f, -1.0f, 0.0f);
        glEnd();
        
        glPopMatrix();

        aux = (aux + 1)%5;
    }

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}
