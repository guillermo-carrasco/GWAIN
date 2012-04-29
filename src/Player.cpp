#include "Player.h"
#include "Scene.h"


CPlayer::CPlayer() {
}


CPlayer::~CPlayer() {
}


void CPlayer::init(void) {
	vides = 3;
	canyons = 1;
	focActiu = false;
	
	initParams();

	models = CModels::pGetInstance();
	soundman = CSoundManager::pGetInstance();

	sispar = new CParticleSystem();
	sispar = new CParticleSystem();
	sispar->setTipus(PS_LOOP, 0.0f, PT_DOT, 0, 8.0f);
	float color1[3] = {1.0f, 0.0f, 0.0f};
	sispar->setColor(color1, 1, true);
	float color2[3] = {1.0f, 1.0f, 0.0f};
	sispar->setColor(color2, 1, false);
	sispar->setFading(3.5f, 0.5f);
	sispar->setPosition(x, y, z-3.0f);
	sispar->setDirection(0.0f, 0.0f, -1.0f, 360.0f, 30.0f, 10.0f, 5.0f);
	sispar->setRotacio(180.0f);
	sispar->init(128);
}


void CPlayer::initParams() {
	angVel = angAccel = 0.0f;
	angle = 0.0f;
	angleRad = 0.0f;
    friction = 0.8f;
	rotFriction = 2.0f;
	vel.setVector(0.0f, 0.0f, 0.0f);
	accel.setVector(0.0f, 0.0f, 0.0f);
	MAX_VEL = 3.5f;
	MAX_ANGVEL = 20.0f;
	MOVE_ACCEL = 1.50f;
	LATERAL_ACCEL = 1.0f;
	ANGULAR_ACCEL = 3.0f;
	BULLET_TIME = 1.2f;
	INVENCIBLE_TIME = 75.0f;
	INVISIBLE_TIME = 200.0f;
	FROZEN_TIME = 30.0f;
	SPEED_TIME = 300.0f;
	timeToBullet = 0.0f;
	salut = 100;
	if (canyons > 1) canyons--;
	bomba = false;
	estat = PS_INVENCIBLE;
	timeToNormal = INVENCIBLE_TIME;
	timeToSwitchDraw = 2.5f;
}

void CPlayer::setParameter(int param, float value) {
	switch(param) {
		case PLY_MAX_VELOCITY:
			MAX_VEL = value;
			break;
		case PLY_ANGLE:
			angle = value;
			break;
		case PLY_ANGULAR_VELOCITY:
			angVel = value;
			break;
		case PLY_MAX_ANGULAR_VELOCITY:
			MAX_ANGVEL = value;
			break;
		case PLY_MOVE_ACCEL:
			MOVE_ACCEL = value;
			break;
		case PLY_LATERAL_ACCEL:
			LATERAL_ACCEL = value;
			break;
		case PLY_ANGULAR_ACCEL:
			ANGULAR_ACCEL = value;
			break;
		case PLY_FRICTION:
			friction = value;
			break;
		case PLY_ROT_FRICTION:
			rotFriction = value;
			break;
		case PLY_BULLET_TIME:
			BULLET_TIME = value;
			break;
		case PLY_INVENCIBLE_TIME:
			INVENCIBLE_TIME = value;
			break;
		case PLY_INVISIBLE_TIME:
			INVISIBLE_TIME = value;
			break;
		case PLY_FROZEN_TIME:
			FROZEN_TIME = value;
			break;
		case PLY_SPEED_TIME:
			SPEED_TIME = value;
			break;
		default:
			printf("%d no es una magnitud escalar\n", param);
			break;
	}	
}


void CPlayer::setVector(int param, float v0, float v1, float v2) {
	switch(param) {
		case PLY_POSITION:
			x = v0;
			y = v1;
			z = v2;
			break;
		case PLY_VELOCITY:
			vel.setVector(v0, v1, v2);
			break;
		default:
			printf("%d no es una magnitud vectorial\n", param);
			break;
	}	
}


float CPlayer::getParameter(int param) {
	switch(param) {
		case PLY_MAX_VELOCITY:
			return MAX_VEL;
		case PLY_ANGLE:
			return angle;
		case PLY_ANGULAR_VELOCITY:
			return angVel;
		case PLY_MAX_ANGULAR_VELOCITY:
			return MAX_ANGVEL;
		case PLY_MOVE_ACCEL:
			return MOVE_ACCEL;
		case PLY_LATERAL_ACCEL:
			return LATERAL_ACCEL;
		case PLY_ANGULAR_ACCEL:
			return ANGULAR_ACCEL;
		case PLY_FRICTION:
			return friction;
		case PLY_ROT_FRICTION:
			return rotFriction;
		case PLY_BULLET_TIME:
			return BULLET_TIME;
		case PLY_INVENCIBLE_TIME:
			return INVENCIBLE_TIME;
		case PLY_INVISIBLE_TIME:
			return INVISIBLE_TIME;
		case PLY_FROZEN_TIME:
			return FROZEN_TIME;
		case PLY_SPEED_TIME:
			return SPEED_TIME;
		default:
			printf("%d no es una magnitud escalar\n", param);
			return -1337.0f;
	}	
}


