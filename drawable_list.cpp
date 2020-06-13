//
// Created by Shlomi Shitrit on 12/06/2020.
//
// Includes //

#include "drawable_list.h"

// members functions //

// Constructors:
/**
 * @brief Make an iterator from a list node
 */

Iterator::Iterator(Node& n): ptr(&n){
    this->increase_counter();
}

// COPY CONSTRUCTOR:
/**
 * @brief When cloning iterators, one must update
 * the iterator counter of the node
 */

Iterator::Iterator(const Iterator& other){
    this->ptr = other.ptr;
    this->increase_counter();
}

// Destructor:
/**
 * @brief Updates iterator counter in the node pointed by this
 * @note In case this is the last iterator that
 * points to a node, free the memory of the node
 * (including everything!)
 */
Iterator::~Iterator(){
    this->decrease_counter();
}

/**
 * @brief Decreases iterator counter in the node pointed by this
 * @note In case this is the last iterator that
 * points to a node, free the memory of the node
 * (including everything!)
 */

void Iterator::decrease_counter(){
    if (this->ptr == nullptr){
        return;
    }
    this->ptr->iterator_counter--;
    if (this->ptr->iterator_counter > 0){
        return;
    }
    // FREE ALL MEMORY IF NEEDED:
    if ( (this->ptr->iterator_counter == 0) & (! this->ptr->valid) ){
        delete this->ptr->item;
        delete this->ptr;
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
    if (this->ptr == nullptr){
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
    if (this->ptr->iterator_counter == 0){
        delete this->ptr->item;
        delete this->ptr;
    }
}


/**
 * @brief Upon assigning, we must invalidate the iterator.
 * @note We also must update the node iterator counter
 */

Iterator& Iterator::set(const Iterator& other){
    decrease_counter();
    invalidate();
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
    struct Node* AuxPtr = this->ptr;
    AuxPtr = AuxPtr->next;
    while ( (AuxPtr != nullptr) && (! AuxPtr->valid) ){
        AuxPtr = AuxPtr->next;
    }
    if (AuxPtr == nullptr){
        invalidate();
        return *this;
    }
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

Iterator& Iterator::prev(){
    struct Node* AuxPtr = this->ptr;
    AuxPtr = AuxPtr->prev;
    while ( (AuxPtr != nullptr) && (! AuxPtr->valid) ){
        AuxPtr = AuxPtr->prev;
    }
    if (AuxPtr == nullptr){
        invalidate();
        return *this;
    }
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


