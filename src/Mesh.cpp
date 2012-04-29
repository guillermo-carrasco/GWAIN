#include "Mesh.h"



Mesh::Mesh(void)
{
}


Mesh::~Mesh(void)
{
}


Mesh::Mesh(int _n, int _m) {
	n = _n;
	m = _m;
}


void Mesh::init() {
	m_vVertexos = std::vector<Vertex> (4*n*m);
	m_vVelocitats = std::vector<CVector3> (n*m);
	float x, z;
	int k = 0;
	for (int i = 0; i <= n-1; i++) {
		for (int j = 0; j <= m-1; j++) {
			x = CELL_SPACE*((float)i-float(n)/2.0f);
			z = CELL_SPACE*((float)j-float(m)/2.0f);
			//m_vVertexos.push_back(Vertex(x, 0.0f, z));
			m_vVertexos[k] = Vertex(x, 0.0f, z);
			k++;
			x = CELL_SPACE*((float)i+1-float(n)/2.0f);
			//m_vVertexos.push_back(Vertex(x, 0.0f, z));
			m_vVertexos[k] = Vertex(x, 0.0f, z);
			k++;
			z = CELL_SPACE*((float)j+1-float(m)/2.0f);
			//m_vVertexos.push_back(Vertex(x, 0.0f, z));
			m_vVertexos[k] = Vertex(x, 0.0f, z);
			k++;
			x = CELL_SPACE*((float)i-float(n)/2.0f);
			//m_vVertexos.push_back(Vertex(x, 0.0f, z));
			m_vVertexos[k] = Vertex(x, 0.0f, z);
			k++;
		}
	}
}


void Mesh::applyForce(float px, float pz, float fx, float fy, float fz) {
	int i = (int)px; 
	int j = (int)pz;
	CVector3 nf(fx, fy, fz);
	m_vVelocitats[i*m+j] += nf*K_FACTOR;
}


void Mesh::update(float time) {
	
}


void Mesh::draw() {
	glDisable(GL_BLEND);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.42f, 1.0f);
	glEnableClientState(GL_VERTEX_ARRAY); 
	glVertexPointer(3, GL_FLOAT, 0, &m_vVertexos[0]); 
	glDrawArrays(GL_QUADS, 0, 4*n*m);
	glDisableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_BLEND);
}