void CPlayer::getVector(int param, float v[3]) {
	switch(param) {
		case PLY_POSITION:
			v[0] = x;
			v[1] = y;
			v[2] = z;
			break;
		case PLY_VELOCITY:
			vel.getValues(v);
			break;
		default:
			printf("%d no es una magnitud vectorial\n", param);
			v = NULL;
			break;
	}	
}


void CPlayer::update(float time) {
	
	//ajust de la velocitat del jugador
	time = time*10;

	//si estem explotant no farem res
	if (estat == PS_EXPLODING) {
		sispar->update(time*1000.0f);
		timeToNormal -= time;
		if (timeToNormal > 0.0f) return;
		if (vides > 0) {
			setPosition(0.0f, 0.0f, 0.0f);
			initParams();
			sispar->setPosition(0.0f, 0.0f, 0.0f);
		}
		else {
			salut = 100; //indiquem que hem acabat d'explotar (chapuza)
			return;
		}
	}

	CInput* i = CInput::pGetInstance();

	//disparar
	timeToBullet -= time;
	if (i->checkPress(kSpace)) focActiu = !focActiu;
	if (focActiu && timeToBullet <= 0.0f) {
		disparar();
	}

	//bomba
	if (bomba && i->check(kUp)) {
		bomba = false;
		CScene::pGetInstance()->armaggedon();
	}

	//Girs
	if (i->check(kLeft)) {
		angAccel += ANGULAR_ACCEL;
	}
	if (i->check(kRight)) {
		angAccel -= ANGULAR_ACCEL;
	}

    //Moviment amb WASD
	if (i->check(kW)) {
	    accel.addVector(MOVE_ACCEL*sin(angleRad), 0.0f, MOVE_ACCEL*cos(angleRad));
	}
	if (i->check(kS)) {	
		accel.addVector(-MOVE_ACCEL*sin(angleRad), 0.0f, -MOVE_ACCEL*cos(angleRad));
	}
	if (i->check(kA)) {
		accel.addVector(LATERAL_ACCEL*cos(angleRad), 0.0f, -LATERAL_ACCEL*sin(angleRad));
	}
	if (i->check(kD)) {
		accel.addVector(-LATERAL_ACCEL*cos(angleRad), 0.0f, LATERAL_ACCEL*sin(angleRad));
    }
	
	//Tractament de les forces
	float tf, v;
	
    vel += accel*time;
    tf = time*friction;
	v = vel.getNorm();
    if (v > tf) {
		v -= tf;
		if (estat == PS_SPEEDSTER && v > 2.0f*MAX_VEL) v = 4.0f*MAX_VEL;
		else if (v > MAX_VEL) v = MAX_VEL;
		vel = vel.getUnit()*v;
	}
    else {
        vel.setVector(0.0f, 0.0f, 0.0f);
    }
    
    //Moviment
	if (estat != PS_FROZEN) {
		x += time*vel.getX();
		//y += time*vel.getY();
		z += time*vel.getZ();
		if (estat == PS_SPEEDSTER) {
			x += time*vel.getX();
			//y += time*vel.getY();
			z += time*vel.getZ();
		}
	}
    
    //Rotacio
    angle += time*angVel;
    angleRad = (M_PI * angle)/180.0f;
    angVel += time*angAccel;
    if (angVel > MAX_ANGVEL) 
        angVel = MAX_ANGVEL;
    else if (angVel < -MAX_ANGVEL) 
        angVel = -MAX_ANGVEL;
        
    //Fregament en rotacio
    float trf = time*rotFriction;
    if (angVel > trf) 
        angVel -= trf;
    else if (angVel < -trf) 
        angVel += trf;
    else 
        angVel = 0.0f;

    //Eliminem totes les forces
	accel.setVector(0.0f, 0.0f, 0.0f);	
	angAccel = 0.0f;

	//processem estats
	if (timeToNormal > 0) timeToNormal -= time;
	else setState(PS_NORMAL);

	if (estat == PS_INVENCIBLE) {
		timeToSwitchDraw -= time;
		if (timeToSwitchDraw < 0) {
			timeToSwitchDraw = 2.5f;
			visible = !visible;
		}
	}

	if (estat == PS_INVISIBLE) sispar->setPosition(x-3.0f*sin(angleRad), y-2.0f, z-3.0f*cos(angleRad));
	else sispar->setPosition(x-3.0f*sin(angleRad), y, z-3.0f*cos(angleRad));
	sispar->setRotacio(180.0f+angle);
	sispar->update(time/10);

	soundman->setListener(x, y, z, sin(angleRad), 0.0f, cos(angleRad), 0.0f, 1.0f, 0.0f);
}



void CPlayer::draw() {
	if (estat == PS_EXPLODING || vides <= 0) return;

	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	if (estat == PS_INVISIBLE) {
		glTranslatef(0.0f, -2.0f, 0.0f);
		models->dibuixa(M_OMNAU);
	}
	else if (visible) models->dibuixa(M_NAU);

	glPopMatrix();

	sispar->draw();
}


