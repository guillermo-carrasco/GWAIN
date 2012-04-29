//CLASE JUGADOR CONTROLABLE

#pragma once

#include "Globals.h"
#include <cmath>
#include <SDL/SDL.h>
#include "Input.h"
#include "Vector3.h"
#include "Models.h"
#include "BBox.h"
#include "Bala.h"
#include "ParticleSystem.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "emyl.h"


#define PLY_POSITION				0
#define PLY_VELOCITY				1
#define PLY_MAX_VELOCITY			2

#define PLY_ANGLE					3
#define PLY_ANGULAR_VELOCITY		4
#define PLY_MAX_ANGULAR_VELOCITY	5

#define PLY_MOVE_ACCEL				6
#define PLY_LATERAL_ACCEL			7
#define PLY_ANGULAR_ACCEL			8

#define PLY_FRICTION				9
#define PLY_ROT_FRICTION			10

#define PLY_BULLET_TIME				11
#define PLY_INVENCIBLE_TIME			12
#define PLY_INVISIBLE_TIME			13
#define PLY_FROZEN_TIME				14
#define PLY_SPEED_TIME				15


#define PS_NORMAL					1
#define PS_INVENCIBLE				2
#define PS_INVISIBLE				3
#define PS_FROZEN					4
#define PS_SPEEDSTER				5
#define PS_EXPLODING				6



class CPlayer {

	public:
		CPlayer();
		~CPlayer();

		void setParameter(int param, float value);
		float getParameter(int param);
		void setVector(int vector, float v0, float _v1, float _v2);
		void getVector(int vector, float v[3]);

		void setPosition(float _x, float _y, float _z);
		void getPosition(float r[3]);
		void getDirection(float r[3]);

		void oneUp();
		void morePower();
		void heal(int healn);
		void catchBomb();

		int getVides();
		int getSalut();
		float getTempsEstat();
		bool esVisible();
		bool esViu();
		bool teBomba();
		CBBox getBB();
		void repMal(int malRebut);
		void setState(int state);

		void init(void);
		
		void update(float time);
		void draw();

	private:
		void initParams();
		void disparar();
		void explota();

		float x, y, z;

		int vides, salut, estat;

		CVector3 vel, accel;
		float angle, angleRad, angVel, angAccel;
		float MAX_VEL, MAX_ANGVEL;
		float MOVE_ACCEL, LATERAL_ACCEL, ANGULAR_ACCEL;
		float BULLET_TIME, INVISIBLE_TIME, INVENCIBLE_TIME;
		float SPEED_TIME, FROZEN_TIME;

		float friction, rotFriction;
		float timeToBullet, timeToNormal, timeToSwitchDraw;
		bool visible;
		int canyons;
		bool bomba;
		bool focActiu;

		CParticleSystem* sispar;

		CModels* models;
		CSoundManager* soundman;
};

