#ifndef APPLE_H
#define APPLE_H

/* includes */
#include "drawable.h"
#include "ascii_objects.h"
#include "drawable_list.h"


// Apple class:
class Apple : public Drawable { 
	// true if the apple is eaten
	bool isEaten;
	bool isDrawn;

public:

	Apple(unsigned short x, unsigned short y);

	~Apple() override;

	// doing nothing, since an Apple can't move
	void move(direction_t direction) override;

	// draws the Apple
	void draw() override;

	// refreshes the Apple graphics 
	void refresh() override;

	// Apple id
	int id() override;

	// update the Apple if he is eaten
	void step(DrawableList& lst) override;
};

#endif