#pragma once

class CBBox
{
	public:
		CBBox();
		CBBox(float l, float r, float t, float b);
		~CBBox(void);
		
		bool collide(CBBox bb2);
		bool inside(float x, float y);
		bool circle(float x, float y, float r);

		float left, right, top, bottom;
};
