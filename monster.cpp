#include "monster.h"
#include <string.h>
#include "drawable_list.h" 


// initialize Monster
Monster::Monster(unsigned short x, unsigned short y, int direction_hold)
	: Drawable({ x, y, 1, 1 }), level(1), vel(1), current_direction(left),
		direction_hold(direction_hold), direction_counter(0), next_bb(bounding_box)
{
	gfx = MONSTER0;
}

Monster::~Monster()
{
}


// move Monster. Monster changes direction only if it finished moving in her
// previous direction. moves only if within bounderies of mg (mini gui)
void Monster::move(direction_t direction)
{
	// update current direction only if finished moving in that direction
	if (direction_counter == 0) {
		current_direction = direction;
		direction_counter = direction_hold;
	}
	struct rect screen = mini_gui_get_screen_size(mg);
	// update cuurent direction, and checks if within bounderies
	if (current_direction == left &&
		next_bb.x + vel + next_bb.width <= screen.x + screen.width)
	{
		next_bb.x += vel;
	}
	else if (current_direction == right &&
		next_bb.x - vel + next_bb.width <= screen.x - screen.width)
	{
		next_bb.x -= vel;
	}
	else if (current_direction == up &&
		next_bb.y + vel - next_bb.height <= screen.y - screen.height)
	{
		next_bb.y -= vel;
	}
	else if (next_bb.y + vel + next_bb.height <= screen.y + screen.height)
	{
		next_bb.y += vel;
	}

	
	--direction_hold;
	draw();
}


void Monster::draw()
{
	mini_gui_clear_rect(mg, bounding_box);
	bounding_box = next_bb;
	mini_gui_print_rect(mg, bounding_box, APPLE);
}


// updates monster's graphics according to level
void Monster::refresh()
{
	if (level < 5) {
		gfx = MONSTER0;
		vel = 1;
		next_bb.height = 1;
		next_bb.width = 1;
	}
	else if (level < 15) {
		gfx = MONSTER1;
		vel = 1;
		next_bb.height = 1;
		next_bb.width = 3;
	}
	else if (level < 25) {
		gfx = MONSTER2;
		vel = 1;
		next_bb.height = 2;
		next_bb.width = 3;
	}
	else {
		gfx = MONSTER3;
		vel = 2;
		next_bb.height = 3;
		next_bb.width = 8;
	}
}


// checks if this Monster collides with an Apple or a Monster
// and apdates the colliding Drawables accordingly
// recieves list of drawables 
void Monster::step(DrawableList& lst)
{
	Iterator iter(lst.begin());
	Iterator thisIter(iter);
	bool isEaten = false;			// indicates if this Monster is eaten
	int initial_level = level;
	do {
		if (iter.get_object() == this) {	// skip this when checking collision
			thisIter = iter;				// create Iterator tha points to this
			continue;
		}

		if (iter.get_object()->collide(*this))			// if there is collision
		{
			if (iter.get_object()->id() == 'M') {		// if it's a Monster, find who wins
				if (level <= ((Monster*)iter.get_object())->level) {
					((Monster*)iter.get_object())->level += level;
					break;
				}
				else {
					level += ((Monster*)iter.get_object())->level;
					lst.erase(iter);
				}
			}
			else if (iter.get_object()->id() == 'A') {	// if it's an Apple, this Monster eats the Apple
				level++;
				lst.erase(iter);
			}
			
		}
	} while (iter.next().valid());
	
	if (isEaten) {					// if this Monster was eaten, erase it
		lst.erase(thisIter);
		return;
	}

	if (initial_level == level)		// refresh graphics if changes were made
		refresh();
}








