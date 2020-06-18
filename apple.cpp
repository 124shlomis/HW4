#include "drawable_list.h"
#include "apple.h"
#include "ascii_objects.h"


Apple::Apple(unsigned short x, unsigned short y)
	: Drawable({ x, y, 1, 1 }),
	  isEaten(false), isDrawn(false) {}

// no additional memory allocations in Apple
Apple::~Apple()= default; // clear rect in parent dtor


void Apple::draw() 
{
	if (!isDrawn) {
		mini_gui_print_rect(mg, bounding_box, APPLE);
		isDrawn = true;
	}
}


void Apple::refresh() {}

int Apple::id()
{
	return 'A';
}



void Apple::step(DrawableList& lst) 
{
	Iterator iter(lst.begin());
	
	do {
		if (iter.get_object()->id() == 'M' &&		// if object is Monster
			iter.get_object()->collide(*this)) 
		{
			isEaten = true;							// mark Apple as eaten
		}
	} while (iter.next().valid());
	
}