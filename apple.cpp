#include "drawable_list.h"
#include "apple.h"
#include "ascii_objects.h"


Apple::Apple(unsigned short x, unsigned short y)
	: Drawable({ x, y, 1, 1 }), isEaten(false),isDrawn(false) {ID='A';}

// no additional memory allocations in Apple
Apple::~Apple() = default;


void Apple::draw() 
{
	if (! isDrawn){
        mini_gui_print_rect(mg, bounding_box, APPLE);
        isDrawn = true;
	}

}


void Apple::refresh() 
{
	if (isDrawn) {
        mini_gui_clear_rect(mg, bounding_box);
    }
    if (!isEaten) {
        draw();
    }
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

int  Apple::id() {
    return Apple::ID;
}

void Apple::move(direction_t direction) {}
