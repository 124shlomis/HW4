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

	if (!isDrawn && !isEaten) {
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
	for (Iterator iter = lst.begin(); (iter.get_object()->id()=='M') && iter.valid() ; iter.next()){

	    if (iter.get_object()->collide(*this)){ // case apple is eaten by monster.
            isEaten = true;
            isDrawn = false;
	    }
	}
}