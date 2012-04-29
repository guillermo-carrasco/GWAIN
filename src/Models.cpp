#include "Models.h"


//Ho podem fer millor "compilant glLists" dels CModels sota demanda

CModels* CModels::m_pInstance = 0;

CModels::CModels(void)
{
}

CModels::~CModels(void)
{
}

CModels* CModels::pGetInstance()
{
	if (CModels::m_pInstance == 0)
	{
		CModels::m_pInstance = new CModels();
		m_pInstance->generaTots();
	}
	return CModels::m_pInstance;
}

void CModels::generaTots() {
	models[M_TETRA] = buildTetraedre();
	models[M_CUBE]  = buildCub(); 
	models[M_ENAU]  = buildEsqueletNau();
	models[M_NAU]   = buildNau();
	models[M_OMNAU] = buildOmbraNau();
	models[M_BALA]  = buildBala();
	models[M_OBJS]  = buildObjecte();
	models[M_ENEMC] = buildEnemicCreador();
	models[M_ENEM1] = buildEnemic1();
	models[M_ENEM2] = buildEnemic2();
	models[M_ENEM3] = buildEnemic3();
	models[M_ENEM4] = buildEnemic4();
	models[M_ENEM5] = buildEnemic5();
	models[M_ENEM6] = buildEnemic6();
	models[M_ENEM7] = buildEnemic7();
}


void CModels::dibuixa(int idModel) {
	glCallList(models[idModel]);
}


/*****************************************************************************/
//                          MODELS  GENERALS                                 //
/*****************************************************************************/


unsigned int CModels::buildTerra() {
	unsigned int terreny = glGenLists(1);    
    
    glNewList(terreny, GL_COMPILE); 
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
        //DIBUIX DEL TERRA

        int numdivs = 500;
        glLineWidth(2.0);
        glColor3f (0.0f, 0.42f, 1.0f);  
        for (int i = -numdivs; i <= numdivs; i++) {
            glBegin(GL_LINES);
        	  glVertex3f(float(-numdivs), 0.0f, float(i));
        	  glVertex3f(float(+numdivs), 0.0f, float(i));
        	  glVertex3f(float(i), 0.0f, float(-numdivs));
        	  glVertex3f(float(i), 0.0f, float(+numdivs));
        	glEnd();   
        }
        
    	//DIBUIX DELS EIXOS
        glLineWidth(4.0);
    	glDisable(GL_BLEND);
    	glBegin(GL_LINES);
    	  glColor3f (1.0f, 0.0f, 0.0f);
    	  glVertex3f(0.0f, 0.0f, 0.0f);
    	  glVertex3f(3.0f, 0.0f, 0.0f);
    	  glVertex3f(3.0f, 0.0f, 0.0f);
    	  glVertex3f(2.8f, 0.2f, 0.0f);
    	  glVertex3f(3.0f, 0.0f, 0.0f);
    	  glVertex3f(2.8f,-0.2f, 0.0f);
    	 glEnd();
    	 glBegin(GL_LINES);
    	  glColor3f ( 0.0f, 1.0f, 0.0f);
    	  glVertex3f( 0.0f, 0.0f, 0.0f);
    	  glVertex3f( 0.0f, 3.0f, 0.0f);
    	  glVertex3f( 0.0f, 3.0f, 0.0f);
    	  glVertex3f( 0.2f, 2.8f, 0.0f);
    	  glVertex3f( 0.0f, 3.0f, 0.0f);
    	  glVertex3f(-0.2f, 2.8f, 0.0f);
    	glEnd();
    	glBegin(GL_LINES);
    	  glColor3f ( 0.0f, 0.0f, 1.0f);
    	  glVertex3f( 0.0f, 0.0f, 0.0f);
    	  glVertex3f( 0.0f, 0.0f, 3.0f);
    	  glVertex3f( 0.0f, 0.0f, 3.0f);
    	  glVertex3f( 0.2f, 0.0f, 2.8f);
    	  glVertex3f( 0.0f, 0.0f, 3.0f);
    	  glVertex3f(-0.2f, 0.0f, 2.8f);
    	glEnd();
    	glBegin(GL_POINTS);
    	  glColor3f (1.0f, 1.0f, 1.0f);
    	  glVertex3f(0.0f, 0.0f, 0.0f);
    	glEnd(); 
    
		glPopMatrix();
        glPopAttrib(); 
	glEndList();
	
	return terreny;
}


unsigned int CModels::buildTetraedre() {
	unsigned int tetraedre = glGenLists(1);    
    
    glNewList(tetraedre, GL_COMPILE);
    	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0.0f, 1.5f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();
	glEndList();
	
	return tetraedre;
}



