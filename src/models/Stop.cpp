#pragma once
#include "Stop.hpp"

Stop::Stop() {}

Stop::~Stop() {}

void Stop::setId(unsigned int id)
{
    this->id = id;
}

void Stop::setName(std::string name)
{
    strcpy(this->name, name.c_str());
}

void Stop::setTicketPrice(float ticket_price)
{
    this->ticket_price = ticket_price;
}
