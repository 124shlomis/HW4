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

void Letter::print() const {
    cout << "Iterator Character is: " << s << endl;
}





// test DrawableList
/*struct rect a = {0,1,1,0};
auto* A = new Letter(a, 'A');
auto* B = new Letter({1,1,1,1}, 'B');
auto* C = new Letter({0,0,0,0},'C');
auto* D = new Letter({1,1,1,1},'D');
DrawableList ListOfLetters = DrawableList();
ListOfLetters.push_back(*B); //list: {B}
Iterator Iter1 = ListOfLetters.begin(); // Iter1 = B
ListOfLetters.push_back(*C);//list: {B,C}
Iterator Iter2 = ListOfLetters.end();  // Iter2 = C
ListOfLetters.push_front(*A); // list: {A,B,C}
ListOfLetters.push_back(*D); // list: {A,B,C,D}
cout << "There is: " << ListOfLetters.get_size() << " letters in the list" << endl;*/
/* test the following methods:
 * erase, begin, end *//*
Iterator Iter3 = ListOfLetters.begin(); // Iter3 = A
Iterator Iter4 = ListOfLetters.begin(); // Iter4 = A
Iterator Iter5 = ListOfLetters.end(); // Iter5 = D
Iterator Iter6 = ListOfLetters.end(); // Iter6 = D
//ListOfLetters.erase(Iter1);
//ListOfLetters.erase(Iter1);
ListOfLetters.erase(Iter2); // list: {A,B,D}
ListOfLetters.erase(Iter3); // list: {B,D}
ListOfLetters.erase(Iter4); // list: {B,D}
ListOfLetters.erase(Iter4); // list: {B,D}
cout << "There is: " << ListOfLetters.get_size() << " letters in the list" << endl;
ListOfLetters.erase(Iter5); // list: {B}
cout << "There is: " << ListOfLetters.get_size() << " letters in the list" << endl;
*/

