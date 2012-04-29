//Classe: CVector3
//Autor: Oscar Argudo
//Descripció: vector a R3 amb les operacions habituals

#pragma once
#include <cmath>


class CVector3 {
	private:
		float v[3];

	public:
        //constructors
		CVector3();
		CVector3(float x, float y, float z);
		//destructor
		~CVector3();

        //funcions set/get
		void setVector(float x, float y, float z);
		void getValues(float w[3]);
		float getX();
		float getY();
		float getZ();
		void getUnit(float w[3]);
		CVector3 getUnit();
		float getNorm();
		
		//operacions amb vectors
		void addVector(float x, float y, float z);
		void addVector(const CVector3& w);
		float dotProduct(const CVector3& w);
		CVector3 crossProduct(const CVector3& w);
		void normalize();

        //sobrecàrrega dels operadors
		void operator=(const CVector3& w);
		CVector3 operator+(const CVector3& w);
		CVector3 operator-(const CVector3& w);
		void operator+=(const CVector3& w);
		void operator-=(const CVector3& w);
	    CVector3 operator*(float f);
	    CVector3 operator/(float f);
    	float operator*(CVector3 w);
		CVector3 operator^(CVector3 w);
};


float distance(const CVector3& p1, const CVector3& p2);
float angle(const CVector3& v, const CVector3& w);
