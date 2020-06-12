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

    // ELSE - FREE ALL MEMORY
    // NEED TO BE DONE
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
    return this->ptr->item;
}


/**
 * @brief Make the node pointed by this to be invalid.
 * @note In case this is the last iterator that
 * points to a node, free the memory of the node
 * (including everything!)
 */
void Iterator::invalidate(){
    this->ptr->valid = false;
    if (this->ptr->iterator_counter == 0){
        // Free all memory
    }
}


/**
 * @brief Upon assigning, we must invalidate the iterator.
 * @note We also must update the node interator counter
 */
Iterator& Iterator::set(const Iterator& other){

}

