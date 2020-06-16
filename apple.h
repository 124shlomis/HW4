#ifndef APPLE_H
#define APPLE_H

#include "drawable.h"

class Apple : public Drawable {

private:
    // true if the apple is eaten
	bool isEaten;
    bool isDrawn;
    int ID;

public:

	Apple(unsigned short x, unsigned short y);

	~Apple() override;

	// does nothing, since an Apple can't move
	void move(direction_t direction) override;

	// draws the Apple
	void draw() override;

	// refreshes the Apple graphics 
	void refresh()override ;

	// Apple id is A
	 int id() override ;

	// update the Apple if it is eaten
	void step(DrawableList& lst) override;
};

#endif