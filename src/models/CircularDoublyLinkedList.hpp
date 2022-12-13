#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <iostream>
#include "Stop.cpp"

typedef struct Element
{
    Stop item;
    Element *next = NULL;
    Element *prev = NULL;
};

class CircularDoublyLinkedList
{
private:
    Element *start;
    Element *last;
    unsigned int m_size;

    void update_last();

public:
    CircularDoublyLinkedList();
    ~CircularDoublyLinkedList();

    Element *getStart() const { return start; }
    Element *getLast() const { return last; }

    void push_back(Stop stop);
    bool push_after(unsigned int id, Stop stop);
    bool is_id_valid(unsigned int id);
    Stop *find_stop(unsigned int id);
    bool pop_stop_by_id(unsigned int id);
    void show_stops();
    unsigned int size();
    bool empty();
};

#endif