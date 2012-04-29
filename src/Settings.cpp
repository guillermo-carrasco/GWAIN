#include "Settings.h"

#ifdef WIN32
#include <windows.h>
#include <SDL/SDL.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fstream>


CSettings* CSettings::m_pInstance = 0;

CSettings::CSettings()
{
	//Default Settin-gs
	ScreenWidth  = 0;
	ScreenHeight = 0;
	ScreenBpp    = 32;
	Fullscreen   = true;

	Keyboard[kEnter] = SDLK_RETURN;
	Keyboard[kEsc  ] = SDLK_ESCAPE;
	Keyboard[kSpace] = SDLK_SPACE;

	Keyboard[kUp   ] = SDLK_UP;
	Keyboard[kDown ] = SDLK_DOWN;
	Keyboard[kLeft ] = SDLK_LEFT;
	Keyboard[kRight] = SDLK_RIGHT;

	Keyboard[kW    ] = SDLK_w;
	Keyboard[kS    ] = SDLK_s;
	Keyboard[kA    ] = SDLK_a;
	Keyboard[kD    ] = SDLK_d;

	Keyboard[kViews] = SDLK_F1;
	Keyboard[kSound] = SDLK_F2;
	Keyboard[kFog  ] = SDLK_F3;

	Keyboard[kZoomIn  ] = SDLK_KP4;
	Keyboard[kZoomOut ] = SDLK_KP6;
	Keyboard[kTiltDown] = SDLK_KP2;
	Keyboard[kTiltUp  ] = SDLK_KP8;
	Keyboard[kEyeFar  ] = SDLK_KP7;
	Keyboard[kEyeNear ] = SDLK_KP9;
}

CSettings::~CSettings() { m_pInstance = NULL; }

CSettings* CSettings::pGetInstance()
{
	if(m_pInstance == NULL)
		m_pInstance = new CSettings();

	return m_pInstance;
}

bool CSettings::bLoad(char *filename)
{
	FILE* fSettingsFile;
	fSettingsFile = fopen(filename, "rb");
	if(fSettingsFile != NULL)
	{
		fread((void*)m_pInstance,1,sizeof(CSettings),fSettingsFile);
		fclose(fSettingsFile);
	}
	else return false;

	return true;
}

bool CSettings::bSave(char *filename)
{
	FILE* fSettingsFile;
	fSettingsFile = fopen(filename, "wb");
	if(fSettingsFile != NULL)
	{
		fwrite((void*)m_pInstance,1,sizeof(CSettings),fSettingsFile);
		fclose(fSettingsFile);
	}
	else return false;

	return true;
}
