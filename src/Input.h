#pragma once

#include "Settings.h"
#include <SDL/SDL.h>


#define KEY_OFF         0
#define KEY_ON          1
#define KEY_RELEASED    2
#define KEY_PRESSED     3


class CInput
{
	public:
		static CInput* pGetInstance();
		~CInput();

		void update();
		bool bExit();

		float getGlobalTime();
		
		bool check(unsigned char key);
		bool checkPress(unsigned char key);
		bool checkRelease(unsigned char key);
		
	private:
		CInput();

		static CInput *m_pInstance;
		CSettings* m_pSettings;

		char keys[Nkeys];

		float m_GlobalTime;
		bool  DoExit;
};
