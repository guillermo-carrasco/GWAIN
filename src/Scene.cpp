#include "Scene.h"
#include "GestorScene.h"


CScene* CScene::m_pInstance = 0;

CScene::CScene(void)
{
}

CScene::~CScene(void)
{
}

void CScene::init(void)
{
	//variables per a la camara
	zoom = 64.0f;//10.0f;  
    tilt = 40.0f;//6.0f;
    viewdist = 15.0f;
	vistaLluny = true;
	
	//iniciem el gestor
	CGestorScene::pGetInstance()->init();

	//iniciem els motors
	graphics = CGraphics::pGetInstance();
	input = CInput::pGetInstance();
	models = CModels::pGetInstance();
	stats = CStats::getInstance();

	texXoc = CTextureManager::pGetInstance()->loadTexture("mesh");
	soundman = CSoundManager::pGetInstance();


	//iniciem jugador
	p.setPosition(0.0f, 0.0f, 0.0f);
	p.init();
	
	//iniciem vectors
	m_vEnemics = std::vector<CEnemic*>(0);
	m_vObjectes = std::vector<CObjecte*>(0);
	m_vBales = std::vector<CBala*>(0);
	m_vParticules = std::vector<CParticleSystem*>(0);

	//definim mesh
	malla = Mesh(60, 60);
	malla.init();

	m_fRight = m_fTop = 120;
	m_fLeft = m_fBottom = -120;

	dibuixarXoc = 0;
	puntuacio = 0;
}


CScene* CScene::pGetInstance()
{
	if (CScene::m_pInstance == 0) {
		m_pInstance = new CScene();
	}
	return m_pInstance;
}


void CScene::afegirEnemic(CEnemic* e) {
	m_vEnemics.push_back(e);
}


void CScene::afegirObjecte(CObjecte* o) {
	m_vObjectes.push_back(o);
}


void CScene::afegirBala(CBala* b) {
	m_vBales.push_back(b);
}


void CScene::afegirParticules(CParticleSystem* p) {
	m_vParticules.push_back(p);
}



