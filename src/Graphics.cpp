#include "Graphics.h"




bool CGraphics::initScreenSDL() {
    //iniciem el mode de video de SDL
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == -1)  {
        std::cerr << "No s'ha iniciat la SDL" << std::endl;
        return false;
    }
    //donem titol a la finestra
	SDL_WM_SetCaption("GWAIN", NULL);  
    //definim les propietats dels grafics       
	SDL_Surface* screen = SDL_SetVideoMode(RES_H, 
                                           RES_V, 
                                           16, 
                                           SDL_OPENGL | 
                                           SDL_GL_DOUBLEBUFFER | 
   	                                       SDL_HWPALETTE | 
                                           SDL_HWSURFACE | 
                                           SDL_HWACCEL);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	//si no tenim un punter a pantalla ha passat algun error
	if (screen == NULL)  {
        std::cerr << "No s'ha iniciat la screen" << std::endl;
        return false;
    }
    //altrament tot ha anat be
    return true;
}

void CGraphics::initGL() {
    //interpolem colors
	glShadeModel(GL_SMOOTH);
	
	//color per borrar la pantalla i profunditat
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClearDepth( 1.0f );
	

	//parametres de la boira
    float fogColor[4];
	fogColor[0] = 0.0f;
    fogColor[1] = 0.0f;
    fogColor[2] = 0.0f;
    fogColor[3] = 1.0f;

	//parametres de la boira
    glFogi(GL_FOG_MODE, GL_LINEAR);       
    glFogfv(GL_FOG_COLOR, fogColor);	
    glFogf(GL_FOG_DENSITY, 0.15f);		
    glHint(GL_FOG_HINT, GL_NICEST);	
    glFogf(GL_FOG_START, 50.0f);			
    glFogf(GL_FOG_END, 230.0f);
	glEnable(GL_FOG);
    fogActive = true;

	//activem el test de profunditat
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	//activem la funcio de blending
	glBlendFunc( GL_ONE, GL_ONE );
	
	//bona correccio de perspectiva
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}  

//---------------------------------------------------------------------------//

CGraphics* CGraphics::m_pInstance = 0;

CGraphics* CGraphics::pGetInstance()
{
	if (m_pInstance == 0) m_pInstance = new CGraphics();
	return m_pInstance;
}

CGraphics:: CGraphics() {
}


CGraphics::~CGraphics() {
	if (screen) SDL_FreeSurface(screen);

	std::map<std::string,GLuint>::iterator iter = m_mTextures.begin();
	while (iter != m_mTextures.end()) 
	{
		GLuint uiID = iter->second;
		glDeleteTextures(1,&uiID);
		m_mTextures.erase(iter);
		iter++;
	}

	SDL_Quit();
}

//---------------------------------------------------------------------------//

bool CGraphics::bInit()
{
	if (!initScreenSDL()) return false;
	initGL();

	return true;
}

//---------------------------------------------------------------------------//

void CGraphics::flip() { SDL_GL_SwapBuffers(); }
//---------------------------------------------------------------------------//

float CGraphics::fGetScreenRatio()
{
	if (selected_mode.h == 0.0f) return 0.0f;
	return float(selected_mode.w)/float(selected_mode.h);
}

int CGraphics::compare_modes(const void *a, const void *b)
{
	tmode* A = (tmode*)a;
	tmode* B = (tmode*)b;

	return (A->w * A->h) < (B->w * B->h); //SORTED GREATER-->SMALLER
}

//----------------------------------------------------------//

void CGraphics::canviaOrthoView() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, RES_H, RES_V, 0, 1, 30);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -20.0f);
}

void CGraphics::tornaOrthoView() {
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void CGraphics::turnFog() {
	if (fogActive) {
		glDisable(GL_FOG);
		fogActive = false;
	}
	else {
		glEnable(GL_FOG);
		fogActive = true;
	}
}
