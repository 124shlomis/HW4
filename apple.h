//
// Created by shlomi shitrit on 12/06/2020.
//

#ifndef APPLE_H
#define APPLE_H

/* includes */
#include "drawable.h"
#include "ascii_objects.h"
#include "drawable_list.h"

/* class */
class Apple: public Drawable{
public:

    /**
    * @brief Make an Apple with coordinates x,y
    */
    Apple(unsigned short x, unsigned short y);

    /**
    * @brief Destruct an Apple
    */
    ~Apple() override;

    void move(direction_t direction) override;
    void draw() override;
    void refresh() override;
    int id() override ;
    void step(DrawableList& list) override ;


private:
    int ID;
    unsigned short X; // x coordinate
    unsigned short Y; // y coordinate
};



#endif //APPLE_H
