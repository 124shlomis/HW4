//
// Created by Shlomi Shitrit on 14/06/2020.
//

#include "test_drawable_list_module.h"
#include "mini_gui.h"
#include "drawable_list.h"
#include <iostream>
using namespace std;
Letter::Letter(struct rect bb, char ch) : Drawable(bb) {
    s = ch;
}

Letter::~Letter() = default;

void Letter::move(direction_t direction) {
    switch (direction){
        case 0:
            bounding_box.x--;
            break;
        case 1:
            bounding_box.x++;
            break;
        case 2:
            bounding_box.y++;
            break;
        case 3:
            bounding_box.y--;
            break;
        default:
            break;
    }
}

void Letter::draw() {
    mini_gui_clear_rect(mg,bounding_box);
    mini_gui_print_rect(mg,bounding_box,MONSTER0);
}

void Letter::refresh() {
    bounding_box.x = 2;
}

int Letter::id() {
    return ID_;
}

void Letter::step(DrawableList &lst) {
    for (Iterator it=lst.begin(); it.valid(); it.next() ) {
        if( collide( *(it.get_object()) )) {
            cout<<"collide!"<<endl;
        }
    }
}








