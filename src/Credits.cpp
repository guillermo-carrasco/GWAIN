#include "Credits.h"

CCredits::CCredits(void){
}

CCredits::~CCredits(void){
}

void CCredits::init(){
    texman = CTextureManager::pGetInstance();
    escriptor = CWriter::getInstance();

    image_credits = texman->loadTexture("titol");
    marvin = texman->loadTexture("oscar");
    vader = texman->loadTexture("guillem");
}

void CCredits::draw(){

	//definicio de la matriu de projeccio en ortho per al fons
	CGraphics::pGetInstance()->canviaOrthoView();

	//dbuixem fons
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, image_credits);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.75f); glVertex3f(0.0f, float(RES_V), 0.0f);
        glTexCoord2f(1.0f, 0.75f); glVertex3f(float(RES_H), float(RES_V), 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(float(RES_H), 0.0f, 0.0f);
	glEnd();

    //Marvin
    glBindTexture(GL_TEXTURE_2D, marvin);
    glBegin (GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(112.0f, 272.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(112.0f, 400.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(240.0f, 400.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(240.0f, 272.0f, 0.0f);
    glEnd();

    //Vader
    glBindTexture(GL_TEXTURE_2D, vader);
    glBegin (GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(560.0f, 272.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(560.0f, 400.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(688.0f, 400.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(688.0f, 272.0f, 0.0f);
    glEnd();

	//Lletres
    escriptor->escriu(112, 420, 1.0f, "oscar");
    escriptor->escriu(112, 460, 1.0f, "argudo");
    escriptor->escriu(112, 500, 1.0f, "medrano");

    escriptor->escriu(400, 420, 1.0f, "guillermo");
    escriptor->escriu(432, 456, 1.0f, "carrasco");
    escriptor->escriu(400, 492, 1.0f, "hernandez");

	escriptor->escriu(112, 552, 1.0f, "videojocs fib 2008");
}
