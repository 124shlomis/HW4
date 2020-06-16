//
// Created by Shlomi Shitrit on 12/06/2020.
//

/* Includes */

#include "drawable_list.h"

/* Iterator CLASS: */
// members functions //

// Constructors:
/**
 * @brief Make an iterator from a list node
 */

Iterator::Iterator(Node& n): ptr(&n){
    this->increase_counter();
}

// Cpy C'tor:
/**
 * @brief When cloning iterators, one must update
 * the iterator counter of the node
 */

Iterator::Iterator(const Iterator& other){

    this->ptr = other.ptr;
    if (&other != this){ // if trying to construct with the same iterator
        this->increase_counter();
    }
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
    if (this->ptr == nullptr){
        return;
    }
    this->ptr->iterator_counter--; // case no need to free memory
    if (this->ptr->iterator_counter > 0){
        return;
    }
    // FREE ALL MEMORY IF NEEDED: counter =0 && and node is invalid.
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
    /*if (ptr->iterator_counter == 0 ){ // free the node memory if needed
        delete ptr->item;
        delete ptr;

    }*/
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
    struct Node* AuxPtr = this->ptr->next;
    while ( (AuxPtr != nullptr) && (! AuxPtr->valid) ){ // in case we got the end of the list and there is no valid nodes
        AuxPtr = AuxPtr->next;
    }
    if (AuxPtr == nullptr){ // end of the list. no valid node found. the node become invalid.
        invalidate();
        return *this;
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
    struct Node* AuxPtr = this->ptr;
    AuxPtr = AuxPtr->prev;
    while ( (AuxPtr != nullptr) && (! AuxPtr->valid) ){
        AuxPtr = AuxPtr->prev;
    }
    if (AuxPtr == nullptr){ // start of the list. no valid node found. the node become invalid.
        invalidate();
        return *this;
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
    if ( (head == nullptr) && (size == 0) ){ // case of empty list.
        return;
    }
    Node* PrevAuxNode;
    Node* AuxNode = head;

    if ( (AuxNode->next == nullptr) && (size == 1) ){ // case of only 1 item in the list.
        delete AuxNode->item;
        delete AuxNode;
        return;
    }
    while ( (AuxNode != nullptr) ){ // case size > 1
        PrevAuxNode = AuxNode;
        AuxNode = AuxNode->next;
        delete PrevAuxNode->item;
        delete PrevAuxNode;
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

void DrawableList::erase(Iterator& it){
    if ( it.ptr == nullptr ){ // case that node pointer is nullptr
        return;
    }
    if ( it.ptr->valid){
        it.invalidate();
    }
    if (size == 1){ // case we erase the only item in the list.
        size--;
        it.invalidate();
        head = nullptr;
        tail = nullptr;
        if (it.ptr->iterator_counter == 0){ // if there is no iterators on it.
            delete it.ptr->item;
            delete it.ptr;
        }
        return; // return empty list
    }
    // Update Nodes:
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
    size--;
    it.invalidate();
    if (it.ptr->iterator_counter == 0){
        delete it.ptr->item;
        delete it.ptr;
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

    Iterator NewIterator = Iterator(*head);
    return NewIterator;
}


/**
 * @brief Returns an iterator to the end of the list
 */

Iterator DrawableList::end(){
    Iterator NewIterator = Iterator(*tail);
    return NewIterator;
}