unsigned int CModels::buildCub() {
	unsigned int cub = glGenLists(1);
	glNewList(cub,GL_COMPILE);
		glBegin(GL_QUADS);
			// Top Face
			glNormal3f( 0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f,  1.0f, -1.0f);
			glVertex3f(-1.0f,  1.0f,  1.0f);
			glVertex3f( 1.0f,  1.0f,  1.0f);
			glVertex3f( 1.0f,  1.0f, -1.0f);
			// Bottom Face
			glNormal3f( 0.0f,-1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f( 1.0f, -1.0f, -1.0f);
			glVertex3f( 1.0f, -1.0f,  1.0f);
			glVertex3f(-1.0f, -1.0f,  1.0f);
			// Front Face
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f,  1.0f);
			glVertex3f( 1.0f, -1.0f,  1.0f);
			glVertex3f( 1.0f,  1.0f,  1.0f);
			glVertex3f(-1.0f,  1.0f,  1.0f);
			// Back Face
			glNormal3f( 0.0f, 0.0f,-1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f,  1.0f, -1.0f);
			glVertex3f( 1.0f,  1.0f, -1.0f);
			glVertex3f( 1.0f, -1.0f, -1.0f);
			// Right face
			glNormal3f( 1.0f, 0.0f, 0.0f);
			glVertex3f( 1.0f, -1.0f, -1.0f);
			glVertex3f( 1.0f,  1.0f, -1.0f);
			glVertex3f( 1.0f,  1.0f,  1.0f);
			glVertex3f( 1.0f, -1.0f,  1.0f);
			// Left Face
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f,  1.0f);
			glVertex3f(-1.0f,  1.0f,  1.0f);
			glVertex3f(-1.0f,  1.0f, -1.0f);
		glEnd();
	glEndList();

	return cub;
}



/*****************************************************************************/
//                              MODELS  NAU                                  //
/*****************************************************************************/



