#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstring>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <windows.h>
#include "./models/Route.cpp"
#include "./models/Stop.cpp"
#include "./models/CircularDoublyLinkedList.cpp"

#define FILE_NAME "./resources/routes.bin"
#define EXIT_OPTION 3
#define PASSWORD "1234"

void menu();

bool loadListFromFile(std::forward_list<Route> &routes);
void createFile();

void searchBusRoute(std::forward_list<Route> &routes);
void searchBusRouteByCity(std::forward_list<Route> &routes);
void searchBusRouteByCode(std::forward_list<Route> &routes);

void programMaintenance(std::forward_list<Route> &routes);
bool isPasswordValid(std::string password);
void addRoute(std::forward_list<Route> &routes);
Route *findRouteByCode(std::forward_list<Route> &routes, std::string code);
void createStop(Stop &stop);
void addStop(std::forward_list<Route> &routes);
void updateStop(std::forward_list<Route> &routes);
void deleteStop(std::forward_list<Route> &routes);
void deleteRoute(std::forward_list<Route> &routes);

bool saveListToFile(std::forward_list<Route> &routes);

#endif