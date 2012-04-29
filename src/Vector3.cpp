#include "Vector3.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


CVector3::CVector3() {
    v[0] = v[1] = v[2] = 0.0f;
}


CVector3::CVector3(float x, float y, float z) {
    v[0] = x;
	v[1] = y;
	v[2] = z;
}


CVector3::~CVector3() {
}


void CVector3::setVector(float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}


void CVector3::getValues(float w[3]) {
    w[0] = v[0];
    w[1] = v[1];
    w[2] = v[2];
}


float CVector3::getX() {
	return v[0];
}


float CVector3::getY() {
	return v[1];
}


float CVector3::getZ() {
	return v[2];
}


void CVector3::getUnit(float w[3]) {
    float m = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if (m != 0 && m != 1) {
        w[0] = v[0]/m;  
        w[1] = v[1]/m;
        w[2] = v[2]/m;  
    }
    else {
        w[0] = v[0];
        w[1] = v[1];
        w[2] = v[2];
    }
}


CVector3 CVector3::getUnit() {	
    CVector3 _v;
	float m = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if (m != 0 && m != 1) {
        _v.v[0] = v[0]/m;  
        _v.v[1] = v[1]/m;
        _v.v[2] = v[2]/m;  
    }
    else {
        _v.v[0] = v[0];
        _v.v[1] = v[1];
        _v.v[2] = v[2];
    }
	return _v;
}


void CVector3::normalize() {	
	float m = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if (m != 0 && m != 1) {
        v[0] = v[0]/m;  
        v[1] = v[1]/m;
        v[2] = v[2]/m;  
    }
}


float CVector3::getNorm() {	
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}


void CVector3::addVector(float x, float y, float z) {
    v[0] += x;
    v[1] += y;
    v[2] += z;
}


void CVector3::addVector(const CVector3& w) {
    v[0] += w.v[0];
    v[1] += w.v[1];
    v[2] += w.v[2];
}


float CVector3::dotProduct(const CVector3& w) {
	return v[0]*w.v[0] + v[1]*w.v[1] + v[2]*w.v[2];
}


CVector3 CVector3::crossProduct(const CVector3& w) {	
	CVector3 z;	
	z.v[0] = v[1]*w.v[2] - w.v[1]*v[2];
	z.v[1] = w.v[0]*v[2] - v[0]*w.v[2];
	z.v[2] = v[0]*w.v[1] - w.v[0]*v[1];
	return z;
}



/*   OPERATORS   */



void CVector3::operator=(const CVector3& w) {
	v[0] = w.v[0];
	v[1] = w.v[1];
	v[2] = w.v[2];
}


CVector3 CVector3::operator+(const CVector3& w) {
	CVector3 z;
	z.v[0] = v[0] + w.v[0];
	z.v[1] = v[1] + w.v[1];
	z.v[2] = v[2] + w.v[2];
	return z;
}


void CVector3::operator+=(const CVector3& w) {
	v[0] += w.v[0];
	v[1] += w.v[1];
	v[2] += w.v[2];
}


CVector3 CVector3::operator-(const CVector3& w) {
	CVector3 z;
	z.v[0] = v[0] - w.v[0];
	z.v[1] = v[1] - w.v[1];
	z.v[2] = v[2] - w.v[2];
	return z;
}


void CVector3::operator-=(const CVector3& w) {
	v[0] -= w.v[0];
	v[1] -= w.v[1];
	v[2] -= w.v[2];
}


CVector3 CVector3::operator*(float f) {
	CVector3 z;
	z.v[0] = f*v[0];
	z.v[1] = f*v[1];
	z.v[2] = f*v[2];
	return z;
}


CVector3 CVector3::operator/(float f) {
	CVector3 z;
	z.v[0] = v[0]/f;
	z.v[1] = v[1]/f;
	z.v[2] = v[2]/f;
	return z;
}


float CVector3::operator*(CVector3 w) {
	return v[0]*w.v[0] + v[1]*w.v[1] + v[2]*w.v[2];
}


CVector3 CVector3::operator^(CVector3 w) {
	CVector3 z;	
	z.v[0] = v[1]*w.v[2] - w.v[1]*v[2];
	z.v[1] = w.v[0]*v[2] - v[0]*w.v[2];
	z.v[2] = v[0]*w.v[1] - w.v[0]*v[1];
	return z;
}


float distance(CVector3& p1, CVector3& p2) {
    CVector3 z = p2 - p1;    
    return z.getNorm();
}


float angle(CVector3& v, CVector3& w) {
    float a = (v*w)/(v.getNorm() * w.getNorm());
    return (float)float(acos(a))*180.0f/float(M_PI);
}