unsigned int CModels::buildNau(){

    unsigned int nau = glGenLists(1); 

    glNewList(nau, GL_COMPILE);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
		glCallList(models[M_ENAU]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        for (int i = 4; i > 0; i--) {
            glLineWidth(float(i));
            glColor4f(1.0f/float(i), 1.0f/float(i), 1.0f/float(i), 1.0f/float(i));
			glCallList(models[M_ENAU]);
        }
		
        glPopMatrix();
        glPopAttrib();
    glEndList();

    return nau;
}


unsigned int CModels::buildEsqueletNau() {

	unsigned int nau = glGenLists(1); 

    glNewList(nau, GL_COMPILE);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();

			glBegin(GL_TRIANGLES);
				//cua
				glVertex3f(4.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 2.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, -3.0f);

				glVertex3f(-4.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 2.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, -3.0f);
			
				glVertex3f(4.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, -2.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, -3.0f);

				glVertex3f(-4.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, -2.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, -3.0f);

				//punxa esquerra
				glVertex3f(1.0f, 0.0f, 5.0f);
				glVertex3f(2.0f, 1.25f, 1.0f);
				glVertex3f(2.0f, -1.25f, 1.0f);

				glVertex3f(1.0f, 0.0f, 5.0f);
				glVertex3f(2.0f, 1.25f, 1.0f);
				glVertex3f(4.0f, 0.0f, 0.0f);

				glVertex3f(1.0f, 0.0f, 5.0f);
				glVertex3f(2.0f, -1.25f, 1.0f);
				glVertex3f(4.0f, 0.0f, 0.0f);

				//punxa dreta
				glVertex3f(-1.0f, 0.0f, 5.0f);
				glVertex3f(-2.0f, 1.25f, 1.0f);
				glVertex3f(-2.0f, -1.25f, 1.0f);

				glVertex3f(-1.0f, 0.0f, 5.0f);
				glVertex3f(-2.0f, 1.25f, 1.0f);
				glVertex3f(-4.0f, 0.0f, 0.0f);

				glVertex3f(-1.0f, 0.0f, 5.0f);
				glVertex3f(-2.0f, -1.25f, 1.0f);
				glVertex3f(-4.0f, 0.0f, 0.0f);

				//centre
				glVertex3f(4.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 2.0f, 0.0f);
				glVertex3f(2.0f, 1.25f, 1.0f);

				glVertex3f(-4.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 2.0f, 0.0f);
				glVertex3f(-2.0f, 1.25f, 1.0f);

				glVertex3f(4.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, -2.0f, 0.0f);
				glVertex3f(2.0f, -1.25f, 1.0f);

				glVertex3f(-4.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, -2.0f, 0.0f);
				glVertex3f(-2.0f, -1.25f, 1.0f);                
            glEnd();

			glBegin(GL_QUADS);
				glVertex3f(2.0f, 1.25f, 1.0f);
				glVertex3f(2.0f, -1.25f, 1.0f);
				glVertex3f(0.0f, -2.0f, 0.0f);
				glVertex3f(0.0f, 2.0f, 0.0f);

				glVertex3f(-2.0f, 1.25f, 1.0f);
				glVertex3f(-2.0f, -1.25f, 1.0f);
				glVertex3f(0.0f, -2.0f, 0.0f);
				glVertex3f(0.0f, 2.0f, 0.0f);
			glEnd();
		glPopMatrix();
        glPopAttrib();
    glEndList();

    return nau;

}



unsigned int CModels::buildOmbraNau() {

	unsigned int nau = glGenLists(1); 

    glNewList(nau, GL_COMPILE);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();

        glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
		
		glLineWidth(2.0f);
		glBegin(GL_LINE_LOOP);
			glVertex3f(0.0f, 0.0f, -3.0f);
			glVertex3f(4.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 5.0f);
			glVertex3f(2.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-2.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, 0.0f, 5.0f);
			glVertex3f(-4.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, -3.0f);
		glEnd();

		glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(1.0f, 0.0f, 5.0f);
			glVertex3f(4.0f, 0.0f, 0.0f);
			glVertex3f(2.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, -3.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-4.0f, 0.0f, 0.0f);
			glVertex3f(-2.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, 0.0f, 5.0f);
		glEnd();
		glEnable(GL_DEPTH_TEST);

		glPopMatrix();
        glPopAttrib();
    glEndList();

    return nau;

}


/*****************************************************************************/
//                        MODELS  BALA i OBJECTE                             //
/*****************************************************************************/


unsigned int CModels::buildBala(){
	unsigned int bala = glGenLists(1);    

    glNewList(bala, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 1.0f, 1.0f, 0.75f);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(3.0f);
		glBegin(GL_LINE_STRIP);
			glVertex3f(+0.5f, 0.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, 0.0f, -1.0f);
		glEnd();
		

	    glPopMatrix();
        glPopAttrib();
	glEndList();

	return bala;
}



unsigned int CModels::buildObjecte() {
	unsigned int objecte = glGenLists(1);    

    glNewList(objecte, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glScalef(1.5f, 1.5f, 1.5f);
		
		//Esfera envolvent de l'objecte
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLUquadricObj*  q = gluNewQuadric();
				glColor4f(1.0f, 1.0f, 1.0f, 0.15f);
				gluSphere(q,1.7,32,32);
				glColor4f(1.0f, 1.0f, 1.0f, 0.075f);
				gluSphere(q,2.0,32,32);
		gluDeleteQuadric(q);

	    glPopMatrix();
        glPopAttrib();
	glEndList();

	return objecte;
}


/*****************************************************************************/
//                          MODELS  ENEMICS                                  //
/*****************************************************************************/

unsigned int CModels::buildEnemic1() {
	unsigned int enemic = glGenLists(1);    
    
    glNewList(enemic, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(64.0f/255.0f, 12.0f/255.0f, 120.0f/255.0f, 0.8f);
		
		//cares
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glScalef(1.2f, 1.2f, 1.2f);
		glTranslatef(0.0f, 0.7f, 0.0f);
		glCallList(models[M_TETRA]);
		glTranslatef(0.0f, -1.4f, 0.0f);
		glRotatef(180.0f, 1, 0, 0);
		glCallList(models[M_TETRA]);
		glTranslatef(0.0f, -0.7f, 0.0f);
		glRotatef(90.0f, 1, 0, 0);
		glRotatef(45.0f, 0, 0, 1);
		glRotatef(45.0f, 0, 1, 0);
		glTranslatef(0.0f, 0.7f, 0.0f);
		glCallList(models[M_TETRA]);
		glTranslatef(0.0f, -0.7f, 0.0f);
		glRotatef(-45.0f, 0, 1, 0);
		glRotatef(90.0f, 0, 0, 1);
		glRotatef(45.0f, 0, 1, 0);
		glTranslatef(0.0f, 0.7f, 0.0f);
		glCallList(models[M_TETRA]);
		glTranslatef(0.0f, -0.7f, 0.0f);
		glRotatef(-45.0f, 0, 1, 0);
		glRotatef(90.0f, 0, 0, 1);
		glRotatef(45.0f, 0, 1, 0);
		glTranslatef(0.0f, 0.7f, 0.0f);
		glCallList(models[M_TETRA]);
		glTranslatef(0.0f, -0.7f, 0.0f);
		glRotatef(-45.0f, 0, 1, 0);
		glRotatef(90.0f, 0, 0, 1);
		glRotatef(45.0f, 0, 1, 0);
		glTranslatef(0.0f, 0.7f, 0.0f);
		glCallList(models[M_TETRA]);

    	//DIBUIX DE LES ARESTES
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		for (int i = 6; i > 0; i--) {
			glPopMatrix();
			glPushMatrix();
			glLineWidth(float(i));
			glColor4f(64.0f/255.0f, 12.0f/255.0f, 120.0f/255.0f, 1.0f/float(i));
			
			glScalef(1.2f, 1.2f, 1.2f);
			glTranslatef(0.0f, 0.7f, 0.0f);
			glCallList(models[M_TETRA]);
			glTranslatef(0.0f, -1.4f, 0.0f);
			glRotatef(180.0f, 1, 0, 0);
			glCallList(models[M_TETRA]);
			glTranslatef(0.0f, -0.7f, 0.0f);
			glRotatef(90.0f, 1, 0, 0);
			glRotatef(45.0f, 0, 0, 1);
			glRotatef(45.0f, 0, 1, 0);
			glTranslatef(0.0f, 0.7f, 0.0f);
			glCallList(models[M_TETRA]);
			glTranslatef(0.0f, -0.7f, 0.0f);
			glRotatef(-45.0f, 0, 1, 0);
			glRotatef(90.0f, 0, 0, 1);
			glRotatef(45.0f, 0, 1, 0);
			glTranslatef(0.0f, 0.7f, 0.0f);
			glCallList(models[M_TETRA]);
			glTranslatef(0.0f, -0.7f, 0.0f);
			glRotatef(-45.0f, 0, 1, 0);
			glRotatef(90.0f, 0, 0, 1);
			glRotatef(45.0f, 0, 1, 0);
			glTranslatef(0.0f, 0.7f, 0.0f);
			glCallList(models[M_TETRA]);
			glTranslatef(0.0f, -0.7f, 0.0f);
			glRotatef(-45.0f, 0, 1, 0);
			glRotatef(90.0f, 0, 0, 1);
			glRotatef(45.0f, 0, 1, 0);
			glTranslatef(0.0f, 0.7f, 0.0f);
			glCallList(models[M_TETRA]);
		}
    	
		glPopMatrix();
        glPopAttrib(); 
	glEndList();
	
	return enemic;
}


unsigned int CModels::buildEnemic2() {

	unsigned int enemic = glGenLists(1);    
    
    glNewList(enemic, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 0.7f, 1.0f, 0.8f);

		//cares
		glScalef(1.5f, 1.5f, 1.5f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCallList(models[M_TETRA]);
		glRotatef(180.0f, 1, 0, 0);
		glCallList(models[M_TETRA]);

    	//DIBUIX DE LES ARESTES
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		for (int i = 6; i > 0; i--) {
			glLineWidth(float(i));
			glColor4f(0.0, 1.0f, 1.0f, 1.0f/float(2*i));
			glCallList(models[M_TETRA]);
			glRotatef(180.0f, 1, 0, 0);
			glCallList(models[M_TETRA]);
		}
    	
		glPopMatrix();
        glPopAttrib(); 
	glEndList();
	
	return enemic;
}


unsigned int CModels::buildEnemic3() {
    unsigned int enemic = glGenLists(1); 

    glNewList(enemic, GL_COMPILE);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();
   
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f, 0.8f, 0.2f, 0.8f);
		glScalef(1.2f, 1.2f, 1.2f);

        //CARES EXTERNES
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glCallList(models[M_CUBE]);

        //DIBUIX DE LES ARESTES EXTERNES
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        for (int i = 6; i > 0; i--) {
            glLineWidth(float(i));
            glColor4f(0.0, 0.9f/float(i), 0.2f/float(i), 1.0f/float(i));
			glCallList(models[M_CUBE]);
        }


		//CARES EXTERNES
        glColor4f(0.0f, 0.8f, 0.2f, 0.8f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glScalef(1/sqrt(2.0f), 1/sqrt(2.0f), 1/sqrt(2.0f));
		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
        glCallList(models[M_CUBE]);

        //DIBUIX DE LES ARESTES EXTERNES
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        for (int i = 6; i > 0; i--) {
            glLineWidth(float(i));
            glColor4f(0.0, 0.9f/float(i), 0.2f/float(i), 1.0f/float(i));
			glCallList(models[M_CUBE]);
        }

       
        glPopMatrix();
        glPopAttrib();
    glEndList();
   
    return enemic;
}



unsigned int CModels::buildEnemic4(){
	unsigned int enemic = glGenLists(1);    

    glNewList(enemic, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		//Enemic 4: esfera
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLUquadricObj*  q = gluNewQuadric();

		glScalef(1.5f, 1.5f, 1.5f);
		//glPushMatrix();
			for (float i = 1.0f; i <= 5.0f; i+=1.0f) {
				glScalef(1.0f/i, 1.0f/i, 1.0f/i);
				//glColor4f(1.0f, 0.2f+i/10.0f, 0.0f, i/5.0f);
				glColor4f(0.0f, 0.2f+i/10.0f, 1.0f, i/5.0f);
				gluSphere(q,1,32,32);
				glScalef(i/1.0f, i/1.0f, i/1.0f);
			}
		//glPopMatrix();
		gluDeleteQuadric(q);

	    glPopMatrix();
        glPopAttrib();
	glEndList();

	return enemic;
}

unsigned int CModels::buildEnemic5(){
	unsigned int enemic = glGenLists(1);  

    glNewList(enemic, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
		glScalef(2.0f, 2.0f, 2.0f);

		//Enemic 5: Triangle

		//Dibuix de les cares
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0.0f, 1.3f, 0.0f);
			glVertex3f(0.8f, 0.0f, -0.7f);
			glVertex3f(-0.8f, 0.0f, -0.7f); 
			glVertex3f(0.0f, 0.0f, 0.9f);
			glVertex3f(0.8f, 0.0f, -0.7f);
		glEnd();

		//Dibuix de les arestes
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glScalef(1.1f, 1.1f, 1.1f);
        for (int i = 6; i > 0; i--) {
            glLineWidth(float(i));
            glColor4f(1.0, 1.0f, 0.4f, 1.0f/float(2*i));
			glBegin(GL_TRIANGLE_FAN);
				glVertex3f(0.0f, 1.3f, 0.0f);
				glVertex3f(0.8f, 0.0f, -0.7f);
				glVertex3f(-0.8f, 0.0f, -0.7f); 
				glVertex3f(0.0f, 0.0f, 1.0f);
				glVertex3f(0.8f, 0.0f, -0.7f);
			glEnd();
		}

		glPopMatrix();
        glPopAttrib();
	glEndList();

	return enemic;
}


unsigned int CModels::buildEnemic6(){
	unsigned int enemic = glGenLists(1);  

    glNewList(enemic, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 0.25f, 0.2f, 0.7f);

		//Enemic 6: Cub divisiu
		glScalef(2.0f, 2.0f, 2.0f);

		//Dibuix de les cares
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glScalef(0.9f, 0.9f, 0.9f);
		glCallList(models[M_CUBE]);
		glScalef(1/0.9f, 1/0.9f, 1/0.9f);

		//Dibuix de les arestes
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        for (int i = 6; i > 0; i--) {
			glLineWidth(float(i));
            glColor4f(1.0, 0.25f, 0.2f, 1.0f/float(i));
			glCallList(models[M_CUBE]);

			glScalef(0.95f, 0.95f, 0.95f);
			glBegin(GL_QUADS);
				
				glVertex3f(1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);

				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(0.0f, 1.0f, 0.0f);
				glVertex3f(0.0f, -1.0f, 0.0f);
			glEnd();
			glScalef(1/0.95f, 1/0.95f, 1/0.95f);
		}


		glPopMatrix();
        glPopAttrib();
	glEndList();

	return enemic;
}



unsigned int CModels::buildEnemic7(){
	unsigned int enemic = glGenLists(1);  

    glNewList(enemic, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
		//Enemic 7: Cub divisiu mini
		glScalef(0.5, 0.5, 0.5);
		glCallList(models[M_ENEM6]);

		glPopMatrix();
        glPopAttrib();
	glEndList();

	return enemic;
}


unsigned int CModels::buildEnemicCreador(){
	unsigned int enemic = glGenLists(1);  

    glNewList(enemic, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();
    
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glScalef(2.0f, 2.0f, 2.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLUquadricObj*  q = gluNewQuadric();
		for (float i = 1.0f; i <= 5.0f; i+=1.0f) {
			glScalef(1.0f/i, 1.0f/i, 1.0f/i);
			glColor4f(1.0f, 0.2f+i/10.0f, 0.0f, i/5.0f);
			gluSphere(q,2,32,32);
			glScalef(i/1.0f, i/1.0f, i/1.0f);
		}
		gluDeleteQuadric(q);

		glPopMatrix();
        glPopAttrib();
	glEndList();

	return enemic;
}




