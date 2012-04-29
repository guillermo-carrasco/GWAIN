#pragma once
#include "Globals.h"
#include "Writer.h"
#include "TextureManager.h"


class CStats
{
	public:
		CStats(void);
		~CStats(void);

		static CStats* getInstance();

		void init();
		void draw(int vides, int salut, float testat, bool bom, int punts);

	private:
		static CStats* m_pInstance;
		GLuint texMarcadors;
		CWriter* escriptor;
};