void CPlayer::repMal(int malRebut) {
	if (estat == PS_EXPLODING) return;
	if (malRebut < 0 && estat != PS_FROZEN) setState(PS_FROZEN);
	else if (estat != PS_INVENCIBLE) {
		soundman->play(SO_PLAYERHIT, x, y, z);
		salut -= malRebut;
	}
	if (salut <= 0) {
		vides--;
		sispar->setPosition(0.0f, 0.0f, 0.0f);
		soundman->play(SO_PLAYERMOR, x, y, z);
		explota();
	}
}


void CPlayer::explota() {
	estat = PS_EXPLODING;
	visible = false;
	timeToNormal = 20.0f;
	CParticleSystem* par = new CParticleSystem();
	par->setTipus(PS_ONCE, 0.0f, PT_DOT, 0, 4.0f);
	float color1[3] = {1.0f, 1.0f, 1.0f};
	par->setColor(color1, 1, true);
	par->setColor(color1, 1, false);
	par->setFading(1.5f, 1.0f);
	par->setPosition(x, y, z);
	par->setDirection(0.0f, 0.0f, -1.0f, 360.0f, 360.0f, 10.0f, 5.0f);
	par->init(64);
	CScene::pGetInstance()->afegirParticules(par);
}


void CPlayer::disparar() {
	switch(canyons) {
		case 1: {
			CBala* b = new CBala(angleRad, x, z);
			CScene::pGetInstance()->afegirBala(b);
			timeToBullet = BULLET_TIME;
			break;
		}
		case 2: {
			float dir[2];
			dir[0] = sin(angleRad);
			dir[1] = cos(angleRad);
			CBala* b = new CBala(angleRad, x-dir[1], z+dir[0]);
			CScene::pGetInstance()->afegirBala(b);
			CBala* b2 = new CBala(angleRad, x+dir[1], z-dir[0]);
			CScene::pGetInstance()->afegirBala(b2);
			timeToBullet = BULLET_TIME;
			break;
		}
		case 3: {
			CBala* b = new CBala(angleRad-M_PI/36.0f, x, z);
			CScene::pGetInstance()->afegirBala(b);
			CBala* b2 = new CBala(angleRad, x, z);
			CScene::pGetInstance()->afegirBala(b2);
			CBala* b3 = new CBala(angleRad+M_PI/36.0f, x, z);
			CScene::pGetInstance()->afegirBala(b3);
			timeToBullet = BULLET_TIME;
			break;
		}
		default:
			break;
	}

	soundman->play(SO_BALA, x, y, z);
}


void CPlayer::setPosition(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}


void CPlayer::getPosition(float r[3]) {
	r[0] = x;
	r[1] = y;
	r[2] = z;
}


void CPlayer::getDirection(float r[3]) {
	r[0] = vel.getX();	
	r[1] = vel.getY();
	r[2] = vel.getZ();
}


CBBox CPlayer::getBB(void) {
	CBBox bb;
	bb.left = x-3;
	bb.right = x+3;
	bb.top = z+3;
	bb.bottom = z-3;
	return bb;
}


void CPlayer::oneUp() {
	if (vides < 5) vides++;
}


void CPlayer::morePower() {
	if (canyons < 3) canyons++;
}


void CPlayer::heal(int healn) {
	salut += healn;
	if (salut > 100) salut = 100;
}


void CPlayer::catchBomb() {
	bomba = true;
}


int CPlayer::getVides() {
	return vides;
}


int CPlayer::getSalut() {
	return salut;
}


float CPlayer::getTempsEstat() {
	switch (estat) {
		case PS_NORMAL:
			return 0.0f;
		case PS_INVENCIBLE:
			return timeToNormal/INVENCIBLE_TIME;
		case PS_INVISIBLE:
			return timeToNormal/INVISIBLE_TIME;
		case PS_FROZEN:
			return timeToNormal/FROZEN_TIME;
		case PS_SPEEDSTER:
			return timeToNormal/SPEED_TIME;
		default:
			return 0.0f;
			break;
	}
}


bool CPlayer::esVisible() {
	return (estat != PS_INVISIBLE && estat != PS_EXPLODING);
}

bool CPlayer::esViu() {
	return (salut > 0);
}


bool CPlayer::teBomba() {
	return bomba;
}


void CPlayer::setState(int state) {
	estat = state;
	switch(estat) {
		case PS_NORMAL:
			visible = true;
			timeToNormal = 0.0f;
			break;
		case PS_INVENCIBLE:
			timeToNormal = INVENCIBLE_TIME;
			timeToSwitchDraw = 2.5f;
			break;
		case PS_INVISIBLE:
			timeToNormal = INVISIBLE_TIME;
			break;
		case PS_FROZEN:
			timeToNormal = FROZEN_TIME;
			visible = true;
			break;
		case PS_SPEEDSTER:
			timeToNormal = SPEED_TIME;
			visible = true;
			break;
		default:
			break;
	}
}

