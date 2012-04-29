#pragma once

#include "Globals.h"
#include <cmath>


enum {M_TETRA, M_CUBE, M_ENAU, M_NAU, M_OMNAU, M_BALA, M_OBJS, M_ENEMC,
	  M_ENEM1, M_ENEM2, M_ENEM3, M_ENEM4, M_ENEM5, M_ENEM6, M_ENEM7, M_NUMT};


class CModels {

	public:
		static CModels* pGetInstance();
		~CModels(void);

		void dibuixa(int idModel);
		void generaTots();

	private:
		CModels();

		unsigned int buildTerra();
		unsigned int buildTetraedre();
		unsigned int buildCub();
		unsigned int buildEsqueletNau();
		unsigned int buildNau();
		unsigned int buildOmbraNau();
		unsigned int buildBala();
		unsigned int buildObjecte();
		unsigned int buildEnemic1();
		unsigned int buildEnemic2();
		unsigned int buildEnemic3();
		unsigned int buildEnemic4();
		unsigned int buildEnemic5();
		unsigned int buildEnemic6();
		unsigned int buildEnemic7();
		unsigned int buildEnemicCreador();

		static CModels* m_pInstance;	

		unsigned int models[M_NUMT];
};
