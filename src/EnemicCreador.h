#pragma once
#include "Enemic.h"
#include "EnemicLila.h"
#include "EnemicBlau.h"
#include "EnemicVerd.h"
#include "Scene.h"


#define TIME_RANGE  2000
#define TIME_MIN	1000
#define PROB_RAF	10
#define RAF_RANGE	5
#define RAF_MIN		5


enum {ENCRE_LILA, ENCRE_BLAU, ENCRE_VERD, NUM_CREADORS};



class CEnemicCreador : public CEnemic
{
	public:
		CEnemicCreador(void);
		~CEnemicCreador(void);
		
		int getTipus();
		void init(void* v);
		void update(float time);
		void repBala();

	private:
		int tipusCreador;
		float createTime;

};
