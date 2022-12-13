#ifndef STOP_H
#define STOP_H

#include <time.h>
#include <string>

class Stop
{
private:
    unsigned int id;
    char name[100];
    tm arrival_time;
    tm departure_time;
    float ticket_price;

public:
    Stop();
    ~Stop();

    unsigned int getId() const { return id; }
    std::string getName() const { return std::string(name); }
    tm *getArrivalTime() { return &arrival_time; }
    tm *getDepartureTime() { return &departure_time; }
    float getTicketPrice() const { return ticket_price; }

    void setId(unsigned int id);
    void setName(std::string name);
    void setTicketPrice(float ticket_price);
};

#endif