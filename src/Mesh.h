#pragma once

#include <vector>
#include "Globals.h"
#include "Vector3.h"

#define K_FACTOR	0.95f
#define CELL_SPACE  4.0f
#define MAX_AMP		100.0f


struct Vertex {
	float x, y, z;

	Vertex(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vertex() {
	}
};


class Mesh
{
	public:
		Mesh(void);
		~Mesh(void);

		Mesh(int n, int m);
		void init();
		void applyForce(float px, float pz, float fx, float fy, float fz);
		void update(float time);
		void draw();
		
	private:
		std::vector<Vertex>		m_vVertexos;
		std::vector<CVector3>	m_vVelocitats;
		int n;
		int m;
};
