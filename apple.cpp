/* includes */
#include "apple.h"


/**
 * @brief c'tor
 */
Apple::Apple(unsigned short x, unsigned short y)
	: Drawable({ x, y, 1, 1 }),
	  isEaten(false), isDrawn(false) {}

/**
 * @brief d'tor
 */
// no additional memory allocations in Apple
Apple::~Apple()= default; // clear rect in parent dtor


/**
 * @brief draw an apple if needed
 */
void Apple::draw()
{
	if (!isDrawn && !isEaten) {
		mini_gui_print_rect(mg, bounding_box, APPLE);
		isDrawn = true;
	}
}

/**
 * @brief refresh does'nt need to do something
 */
void Apple::refresh() {}

/**
 * @brief returns apple ID
 */
int Apple::id()
{
	return 'A';
}


/**
 * @brief step does'nt need to do something
 */
void Apple::step(DrawableList& lst) {}

/**
 * @brief move does'nt need to do something
 */
void Apple::move(direction_t direction) {}
