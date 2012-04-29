#pragma once

#include <vector>

#include "Graphics.h"
#include "Stats.h"
#include "Input.h"
#include "Models.h"
#include "Player.h"
#include "Mesh.h"
#include "Enemic.h"
#include "EnemicLila.h"
#include "EnemicBlau.h"
#include "EnemicVermell.h"
#include "EnemicVermellFill.h"
#include "EnemicVerd.h"
#include "EnemicGroc.h"
#include "EnemicEnergyBall.h"
#include "EnemicCreador.h"
#include "Bala.h"
#include "Objecte.h"
//#include "GestorScene.h"


#define MAX_ENEMICS 100


class CScene
{
	public:
		static CScene* pGetInstance();
		~CScene(void);

		int  getNumEnemics();
		void buscaPosicioLliure(float pos[3]);
		void afegirEnemic(CEnemic* e);
		void afegirObjecte(CObjecte* o);
		void afegirBala(CBala* b);
		void afegirParticules(CParticleSystem* p);

		void init(void);
		void doStep(float time);
		void drawScene();

		void getPlayerPos(float position[3], bool &vis);
		std::vector<CBala*> getVectorBales();
		void getBounds(int &w, int &h);
		void armaggedon();
		int getPuntuacio();
		bool gameOver();

	private:
		CScene(void);
		void dibuixaXoc();

		void checkBorders(float cpos[3]);
		void donarObjectePlayer(int tipus);

		static CScene*			m_pInstance;

		CModels*	models;
		CGraphics*	graphics;
		CInput*		input;
		Mesh		malla;
		CPlayer		p;
		CStats*		stats;
		CSoundManager* soundman;

		std::vector<CEnemic*>			m_vEnemics;
		std::vector<CObjecte*>			m_vObjectes;
		std::vector<CBala*>				m_vBales;
		std::vector<CParticleSystem*>	m_vParticules;

		int puntuacio;
		float m_fTop, m_fBottom, m_fLeft, m_fRight;
		int dibuixarXoc;
		bool vistaLluny;
		
		GLuint texXoc;

		float zoom;
		float tilt;
		float viewdist;	
};
