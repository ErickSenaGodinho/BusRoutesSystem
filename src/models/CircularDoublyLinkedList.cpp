#pragma once
#include "CircularDoublyLinkedList.hpp"

CircularDoublyLinkedList::CircularDoublyLinkedList() : start(NULL), last(NULL), m_size(0) {}

CircularDoublyLinkedList::~CircularDoublyLinkedList() {}

void CircularDoublyLinkedList::push_back(Stop stop)
{
    Element *new_element = new Element;
    new_element->item = stop;
    if (this->start == NULL)
    {
        new_element->item.setId(1);
        this->start = new_element;
        this->last = new_element;
        new_element->next = this->start;
        new_element->prev = this->start;
        this->m_size++;
        return;
    }

    new_element->next = this->start;
    new_element->prev = this->last;
    new_element->item.setId(this->last->item.getId() + 1);
    this->start->prev = new_element;
    this->last->next = new_element;
    this->last = new_element;
    this->m_size++;
}

bool CircularDoublyLinkedList::push_after(unsigned int id, Stop stop)
{
    if (!is_id_valid(id))
    {
        return false;
    }

    Element *temp = this->start;
    while (temp->item.getId() != id)
    {
        temp = temp->next;
    }

    Element *new_element = new Element;
    new_element->item = stop;
    new_element->next = temp->next;
    new_element->prev = temp;
    temp->next->prev = new_element;
    temp->next = new_element;
    this->m_size++;
    update_last();
    return true;
}

bool CircularDoublyLinkedList::is_id_valid(unsigned int id)
{
    return id > 0 && id <= size();
}

void CircularDoublyLinkedList::update_last()
{
    Element *temp;
    temp = this->start;
    unsigned int id = 0;
    do
    {
        temp->item.setId(++id);
        temp = temp->next;
    } while (temp != this->start);

    this->last = temp->prev;
}

Stop *CircularDoublyLinkedList::find_stop(unsigned int id)
{
    Element *temp = this->start;
    do
    {
        if (temp->item.getId() == id)
        {
            return &temp->item;
        }
        temp = temp->next;
    } while (temp != this->start);
    return NULL;
}

bool CircularDoublyLinkedList::pop_stop_by_id(unsigned int id)
{
    if (!is_id_valid(id))
    {
        return false;
    }

    Element *temp;
    temp = this->start;
    while (temp->item.getId() != id)
    {
        temp = temp->next;
    }
    if (temp == this->start)
    {
        this->start = temp->next;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    this->m_size--;
    update_last();
    return true;
}

void CircularDoublyLinkedList::show_stops()
{
    if (empty())
    {
        return;
    }
    Element *temp = this->start;
    do
    {
        std::cout << temp->item.getId() << " " << temp->item.getName() << (temp == this->last ? "" : " -> ");
        temp = temp->next;
    } while (temp != this->start);
    std::cout << "\n";
}

unsigned int CircularDoublyLinkedList::size()
{
    return m_size;
}

bool CircularDoublyLinkedList::empty()
{
    return size() == 0;
}
