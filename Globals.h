#ifndef GLOBALS_H
#define GLOBALS_H

////#define		NUMSTARS	10000

typedef struct
{
	int x;
	int y;
} csPOINT;

typedef struct
{
	float r;
	float g;
	float b;
}  COLOR;

extern const COLOR BLACK, WHITE, RED, GREEN, BLUE;

class GUIElement
{
public:
	virtual void Draw() const=0;
};


#endif