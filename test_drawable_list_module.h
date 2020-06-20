//
// Created by shlomi shetrit on 14/06/2020.
//

#ifndef HW4_TEST_DRAWABLE_LIST_MODULE_H
#define HW4_TEST_DRAWABLE_LIST_MODULE_H

#include "drawable.h"

class Letter: public Drawable{
protected:
    char s;
    static const int ID_=1;
public:
    Letter(struct rect bb, char ch);
    ~Letter() override;

    void move(direction_t direction) override;
    void draw() override ;
    void refresh() override ;
    int id() override ;
    void step(DrawableList& lst) override ;
    void print() const ;

};


#endif //HW4_TEST_DRAWABLE_LIST_MODULE_H
