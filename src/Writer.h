#pragma once

#include <string>
#include "Globals.h"
#include "TextureManager.h"

#define MIDA			32

class CWriter
{
	public:
		CWriter(void);
		~CWriter(void);

		static CWriter* getInstance();
		void init();
		void escriu(int x, int y, float escala, std::string text);

	private:
		void calculaTexCoor(char c, float coor[2][2]);

		static CWriter* m_pInstance;

		int texFont;
};
