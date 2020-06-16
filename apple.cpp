#include "drawable_list.h"
#include "Apple.h"
#include "ascii_objects.h"


Apple::Apple(unsigned short x, unsigned short y)
	: Drawable({ x, y, 1, 1 }), isEaten(false) {}

// no additional memory allocations in Apple
Apple::~Apple()
{
}


void Apple::draw() 
{
	mini_gui_clear_rect(mg, bounding_box);
	mini_gui_print_rect(mg, bounding_box, APPLE);
}


void Apple::refresh() 
{
	mini_gui_clear_rect(mg, bounding_box);
	if (!isEaten)
		draw();
}



void Apple::step(DrawableList& lst) 
{
	Iterator iter(lst.begin());
	
	do {
		if (iter.get_object()->id() == 'M' &&		// if object is Monster
			iter.get_object()->collide(*this)) 
		{
			isEaten = true;							// mark Apple as eaten
			refresh();
		}
	} while (iter.next().valid());
	
}