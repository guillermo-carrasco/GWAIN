#pragma once

#include "Globals.h"
#include <SDL/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Settings.h"


class CGraphics
{
public:
	static CGraphics* pGetInstance();
	~CGraphics(void);

	bool bInit();
	void flip();

	void canviaOrthoView();
	void tornaOrthoView();
	void turnFog();

	//TOOLS
	float fGetScreenRatio();

	//TEXMAN ADDS
	//GLuint       uiUseTexture (std::string _sFilename);
	//void         DeleteTexture(std::string _sFilename);
	//unsigned int uiNumOfTextures();

protected:

	typedef struct {
			unsigned int w;
			unsigned int h;
			unsigned int bpp;
	} tmode;
	
	static int compare_modes(const void *a, const void *b);

	SDL_Surface* screen;
	tmode* video_modes;
	tmode selected_mode;

	bool fogActive;

	CGraphics();
	//GLuint uiLoadPNG(FILE* f);

	static CGraphics* m_pInstance;
	std::map<std::string, GLuint> m_mTextures;

	bool initScreenSDL();
	void initGL();

};
