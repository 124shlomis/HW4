//
// Created by Shlomi Shitrit on 12/06/2020.
//

/* Includes */

#include "drawable_list.h"

/* Iterator CLASS: */

/* members functions */

// Constructors:
/**
 * @brief Make an iterator from a list node
 */

Iterator::Iterator(Node& n): ptr(&n){
    this->increase_counter();
}


/**
 * @brief Make an iterator points to nullptr
 */
Iterator::Iterator():ptr(nullptr){}

// Cpy C'tor:
/**
 * @brief When cloning iterators, one must update
 * the iterator counter of the node
 */

Iterator::Iterator(const Iterator& other){

    this->ptr = other.ptr;
    this->increase_counter();
}

// D'tor:
/**
 * @brief Updates iterator counter in the node pointed by this
 * @note In case this is the last iterator that
 * points to a node, free the memory of the node
 * (including everything!)
 */
Iterator::~Iterator(){
    this->decrease_counter(); // decrease counter will free memory if the node is invalid and counter=0;
}

// OTHER Functions:
/**
 * @brief Decreases iterator counter in the node pointed by this
 * @note In case this is the last iterator that
 * points to a node, free the memory of the node
 * (including everything!)
 */

void Iterator::decrease_counter(){
    if (this->ptr == nullptr){ // case the node ptr is nullptr
        return;
    }
    this->ptr->iterator_counter--;
    if (this->ptr->iterator_counter > 0){ // case no need to free memory
        return;
    }
    // FREE ALL MEMORY IF NEEDED: counter =0 && and node is invalid.
    if ( (this->ptr->iterator_counter == 0) & (! this->ptr->valid) ){
        delete this->ptr->item;
        this->ptr->item = nullptr; // set item to nullptr
        delete this->ptr;
        this->ptr = nullptr; // set item to nullptr
    }
}


/**
 * @brief Increases the iterator counter
 * of the node pointed by ptr
 */

void Iterator::increase_counter(){
    if (this->ptr == nullptr){
        return;
    }
    this->ptr->iterator_counter++;
}


/**
 * @brief Returns the item pointerd by this
 */

Drawable* Iterator::get_object(){
    if (this->ptr == nullptr ){
        return nullptr;
    }
    return this->ptr->item;
}


/**
 * @brief Make the node pointed by this to be invalid.
 * @note In case this is the last iterator that
 * points to a node, free the memory of the node
 * (including everything!)
 */

void Iterator::invalidate(){
    if (this->ptr == nullptr){
        return;
    }
    this->ptr->valid = false;
}


/**
 * @brief Upon assigning, we must invalidate the iterator.
 * @note We also must update the node iterator counter
 */

Iterator& Iterator::set(const Iterator& other){
    decrease_counter(); // remember - decrease_counter free memory if needed
    this->ptr = other.ptr;
    increase_counter();
    return *this;
}


/**
 * @brief Changes the state of this to point at the next valid node
 * @returns this
 * @note In case there is no next valid node, sets this as invalid
 */

Iterator& Iterator::next(){
    if (this->ptr == nullptr){
        return *this;
    }

    if (this->ptr->next == nullptr){ // case next is null
        decrease_counter();
        this->ptr = nullptr;
        return *this;
    }

    Node* AuxPtr = this->ptr->next;

    while ( !(AuxPtr->valid) ){
        AuxPtr = AuxPtr->next;
        if (AuxPtr == nullptr){
            this->ptr = nullptr;
            return *this;
        }
    }
    // found valid node. update counters and pointer.
    decrease_counter();
    this->ptr = AuxPtr;
    increase_counter();
    return *this;
}



/**
 * @brief Changes the state of this to point at the previous valid node
 * @returns this
 * @note In case there is no previous valid node, sets this as invalid
 */

