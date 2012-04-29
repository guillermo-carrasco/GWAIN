#include "Stats.h"


CStats* CStats::m_pInstance = 0;

CStats::CStats(void)
{
}

CStats::~CStats(void)
{
}

void CStats::init(void) {
	escriptor = CWriter::getInstance();
	texMarcadors = CTextureManager::pGetInstance()->loadTexture("marcadors");
}

CStats* CStats::getInstance() {
	if (!m_pInstance) {
		m_pInstance = new CStats();
		m_pInstance->init();
	}
	return m_pInstance;
}

void CStats::draw(int vides, int salut, float testat, bool bom, int punts) {
	
	//DIBUIXAR BARRA (24, 24)-(328, 54)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_LINES);
		glColor4f(40.0f/255.0f, 65.0f/255.0f, 140.0f/255.0f, 1.0f);
		glVertex3f(24.0f, 24.0f, 0.0f);
		glVertex3f(328.0f, 24.0f, 0.0f);
		glVertex3f(24.0f, 53.0f, 0.0f);
		glVertex3f(328.0f, 53.0f, 0.0f);
		glVertex3f(24.0f, 24.0f, 0.0f);
		glVertex3f(24.0f, 53.0f, 0.0f);
		glVertex3f(328.0f, 24.0f, 0.0f);
		glVertex3f(328.0f, 53.0f, 0.0f);
	glEnd();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float lon1 = float(salut*3);
	float lon2 = 0.0f;
	glBegin(GL_QUADS);
		glColor4f(1.0f, 0.0f, 0.0f, 0.7f);
		glVertex3f(26.0f, 25.0f, 0.0f);
		glVertex3f(26.0f, 52.0f, 0.0f);
		if (lon1 < 150.0f)  {
			glColor4f(1.0f, lon1/150.0f, 0.0f, 0.7f);
		}
		else {
			glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
			lon2 = lon1-150.0f;
			lon1 = 150.0f;
		}
		glVertex3f(26.0f+lon1, 52.0f, 0.0f);
		glVertex3f(26.0f+lon1, 25.0f, 0.0f);
	glEnd();
	if (lon2 > 0) {
		glBegin(GL_QUADS);
			glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
			glVertex3f(176.0f, 25.0f, 0.0f);
			glVertex3f(176.0f, 52.0f, 0.0f);
			if (lon2 > 0) glColor4f(1.0f-lon2/150.0f, 1.0f, 0.0f, 0.7f);
			else glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
			glVertex3f(176.0f+lon2, 52.0f, 0.0f);
			glVertex3f(176.0f+lon2, 25.0f, 0.0f);
		glEnd();
	}

	//DIBUIXAR BARRA DE TEMPS D'ESTAT
	if (testat > 0.0f) {
		glBegin(GL_LINES);
			glColor4f(0.0f, 0.0f, 0.5f, 1.0f);
			glVertex3f(24.0f, 55.0f, 0.0f);
			glColor4f(0.0f, 0.5f*testat, 0.5f+0.5f*testat, 1.0f);
			glVertex3f(24.0f+testat*304.0f, 56.0f, 0.0f);
		glEnd();
	}

	//DIBUIXAR VIDES (360, 24)-(518, 56) 
	int x0 = 360;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, texMarcadors);
	for (int i = 0; i < vides; i++) {
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(float(x0), 24.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(float(x0), 56.0f, 0.0f);
			glTexCoord2f(0.5f, 1.0f); glVertex3f(float(x0+32), 56.0f, 0.0f);
			glTexCoord2f(0.5f, 0.0f); glVertex3f(float(x0+32), 24.0f, 0.0f);
		glEnd();
		x0 += 32;
	}
	if (bom) {
		glBegin(GL_QUADS);
			glTexCoord2f(0.5f, 0.0f); glVertex3f(520.0f, 24.0f, 0.0f);
			glTexCoord2f(0.5f, 1.0f); glVertex3f(520.0f, 56.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(552.0f, 56.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(552.0f, 24.0f, 0.0f);
		glEnd();
	}

	//DIBUIXAR PUNTUACIO (584, 24)-(776, 56)
	std::string p = "000000";
	int i = 5;
	while (punts > 0 && i >= 0) {
		p[i] = punts%10+'0';
		punts = punts/10;
		i--;
	}

	escriptor->escriu(584, 24, 1.0f, p);
	glDisable(GL_TEXTURE_2D); 
}
