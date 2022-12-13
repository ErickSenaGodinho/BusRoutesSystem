#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include "./CircularDoublyLinkedList.cpp"

class Route
{
private:
    char code[30];
    char company[100];
    CircularDoublyLinkedList stops;

public:
    Route();
    ~Route();

    bool operator==(const Route &rhs) { return strcmp(this->code, rhs.code) == 0; }

    std::string getCode() const { return std::string(this->code); }
    std::string getCompany() const { return std::string(this->company); }
    CircularDoublyLinkedList &getStops() { return this->stops; }

    void setCode(std::string code);
    void setCompany(std::string company);
};
#endif