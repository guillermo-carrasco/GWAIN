#include "ParticleSystem.h"


CParticleSystem::CParticleSystem(void)
{
	srand(time(NULL));
}


CParticleSystem::~CParticleSystem(void)
{
}


void CParticleSystem::setTipus(int tipusE, float lifetime, int tipusP, GLuint tex, float mida) {
	tipusEmisor = tipusE;
	//si tipus no es un temporitzat, ignorem el segon parametre
	if (tipusE == PS_TIMED) totalTime = lifetime;
	
	tipusPart = tipusP;
	//textura: si no es seran punts sense textura, altrament preguntarem per aquell ID
	if (tipusP == PT_TEX) {
		textura = tex;
	}	

	size = mida;
}


void CParticleSystem::setFading(float fr, float f0) {
	fadeR = fr;
	fade0 = f0;
}


void CParticleSystem::setColor(float *color, int n, bool ini) {
	if (ini) {
		numColorsI = n;
		colorsI = (float*)malloc(n*3*sizeof(float));
		for (int i = 0; i < 3*n; i++) colorsI[i] = color[i];
	}
	else {
		numColorsF = n;
		colorsF = (float*)malloc(n*3*sizeof(float));
		for (int i = 0; i < 3*n; i++) colorsF[i] = color[i];
	}
}


void CParticleSystem::setPosition(float x, float y, float z) {
	posX = x;
	posY = y;
	posZ = z;
}


void CParticleSystem::setDirection(float dx, float dy, float dz, float angXY, 
								   float angZ, float velR, float v0) 
{
	dirX = dx;
	dirY = dy;
	dirZ = dz;
	angleXY = angXY*M_PI/180.0f;
	angleZ = angZ*M_PI/180.0f;
	velRange = velR;
	vel0 = v0;
	rotacio = 0.0f;
}

void CParticleSystem::setRotacio(float rot) {
	rotacio = rot*M_PI/180.0f;
}


void CParticleSystem::init(int nump) {
	actiu = true;
	//nump: numero de particules, si supera MAX es queda MAX
	if (nump > MAX_PARTICLES) numParts = MAX_PARTICLES;
	else numParts = nump;
	for (int i = 0; i < numParts; i++) initParticle(i);
}


void CParticleSystem::initParticle(int i) {
	particle[i].active = true;							// Make All The Particles Active
	particle[i].life = 1.0f;							// Give All The Particles Full Life
	particle[i].fade = float(rand()%1000)/1000.0f*fadeR+fade0;
	int rancol = rand()%numColorsI;
	particle[i].r0 = colorsI[rancol*3+0];					// Select Red Color
	particle[i].g0 = colorsI[rancol*3+1];					// Select Green Color
	particle[i].b0 = colorsI[rancol*3+2];					// Select Blue Color
	rancol = rand()%numColorsF;
	particle[i].rf = colorsF[rancol*3+0];					// Select Red Color
	particle[i].gf = colorsF[rancol*3+1];					// Select Green Color
	particle[i].bf = colorsF[rancol*3+2];					// Select Blue Color
	particle[i].x = posX;
	particle[i].y = posY;
	particle[i].z = posZ;
	float angleA = ((float)(rand()%2048)/1024.0f - 1.0f)*angleXY;
	float angleB = ((float)(rand()%2048)/1024.0f - 1.0f)*angleZ;
	float v = (float)((rand()%1000)/1000.0f)*velRange+vel0;
	float xi = sin(angleB)*cos(angleA)*v;				// Random Speed On X Axis
	float yi = sin(angleB)*sin(angleA)*v;			// Random Speed On Y Axis
	float zi = cos(angleB)*v;							// Random Speed On Z Axis
	particle[i].xi = xi*cos(rotacio) + zi*sin(rotacio);		 
	particle[i].yi = yi;	
	particle[i].zi = zi*cos(rotacio) - xi*sin(rotacio);						
	particle[i].xg = 0.0f;								// Set Horizontal Pull To Zero
	particle[i].yg = 0.0f;								// Set Vertical Pull Downward
	particle[i].zg = 0.0f;								// Set Pull On Z Axis To Zero
}


void CParticleSystem::update(float time) {
	totalTime -= time;
	bool act = false;

	for (int loop = 0; loop < numParts; loop++) {
		if (particle[loop].active == false) continue;
		act = true;

		particle[loop].x += particle[loop].xi*time;  // Move On The X Axis By X Speed
		particle[loop].y += particle[loop].yi*time;  // Move On The Y Axis By Y Speed
		particle[loop].z += particle[loop].zi*time;  // Move On The Z Axis By Z Speed

		particle[loop].xi += particle[loop].xg;			// Take Pull On X Axis Into Account
		particle[loop].yi += particle[loop].yg;			// Take Pull On Y Axis Into Account
		particle[loop].zi += particle[loop].zg;			// Take Pull On Z Axis Into Account
		particle[loop].life -= particle[loop].fade*time;// Reduce Particles Life By 'Fade'

		particle[loop].r = (particle[loop].r0*particle[loop].life
							+particle[loop].rf*(1.0f-particle[loop].life));
		particle[loop].g = (particle[loop].g0*particle[loop].life
							+particle[loop].gf*(1.0f-particle[loop].life));
		particle[loop].b = (particle[loop].b0*particle[loop].life
							+particle[loop].bf*(1.0f-particle[loop].life));

		if (particle[loop].life < 0.0f) {
			if ( tipusEmisor == PS_LOOP || 
			    (tipusEmisor == PS_TIMED && totalTime > 0.0f))
			{
				initParticle(loop);
			}
			else particle[loop].active = false;
		}
	}

	actiu = act;
}


void CParticleSystem::draw(void)					// Here's Where We Do All The Drawing
{
	glPushMatrix();
	
	glDisable(GL_DEPTH_TEST);						// Disable Depth Testing
	glEnable(GL_BLEND);								// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	if (tipusPart == PT_TEX) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura);
	}

	for (int loop=0;loop<numParts;loop++) {
		if (particle[loop].active) {
			glColor4f(particle[loop].r, particle[loop].g,
					  particle[loop].b, particle[loop].life);

			switch(tipusPart) {
				case PT_TEX:
					glBegin(GL_QUADS);						
						glTexCoord2d(0,0); glVertex3f(particle[loop].x-2.5f,
													  particle[loop].y-2.5f,
													  particle[loop].z); // Top Right
						glTexCoord2d(0,1); glVertex3f(particle[loop].x-2.5f,
													  particle[loop].y+2.5f,
													  particle[loop].z); // Top Left
						glTexCoord2d(1,1); glVertex3f(particle[loop].x+2.5f,
													  particle[loop].y+2.5f,
													  particle[loop].z); // Top Right
						glTexCoord2d(1,0); glVertex3f(particle[loop].x+2.5f,
													  particle[loop].y-2.5f,
													  particle[loop].z); // Bottom Right
					glEnd();
					break; 
				case PT_DOT:
					glPointSize(size);
					glBegin(GL_POINTS);
						glVertex3f(particle[loop].x, particle[loop].y, particle[loop].z);
					glEnd();
					break;
				case PT_LINE:

					break;
				default:
					break;
			} 
		}
    }

	if (tipusPart == PT_TEX) glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


bool CParticleSystem::isActive() {
	return actiu;
}
