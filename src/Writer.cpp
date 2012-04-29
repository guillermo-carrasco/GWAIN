#include "Writer.h"


CWriter* CWriter::m_pInstance = 0;

CWriter::CWriter(void)
{
}

CWriter::~CWriter(void)
{
}

CWriter* CWriter::getInstance() {
	if (!m_pInstance) {
		m_pInstance = new CWriter();
		m_pInstance->init();
	}
	return m_pInstance;
}

void CWriter::init() {
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);
	texFont = CTextureManager::pGetInstance()->loadTexture("font");
}

void CWriter::escriu(int x, int y, float escala, std::string text) {

	glScalef(escala, escala, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texFont);
	
	float coords[2][2];
	float x0 = float(x);
	float y0 = float(y);
	for (unsigned int i = 0; i < text.size(); i++) {
		if (text[i] == ' ') {
			x0 += 32.0f;
			continue;
		}
		calculaTexCoor(text[i], coords);
		glBegin(GL_QUADS);
			glTexCoord2f(coords[0][0], coords[1][0]);
				glVertex3f(x0, y0, 0.0f);
			glTexCoord2f(coords[0][0], coords[1][1]);
				glVertex3f(x0, y0+32.0f, 0.0f);
			glTexCoord2f(coords[0][1], coords[1][1]);
				glVertex3f(x0+32.0f, y0+32.0f, 0.0f);
			glTexCoord2f(coords[0][1], coords[1][0]);
				glVertex3f(x0+32.0f, y0, 0.0f);
		glEnd();
		x0 += 32.0f;
	}

	glDisable(GL_TEXTURE_2D);
}


void CWriter::calculaTexCoor(char c, float coor[2][2]) {
	int d, h;
	if (c >= '0' && c <= '7') {
		d = c - '0';
		h = 0;
	}
	else if (c == '8' || c == '9') {
		d = c - '8';
		h = 1;
	}
	else if (c >= 'a' && c <= 'h') {
		d = c - 'a';
		h = 2;
	}
	else if (c >= 'i' && c <= 'p') {
		d = c - 'i';
		h = 3;
	}
	else if (c >= 'q' && c <= 'x') {
		d = c - 'q';
		h = 4;
	}
	else if (c == 'y' || c == 'z'){
		d = c - 'y';
		h = 5;
	}
	else {
		d = h = 7;
	}
	coor[0][0] = float(d)/8.0f;
	coor[0][1] = float(d+1)/8.0f;
	coor[1][0] = float(h)/8.0f;
	coor[1][1] = float(h+1)/8.0f;
}