void CScene::doStep(float time) {
	//ENTRADES DE CONFIGURACIO
	if (input->check(kZoomIn)) zoom -= 0.2f;
	if (input->check(kZoomOut)) zoom += 0.2f;
	if (input->check(kTiltUp)) tilt += 0.2f;
	if (input->check(kTiltDown)) tilt -= 0.2f;
	if (input->check(kEyeFar)) viewdist += 0.2f;
	if (input->check(kEyeNear)) viewdist -= 0.2f;
	if (input->checkPress(kFog)) CGraphics::pGetInstance()->turnFog();
	if (input->checkPress(kViews)) {
		vistaLluny = !vistaLluny;
		if (vistaLluny) {
			zoom = 64.0f;
			tilt = 40.0f;
		}
		else {
			zoom = 38.0f;
			tilt = 20.0f;
		}
	}

	//PAS DEL GESTOR
	CGestorScene::pGetInstance()->update(time);
	

	//MOVIMENTS

	//movem jugador
	p.update(time);
	float ppos[3];
	p.getPosition(ppos);
	if (ppos[0]-3.0f <= m_fLeft) {
		ppos[0] = m_fLeft+3.0f;
		dibuixarXoc += 0x0001;
		p.repMal(1);
	}
	else if (ppos[0]+3.0f >= m_fRight) {
		ppos[0] = m_fRight-3.0f;
		dibuixarXoc += 0x0010;
		p.repMal(1);
	}
	if (ppos[2]-3.0f <= m_fBottom) {
		ppos[2] = m_fBottom+3.0f;
		dibuixarXoc += 0x0100;
		p.repMal(1);
	}
	else if (ppos[2]+3.0f >= m_fTop) {
		ppos[2] = m_fTop-3.0f;
		dibuixarXoc += 0x1000;
		p.repMal(1);
	}
	p.setPosition(ppos[0], ppos[1], ppos[2]);

	//actualitzar posicions de bales
	for(unsigned int i = 0; i < m_vBales.size(); i++) {
		m_vBales[i]->step(time);
		if ((m_vBales[i]->x <= m_fLeft) ||
		    (m_vBales[i]->x >= m_fRight) ||
			(m_vBales[i]->z <= m_fBottom) ||
			(m_vBales[i]->z >= m_fTop))
		{
			//explotar-la si arriba al marge
			CParticleSystem* ps = new CParticleSystem();
			ps->setTipus(PS_ONCE, 0.0f, PT_DOT, 0, 1.0f);
			float color1[3] = {1.0f, 1.0f, 1.0f};
			ps->setColor(color1, 1, true);
			ps->setColor(color1, 1, false);
			ps->setFading(1.0, 0.5f);
			ps->setPosition(m_vBales[i]->x, 0.0f, m_vBales[i]->z);
			ps->setDirection(0.0f, 0.0f, 1.0f, 360.0f, 360.0f, 5.0f, 10.0f);
			ps->init(4);
			m_vParticules.push_back(ps);
			std::vector<CBala*>::iterator bit = m_vBales.begin() + i;
			m_vBales.erase(bit);
			i--;
		}	
	}

	//actualitzar posicions d'enemics
	for(unsigned int i = 0; i < m_vEnemics.size(); i++) {
		m_vEnemics[i]->update(time);
		float epos[3];
		m_vEnemics[i]->getPos(epos);
		checkBorders(epos);
		m_vEnemics[i]->setPos(epos[0], epos[1], epos[2]);
	}

	//movem objectes
	for(unsigned int i = 0; i < m_vObjectes.size(); i++) {
		m_vObjectes[i]->update(time);
		float opos[3];
		m_vObjectes[i]->getPos(opos);
		checkBorders(opos);
		m_vObjectes[i]->setPos(opos[0], opos[1], opos[2]);
	}
	
	//actualitzem particules
	for(unsigned int i = 0; i < m_vParticules.size(); i++) {
		m_vParticules[i]->update(time);
		if (!m_vParticules[i]->isActive()) {
			std::vector<CParticleSystem*>::iterator pit = m_vParticules.begin() + i;
			m_vParticules.erase(pit);
			i--;
		}
	}


	//COL·LISIONS

	if (p.esViu()) {
		//objectes-personatge
		for (unsigned int i = 0; i < m_vObjectes.size(); i++) {
			if (p.getBB().collide(m_vObjectes[i]->getBB())) {
				donarObjectePlayer(m_vObjectes[i]->getTipus());		
				std::vector<CObjecte*>::iterator oit = m_vObjectes.begin() + i;
				m_vObjectes.erase(oit);
				i--;
			}
		}

		//enemics-personatge
		for (unsigned int i = 0; i < m_vEnemics.size(); i++) {
			if (p.getBB().collide(m_vEnemics[i]->getBB())) {
				p.repMal(m_vEnemics[i]->getPower()*3);
				m_vEnemics[i]->repBala();
				if(!m_vEnemics[i]->esViu()) {
					std::vector<CEnemic*>::iterator eit = m_vEnemics.begin() + i;
					m_vEnemics.erase(eit);
					i--;
				}
			}
		}
	}

	//bales-enemics
	for (unsigned int i = 0; i < m_vBales.size(); i++) {
		for (unsigned int j = 0; j < m_vEnemics.size(); j++) {
			CBBox bbe = m_vEnemics[j]->getBB();
			CBala* bal = m_vBales[i];
			if (bbe.circle(bal->x, bal->z, 1.0f+VEL_BALA*time/5.0f)) {
				m_vEnemics[j]->repBala();
				std::vector<CBala*>::iterator bit = m_vBales.begin() + i;
				m_vBales.erase(bit);
				i--;
				float pose[3];
				m_vEnemics[j]->getPos(pose);
				soundman->play(SO_ENEMICHIT, pose[0], pose[1], pose[2]);
				if(!m_vEnemics[j]->esViu()) {
					puntuacio += m_vEnemics[j]->getPunts();
					std::vector<CEnemic*>::iterator eit = m_vEnemics.begin() + j;
					m_vEnemics.erase(eit);
					soundman->play(SO_ENEMICMOR, pose[0], pose[1], pose[2]);
				}
				break;
			}
		}
	}

	//limit de puntuacio
	if (puntuacio >= 1000000) puntuacio = 999999;
}



void CScene::drawScene() {

	//int t1, t2, t3, t4, t5, t6, t7, t8, t9;
	//t1 = SDL_GetTicks();

	//definicio de la matriu de projeccio
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.33, 0.1, 500.0);
	
	//definicio de la matriu de CModels
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLoadIdentity(); 

	//t2 = SDL_GetTicks();

    //CAMERA DARRERE DEL JUGADOR
    float pos[3], dir[3];
    p.getPosition(pos);
    p.getDirection(dir);
    float angle = (M_PI * p.getParameter(PLY_ANGLE))/180.0f;
    
	gluLookAt(pos[0] - zoom*sin(angle), 
              pos[1] + tilt, 
              pos[2] - zoom*cos(angle), 
			  pos[0] + viewdist*sin(angle), 
              pos[1] + tilt/4, 
              pos[2] + viewdist*cos(angle),
	 		  0, 1, 0);

	//t3 = SDL_GetTicks();

	//DIBUIX DEL TERRENY
	glTranslatef(0.0f, -2.0f, 0.0f);
	malla.draw();
	glTranslatef(0.0f, 2.0f, 0.0f);

	//t4 = SDL_GetTicks();

	//dibuixar bales
	for(unsigned int i = 0; i < m_vBales.size(); i++) {
		m_vBales[i]->draw();
	}

	//t5 = SDL_GetTicks();

	//dibuixar objectes
	for(unsigned int i = 0; i < m_vObjectes.size(); i++) {
		m_vObjectes[i]->draw();
	}

	//dibuixar enemics
	for(unsigned int i = 0; i < m_vEnemics.size(); i++) {
		m_vEnemics[i]->draw();
	}

	//t6 = SDL_GetTicks();

	//dibuixar particules
	for(unsigned int i = 0; i < m_vParticules.size(); i++) {
		m_vParticules[i]->draw();
	}

	//t7 = SDL_GetTicks();

	//dibuixem el jugador
	p.draw();

	if (dibuixarXoc > 0) dibuixaXoc();
	dibuixarXoc = 0;

	//t8 = SDL_GetTicks();

	//dibuixem estadistiques
	graphics->canviaOrthoView();
	glEnable(GL_BLEND);
	int salut = -1;;
	if (p.getVides() > 0) salut = p.getSalut();
	if (salut < 0) salut = 0;
	stats->draw(p.getVides(), salut, p.getTempsEstat(), p.teBomba(), puntuacio);
	glDisable(GL_BLEND);
	graphics->tornaOrthoView();

	//t9 = SDL_GetTicks();

	/*
	printf("%i: %i %i %i %i %i %i %i %i %i\n", m_vEnemics.size(), t1, t2, t3, t4, t5, t6, t7, t8, t9);
	fflush(stdout);*/
}


