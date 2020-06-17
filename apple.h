#ifndef APPLE_H
#define APPLE_H

#include "drawable.h"

class Apple : public Drawable { 
	// true if the apple is eaten
	bool isEaten;
	bool isDrawn;

public:

	Apple(unsigned short x, unsigned short y);

	virtual ~Apple();

	// does nothing, since an Apple can't move
	virtual void move(direction_t direction) {};

	// draws the Apple
	virtual void draw();

	// refreshes the Apple graphics 
	virtual void refresh();

	// Apple id
	virtual int id();

	// apdate the Apple if he is eaten
	virtual void step(DrawableList& lst);
};




#endif