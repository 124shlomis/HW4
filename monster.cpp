/* includes */
#include "monster.h"


// initialize Monster
Monster::Monster(unsigned short x, unsigned short y, int direction_hold)
	: Drawable({ x, y, 1, 1 }), level(1), vel(1), current_direction(left),
		direction_hold(direction_hold), direction_counter(0), next_bb(bounding_box),gfx(MONSTER0){}

Monster::~Monster() = default;


// move Monster. Monster changes direction only if it finished moving in her
// previous direction. moves only if within boundaries of mg (mini gui)
void Monster::move(direction_t direction)
{
	// update current direction only if finished moving in that direction
	if (direction_counter == 0) {
		current_direction = direction;
		direction_counter = direction_hold;
	}
	struct rect world_size = mini_gui_get_screen_size(mg);
	// update current direction, and checks if within boundaries
    switch (current_direction) {

        case left:
            if ( (next_bb.x - vel) > world_size.x ) {
                next_bb.x -= vel;
            }
            break;
        case right:
            if ( (next_bb.x + next_bb.width + vel) < (world_size.x + world_size.width) ) {
                next_bb.x += vel;
            }
            break;
        case up:
            if ( (next_bb.y - vel) > world_size.y) {
                next_bb.y -= vel;
            }
            break;
        case down:
            if ( (next_bb.y + next_bb.height + vel ) < (world_size.y + world_size.height) ){
                next_bb.y += vel;
            }
            break;
    }
    if (direction_counter>0){
        --direction_counter;
    }


}


void Monster::draw()
{
	mini_gui_clear_rect(mg, bounding_box);
	bounding_box = next_bb;
	mini_gui_print_rect(mg, bounding_box, gfx);
}


int Monster::id()
{
	return 'M';
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

	// Get world size
	struct rect world_size = mini_gui_get_screen_size(mg);
	// Fix position in case of screen overflow
	if (next_bb.x + next_bb.width >= world_size.width) {
		next_bb.x = world_size.width - next_bb.width;
	}
	if (next_bb.y + next_bb.height >= world_size.height) {
		next_bb.y = world_size.height - next_bb.height;
	}
}


// checks if this Monster collides with an Apple or a Monster
// and Updates the colliding Drawable accordingly
// receives list of drawable

void Monster::step(DrawableList& lst){
    for (Iterator iter = lst.begin(); iter.valid() ; iter.next()){

        if ( iter.get_object() == this ){ // case the iterator pointing this.
            continue;
        }

        if ( this->collide(*iter.get_object()) ) { // check colliding

            int Draw_ID = iter.get_object()->id();

            switch (Draw_ID) {

                case 'A': // apple
                    level++;
                    lst.erase(iter);
                    break;

                case 'M': // monster - fight!
                {
                    auto* FighterMonster = dynamic_cast<Monster*>(iter.get_object());

                    if (FighterMonster->level < this->level ) { // case win
                        this->level += FighterMonster->level;
                        lst.erase(iter);
                        break;
                    } else { // case loose
                        FighterMonster->level += this->level;
                        FighterMonster->refresh(); // refresh the winner graphics
                        for (Iterator AuxIter = lst.begin(); AuxIter.valid(); AuxIter.next()) { // find this and erase it
                            if (AuxIter.get_object() == this) {
                                lst.erase(AuxIter);
                                return;
                            }
                        }
                    }
                }
                default:
                    break;
            }
        }
    }
    refresh(); // refresh graphics
}
