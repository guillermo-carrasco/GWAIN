#pragma once

/*enum {
	KG_OK, KG_BACK, //GLOBAL KEYS
	kUp, kDOWN, kLEFT, kRIGHT, 
	kUP, KP2_DOWN, KP2_LEFT, KP2_RIGHT, //CPlayer2 KEYS
	K_SIZE };*/


enum keysDefs{kUp, kDown, kLeft, kRight, kW, kA, kS, kD, kSpace, 
			  kEsc, kEnter, kFog, kViews, kSound, 
			  kZoomIn, kZoomOut, kTiltUp, kTiltDown, kEyeFar, kEyeNear, Nkeys};


class CSettings
{
	public:
		~CSettings();
		static CSettings* pGetInstance();

		bool bLoad(char *filename);
		bool bSave(char *filename);

		//Video Configurations
		int  ScreenWidth;
		int  ScreenHeight;
		int  ScreenBpp;
		bool Fullscreen;

		//Input Configs
		unsigned short Keyboard[Nkeys];

	private:
		CSettings();

		static CSettings *m_pInstance;
};
