#include "BBox.h"

CBBox::CBBox(void)
{
}

CBBox::~CBBox(void)
{
}

CBBox::CBBox(float l, float r, float t, float b) {
	left = l;
	right = r;
	top = t;
	bottom = b;
}
		
bool CBBox::collide(CBBox bb2) {
	if (bb2.left   > right)  return false;
	if (bb2.right  < left)   return false;
	if (bb2.bottom > top)    return false;
	if (bb2.top    < bottom) return false;
	return true;
}

bool CBBox::inside(float x, float y) {
	if (x < left) return false;
	if (x > right) return false;
	if (y < bottom) return false;
	if (y > top) return false;
	return true;
}


bool CBBox::circle(float x, float y, float r) {
	if ((x+r) < left) return false;
	if ((x-r) > right) return false;
	if ((y+r) < bottom) return false;
	if ((y-r) > top) return false;
	return true;
}
