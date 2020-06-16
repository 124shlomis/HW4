//
// Created by shlomi shitrit on 16/06/2020.
//

/* includes */
#include "apple.h"

// C'tor
Apple::Apple(unsigned short x,unsigned short y): Drawable({x, y,1,1}) {
    ID = 0;
    X = x;
    Y = y;
}

// D'tor
Apple::~Apple() = default;


void Apple::move(direction_t direction) {}


void Apple::draw() {
    mini_gui_print(mg, APPLE);
}

void Apple::refresh() {
    mini_gui_get_screen_size(mg);
    bounding_box.x = X;
    bounding_box.y = Y;
}

int Apple::id() {
    return ID;
}

void Apple::step(DrawableList &list) {
}