Iterator& Iterator::prev(){ // in case we got the start of the list and there is no valid nodes
    if (this->ptr == nullptr){
        return *this;
    }

    if (this->ptr->prev == nullptr){ // case next is null
        decrease_counter();
        this->ptr = nullptr;
        return *this;
    }
    Node* AuxPtr = this->ptr->prev;

    while ( !(AuxPtr->valid) ){
        AuxPtr = AuxPtr->prev;
        if (AuxPtr == nullptr){
            this->ptr = nullptr;
            return *this;
        }
    }

    // found valid node. update counters and pointer.
    decrease_counter();
    this->ptr = AuxPtr;
    increase_counter();
    return *this;
}


/**
 * @breif Returns true iff this is valid
 */

bool Iterator::valid() const{
    if (this->ptr == nullptr){
        return false;
    }
    return this->ptr->valid;
}




// DrawableList CLASS:

// Constructor:
DrawableList::DrawableList():head(nullptr), tail(nullptr), size(0){}

// Destructor:
DrawableList::~DrawableList(){
    if ( size == 0 ){ // case of empty list.
        return;
    }

    for (Iterator AuxIter = (this->begin());AuxIter.valid();AuxIter.next()){
        erase((AuxIter));
    }
}


/**
 * @brief Push to list front (before head).
 * @note Do not clone the object!
 */

void DrawableList::push_front(Drawable& item) {
    // allocating memory for the new node:
    Node* NewNode = new Node();

    // settings New Node:
    NewNode->iterator_counter = 0;
    NewNode->prev = nullptr;
    NewNode->next = this->head;
    NewNode->valid = true;
    NewNode->item = &item;
    // Updating list:
    this->size++;
    if (size == 1) {
        this->tail = NewNode;
    } else if (size > 1){
        this->head->prev = NewNode;
    }
    this->head = NewNode;
}


/**
 * @brief Push to list back (after tail).
 * @note Do not clone the object!
 */

void DrawableList::push_back(Drawable& item){
    // allocating memory for the new node:
    Node* NewNode = new Node();

    // settings New Node:
    NewNode->iterator_counter = 0;
    NewNode->prev = this->tail;
    NewNode->next = nullptr;
    NewNode->valid = true;
    NewNode->item = &item;
    // Updating list:
    this->size++;
    if (size == 1) {
        this->head = NewNode;
    } else if (size > 1){
        this->tail->next = NewNode;
    }
    this->tail = NewNode;
}


/**
	 * @brief Removes an object pointed by the iterator
	 * @note Must invalidate the iterator.
	 */

void DrawableList::erase(Iterator it){
    if ( it.ptr == nullptr ){ // case that node pointer is nullptr
        return;
    }
    size--;
    it.invalidate();
    // case we erase the only item in the list.
    if (size == 0){
        head = nullptr; // Update to an empty list
        tail = nullptr;
        return; //  list is empty
    }

    // else (size>0) - Update Nodes:
    Node* AuxNode = it.ptr;
    if (AuxNode == head){
        head = AuxNode->next;
        head->prev = nullptr;
    } else if (AuxNode == tail){
        tail = AuxNode->prev;
        tail->next = nullptr;
    } else {
        AuxNode->prev->next = AuxNode->next;
        AuxNode->next->prev = AuxNode->prev;
    }

}


/**
 * @brief Returns the size of this
 */

int DrawableList::get_size() const{
    return this->size;
}


/**
 * @brief Returns an iterator to the beginning of the list
 */

Iterator DrawableList::begin(){

    Iterator AuxIter = Iterator(*head);

    if (AuxIter.ptr == nullptr){ // empty list
        return Iterator();
    }
    if (AuxIter.valid()){
        return AuxIter;
    } else
        return AuxIter.next();
}


/**
 * @brief Returns an iterator to the end of the list
 */

Iterator DrawableList::end(){

    Iterator AuxIter = Iterator(*tail);

    if (AuxIter.ptr == nullptr){ // empty list
        return Iterator(); // return iterator pointing null
    }
    if (AuxIter.valid()){
        return AuxIter;
    } else
        return AuxIter.prev();
}

