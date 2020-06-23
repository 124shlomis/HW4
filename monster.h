#ifndef MONSTER_H
#define MONSTER_H

/* includes */
#include "drawable.h"
#include "drawable_list.h"


// Monster Class:
class Monster : public Drawable {
private:
	// The level of the monster
	int level;

	// The velocity of the monster
	int vel;

	// The direction the monster is moving right now
	direction_t current_direction;

	// How much to keep the last direction
	int direction_hold;

	// Direction counter
	int direction_counter;

	// The next bounding box
	struct rect next_bb;

	// The gfx of the monster
	const char* gfx;

public:

	/**
	 * @brief Initiate a level 1 monster in x,y
	 */
	Monster(unsigned short x, unsigned short y, int direction_hold);

	~Monster() override;
	/**
	 * @brief Move the object in the direction
	 */
	void move(direction_t direction) override;

	/**
	 * @brief Draw the object
	 */
	void draw() override;

	/**
	 * @brief Return an ID that is unique to 
	 * the dynamic type of the drawable object.
	 */
	int id() override;

	/**
	 * @brief Is called whenever any refresh is required
	 */
	void refresh() override;

	/**
	 * @brief Do a step in the 'game of life'
	 * @param lst A list of all drawable objects in the world
	 */
	void step(DrawableList& lst) override;

};

#endif 