bool CScene::gameOver(void) {
	return (p.getVides() <= 0 && p.esViu());
}


void CScene::getPlayerPos(float position[3], bool &vis) {
	p.getPosition(position);
	vis = p.esVisible();
}

std::vector<CBala*> CScene::getVectorBales() {
	return m_vBales;
}


void CScene::getBounds(int &w, int &h) {
	w = int(m_fRight - m_fLeft);
	h = int(m_fTop - m_fBottom);
}



void CScene::dibuixaXoc() {
	glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texXoc);
		glColor3f(1.0f, 0.5f, 0.0f);
		float ppos[3];
		p.getPosition(ppos);
			glBegin(GL_QUADS);
			if (dibuixarXoc & 0x0001) {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(m_fLeft,  3.0f, ppos[2]-3.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(m_fLeft, -3.0f, ppos[2]-3.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(m_fLeft, -3.0f, ppos[2]+3.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(m_fLeft,  3.0f, ppos[2]+3.0f);
			}
			if (dibuixarXoc & 0x0010) {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(m_fRight,  3.0f, ppos[2]-3.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(m_fRight, -3.0f, ppos[2]-3.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(m_fRight, -3.0f, ppos[2]+3.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(m_fRight,  3.0f, ppos[2]+3.0f);
			}
			if (dibuixarXoc & 0x0100) {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(ppos[0]-3.0f,  3.0f, m_fBottom);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(ppos[0]-3.0f, -3.0f, m_fBottom);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(ppos[0]+3.0f, -3.0f, m_fBottom);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(ppos[0]+3.0f,  3.0f, m_fBottom);
			}
			if (dibuixarXoc & 0x1000) {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(ppos[0]-3.0f,  3.0f, m_fTop);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(ppos[0]-3.0f, -3.0f, m_fTop);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(ppos[0]+3.0f, -3.0f, m_fTop);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(ppos[0]+3.0f,  3.0f, m_fTop);
			}
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
	glPopMatrix();
}


void CScene::checkBorders(float cpos[3]) {
	if (cpos[0] <= m_fLeft) cpos[0] = m_fLeft;
	else if (cpos[0] >= m_fRight) cpos[0] = m_fRight;
	if (cpos[2] <= m_fBottom) cpos[2] = m_fBottom;
	else if (cpos[2] >= m_fTop) cpos[2] = m_fTop;
}

void CScene::donarObjectePlayer(int objt) {
	float pplay[3];
	p.getPosition(pplay);
	soundman->play(SO_AGAFAOBJ, pplay[0], pplay[1], pplay[2]);
	switch(objt) {
		case OBJ_1VIDA:
			p.oneUp();
			break;
		case OBJ_SALUT:
			p.heal(rand()%50+25);
			break;
		case OBJ_POWER:
			p.morePower();
			break;
		case OBJ_SPEED:
			p.setState(PS_SPEEDSTER);
			break;
		case OBJ_BOMBA:
			p.catchBomb();
			break;
		case OBJ_INVIS:
			p.setState(PS_INVISIBLE);
			break;
		case OBJ_INVEN:
			p.setState(PS_INVENCIBLE);
			break;
		default:
			break;
	}
}

void CScene::armaggedon() {
	float pplay[3];
	p.getPosition(pplay);
	soundman->play(SO_BOMBA, pplay[0], pplay[1], pplay[2]);
	while (m_vEnemics.size() > 0) {
		m_vEnemics[0]->mor();
		puntuacio += m_vEnemics[0]->getPunts();
		std::vector<CEnemic*>::iterator eit = m_vEnemics.begin();
		m_vEnemics.erase(eit);
	}
}


int CScene::getPuntuacio() {
	return puntuacio;
}


int CScene::getNumEnemics() {
	return int(m_vEnemics.size());
}

void CScene::buscaPosicioLliure(float pos[3]) {
	int w = int(m_fRight - m_fLeft - 10.0f);
	int h = int(m_fTop - m_fBottom - 10.0f);

	float x = float(rand()%w - w/2);
	float z = float(rand()%h - h/2);

	if (p.getBB().circle(x, z, 5.0f)) {
		x += 5.0f;
		z += 5.0f;
	}

	pos[0] = x;
	pos[1] = 0.0f;
	pos[2] = z;
	return;
}
