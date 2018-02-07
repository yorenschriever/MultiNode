#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <math.h>

struct RGBA {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  float a;
};



static const struct RGBA TRANSPARENT = { 0,0,0,0 };


enum SocketDrive { Push, Pull}; 

class Position
{
public:
	float x;
	float y;
	Position() {};
	Position(float x, float y){ this->x=x; this->y=y; }
	//Position(Position p) { this->x=p.x; this->y=p.y; }
	
	void TranslateMe(float x, float y) { this->x+=x; this->y+=y; }
	Position Translate(float x, float y){ return Position(this->x+x, this->y+y); }

	void RotateMe(float r){
		float newx = this->x * cos(r) - this->y * sin(r);
		float newy = this->x * sin(r) + this->y * cos(r);

		this->x = newx;
		this->y = newy;
	}
};

#endif