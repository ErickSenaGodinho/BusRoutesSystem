#pragma once
#include "system.hpp"

bool loadListFromFile(std::forward_list<Route> &routes)
{
    std::ifstream file;
    file.open(FILE_NAME, std::fstream::binary);

    if (file.fail())
    {
        file.clear();
        return false;
    }

    while (file.peek() != std::ifstream::traits_type::eof())
    {
        Route route;
        file.read(reinterpret_cast<char *>(&route), sizeof(Route));
        unsigned int stops;
        file >> stops;
        route.getStops() = CircularDoublyLinkedList();
        for (unsigned int i = 0; i < stops; i++)
        {
            Stop stop;
            file.read(reinterpret_cast<char *>(&stop), sizeof(Stop));
            route.getStops().push_back(stop);
        }
        routes.push_front(route);
    }
    file.clear();
    return true;
}

void createFile()
{
    std::ofstream file;
    file.open(FILE_NAME, std::ofstream::trunc | std::fstream::binary);
    file.close();
}

void menu()
{
    std::cout << "##########################################################" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                       BUS ROUTES                       #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "##########################################################" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                  1 - Search Bus Routes                 #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                  2 - Maintenance                       #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                  3 - Exit                              #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "##########################################################" << std::endl;
}

void searchBusRoute(std::forward_list<Route> &routes)
{
    system("cls");
    if (routes.empty())
    {
        std::cout << "There are no registered lines." << std::endl;
        std::cout << "Please, access the 'Maintenance' menu to add new lines." << std::endl;
        system("pause");
        return;
    }

    unsigned int option;
    do
    {
        std::cout << "##########################################################" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                   Search Bus Route                     #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "##########################################################" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  1 - Search By City                    #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  2 - Search By Code                    #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  3 - Back                              #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "##########################################################" << std::endl;
        std::cin >> option;
        std::cin.ignore();
        switch (option)
        {
        case 1:
            searchBusRouteByCity(routes);
            break;

        case 2:
            searchBusRouteByCode(routes);
            break;
        }
        system("cls");
    } while (option != 3);
}

void searchBusRouteByCity(std::forward_list<Route> &routes)
{
    system("cls");
    std::cout << "##########################################################" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                     Search By City                     #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "##########################################################" << std::endl;
    std::cout << "Enter the name of the city of origin: ";
    std::string city_of_origin, destination_city;
    getline(std::cin, city_of_origin);

    std::cout << "Enter the name of the destination city: ";
    getline(std::cin, destination_city);

    std::forward_list<Route> found_routes;
    for (auto &route : routes)
    {
        if (!route.getStops().empty())
        {
            Element *temp = route.getStops().getStart();
            do
            {
                if (temp->item.getName().compare(destination_city) == 0 && temp != route.getStops().getStart())
                {
                    found_routes.push_front(route);
                    break;
                }
                temp = temp->next;
            } while (temp != route.getStops().getStart());
        }
    }

    struct route_informations
    {
        std::string code;
        float ticket_price = 0;
        Stop origin;
        Stop destination;
    };

    std::vector<route_informations> list_informations;

    for (auto &route : found_routes)
    {
        Element *temp = route.getStops().getLast();
        bool found_destination_city = false;
        route_informations informations;
        do
        {
            if (temp->item.getName().compare(destination_city) == 0)
            {
                informations.destination = temp->item;
                found_destination_city = true;
            }
            else if (temp->item.getName().compare(city_of_origin) == 0)
            {
                if (found_destination_city)
                {
                    informations.code = route.getCode();
                    informations.origin = temp->item;
                    informations.ticket_price += temp->item.getTicketPrice();
                    list_informations.push_back(informations);
                }
                break;
            }
            else if (found_destination_city)
            {
                informations.ticket_price += temp->item.getTicketPrice();
            }
            temp = temp->prev;
        } while (temp != route.getStops().getLast());
    }

    if (list_informations.empty())
    {
        std::cout << "No route found." << std::endl;
        Sleep(2000);
    }
    else
    {
        std::cout << "\n";
        for (auto &informations : list_informations)
        {
            std::cout << "Route: " << informations.code << std::endl;
            std::cout << "Departure: " << std::put_time(informations.origin.getDepartureTime(), "%H:%M") << ", " << informations.origin.getName() << std::endl;
            std::cout << "Arrival: " << std::put_time(informations.destination.getArrivalTime(), "%H:%M") << ", " << informations.destination.getName() << std::endl;
            std::cout << "Ticket Price: R$ " << informations.ticket_price << std::endl;
            std::cout << "\n";
        }
        system("pause");
    }
}

void searchBusRouteByCode(std::forward_list<Route> &routes)
{
    system("cls");
    std::cout << "##########################################################" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                     Search By Code                     #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "##########################################################" << std::endl;
    std::cout << "Enter the code of route: ";
    std::string code;
    getline(std::cin, code);
    Route *found_route = findRouteByCode(routes, code);
    if (found_route == NULL)
    {
        std::cout << "No route was found with that code." << std::endl;
        Sleep(2000);
    }
    else
    {
        std::cout << "Code: " << found_route->getCode() << std::endl;
        std::cout << "Company: " << found_route->getCompany() << std::endl;
        found_route->getStops().show_stops();
        system("pause");
    }
}

void programMaintenance(std::forward_list<Route> &routes)
{
    system("cls");
    std::string password;
    std::cout << "Password: ";
    getline(std::cin, password);
    if (!isPasswordValid(password))
    {
        std::cout << "Invalid Password!" << std::endl;
        Sleep(2000);
        return;
    }

    system("cls");
    unsigned int option;
    do
    {
        std::cout << "##########################################################" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  Program Maintenance                   #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "##########################################################" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  1 - Add New Route                     #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  2 - Add New Stop                      #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  3 - Update Stop                       #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  4 - Delete Stop                       #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  5 - Delete Route                      #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "#                  6 - Back                              #" << std::endl;
        std::cout << "#                                                        #" << std::endl;
        std::cout << "##########################################################" << std::endl;
        std::cin >> option;
        std::cin.ignore();
        switch (option)
        {
        case 1:
            addRoute(routes);
            break;

        case 2:
            addStop(routes);
            break;

        case 3:
            updateStop(routes);
            break;

        case 4:
            deleteStop(routes);
            break;

        case 5:
            deleteRoute(routes);
            break;
        }
        saveListToFile(routes);
        system("cls");
    } while (option != 6);
}

bool isPasswordValid(std::string password)
{
    return password.compare(PASSWORD) == 0;
}

void addRoute(std::forward_list<Route> &routes)
{
    system("cls");
    std::cout << "##########################################################" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                      Add New Route                     #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "##########################################################" << std::endl;
    std::cout << "Code of new route (-1 to cancel): ";
    std::string code;
    getline(std::cin, code);
    if (code.compare("-1") != 0)
    {
        if (findRouteByCode(routes, code) == NULL)
        {
            Route new_route;
            new_route.setCode(code);
            std::string company;
            std::cout << "Company's name: ";
            getline(std::cin, company);
            new_route.setCompany(company);
            std::cout << "Enter at least 2 stops (Origin and Destination):" << std::endl;
            unsigned int stops_ammount = 0;
            unsigned int option;
            do
            {
                Stop new_stops;
                createStop(new_stops);
                new_route.getStops().push_back(new_stops);
                stops_ammount++;
                if (stops_ammount >= 2)
                {
                    do
                    {
                        std::cout << "Do you want to add another stop?" << std::endl;
                        std::cout << "1-Yes" << std::endl;
                        std::cout << "2-No" << std::endl;
                        std::cin >> option;
                        std::cin.ignore();
                        system("cls");
                    } while (option > 2);
                }
                system("cls");
            } while (stops_ammount < 2 || option == 1);

            std::cout << "Route created successfully." << std::endl;
            routes.push_front(new_route);
            Sleep(1000);
        }
        else
        {
            std::cout << "Route already registered, check and try again." << std::endl;
            Sleep(2000);
        }
    }
}

Route *findRouteByCode(std::forward_list<Route> &routes, std::string code)
{
    for (auto &route : routes)
    {
        if (route.getCode().compare(code) == 0)
        {
            return &route;
        }
    }
    return NULL;
}

void createStop(Stop &stop)
{
    std::string name;
    float ticket_price;

    std::cout << "Stop name: ";
    getline(std::cin, name);
    std::cout << "Arrival Time (ex: 15:00): ";
    std::cin >> std::get_time(stop.getArrivalTime(), "%H:%M");
    std::cout << "Departure Time (ex: 15:15): ";
    std::cin >> std::get_time(stop.getDepartureTime(), "%H:%M");
    std::cout << "Ticket Price: R$ ";
    std::cin >> ticket_price;
    std::cin.ignore();

    stop.setName(name);
    stop.setTicketPrice(ticket_price);
}

void addStop(std::forward_list<Route> &routes)
{
    system("cls");
    std::cout << "##########################################################" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                       Add New Stop                     #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "##########################################################" << std::endl;
    std::cout << "Code of new route (-1 to cancel): ";
    std::string code;
    getline(std::cin, code);
    if (code.compare("-1") != 0)
    {

        Route *found_route = findRouteByCode(routes, code);
        if (found_route == NULL)
        {
            std::cout << "No route was found with that code." << std::endl;
            Sleep(2000);
        }
        else
        {
            found_route->getStops().show_stops();
            std::cout << "Choose the id of the stop you want to insert after: ";
            unsigned int id;
            std::cin >> id;
            std::cin.ignore();
            if (found_route->getStops().is_id_valid(id))
            {
                Stop new_stops;
                createStop(new_stops);
                bool added = found_route->getStops().push_after(id, new_stops);
                if (added)
                {
                    std::cout << "Successfully added stop." << std::endl;
                }
                else
                {
                    std::cout << "Could not add stop." << std::endl;
                }
                Sleep(1000);
            }
            else
            {
                std::cout << "Non-existent id" << std::endl;
                Sleep(2000);
            }
        }
    }
}

void updateStop(std::forward_list<Route> &routes)
{
    system("cls");
    std::cout << "##########################################################" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                       Update Stop                      #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "##########################################################" << std::endl;
    std::cout << "Code of new route (-1 to cancel): ";
    std::string code;
    getline(std::cin, code);
    if (code.compare("-1") != 0)
    {

        Route *found_route = findRouteByCode(routes, code);
        if (found_route == NULL)
        {
            std::cout << "No route was found with that code." << std::endl;
            Sleep(2000);
        }
        else
        {
            std::cout << "Choose the id of the stop you want to update: " << std::endl;
            found_route->getStops().show_stops();
            unsigned int id;
            std::cin >> id;
            std::cin.ignore();
            Stop *found_stops = found_route->getStops().find_stop(id);
            if (found_stops == NULL)
            {
                std::cout << "No stop with that id found." << std::endl;
                Sleep(2000);
            }
            else
            {
                createStop(*found_stops);
                std::cout << "Stop Updated Successfully!" << std::endl;
                Sleep(1000);
            }
        }
    }
}

void deleteStop(std::forward_list<Route> &routes)
{
    system("cls");
    std::cout << "##########################################################" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                      Delete Stop                       #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "##########################################################" << std::endl;
    std::cout << "Code of new route (-1 to cancel): ";
    std::string code;
    getline(std::cin, code);
    if (code.compare("-1") != 0)
    {
        Route *found_route = findRouteByCode(routes, code);
        if (found_route == NULL)
        {
            std::cout << "No route was found with that code." << std::endl;
            Sleep(2000);
        }
        else
        {
            if (found_route->getStops().size() == 2)
            {
                std::cout << "It is not possible to have a route with less than two (2) stops." << std::endl;
                Sleep(2000);
            }
            else
            {
                std::cout << "Choose the id of the stop you want to delete: " << std::endl;
                found_route->getStops().show_stops();
                unsigned int id;
                std::cin >> id;
                std::cin.ignore();
                Stop *found_stops = found_route->getStops().find_stop(id);
                if (found_stops == NULL)
                {
                    std::cout << "No stop with that id found." << std::endl;
                    Sleep(2000);
                }
                else
                {
                    found_route->getStops().pop_stop_by_id(found_stops->getId());
                    std::cout << "Stop Removed Successfully!" << std::endl;
                    Sleep(1000);
                }
            }
        }
    }
}

void deleteRoute(std::forward_list<Route> &routes)
{
    system("cls");
    std::cout << "##########################################################" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "#                      Delete Route                      #" << std::endl;
    std::cout << "#                                                        #" << std::endl;
    std::cout << "##########################################################" << std::endl;
    std::cout << "Code of new route (-1 to cancel): ";
    std::string code;
    getline(std::cin, code);
    if (code.compare("-1") != 0)
    {
        Route *found_route = findRouteByCode(routes, code);
        if (found_route == NULL)
        {
            std::cout << "No route was found with that code." << std::endl;
            Sleep(2000);
        }
        else
        {
            routes.remove(*found_route);
            std::cout << "Route Removed Successfully!" << std::endl;
            Sleep(1000);
        }
    }
}

bool saveListToFile(std::forward_list<Route> &routes)
{
    std::ofstream file;
    file.open(FILE_NAME, std::ofstream::trunc | std::fstream::binary);

    if (file.fail())
    {
        file.clear();
        return false;
    }

    for (auto &route : routes)
    {
        file.write(reinterpret_cast<char *>(&route), sizeof(Route));
        file << route.getStops().size();

        for (unsigned int i = 0; i < route.getStops().size(); i++)
        {
            Stop stop = *route.getStops().find_stop(i + 1);
            file.write(reinterpret_cast<char *>(&stop), sizeof(Stop));
        }
    }
    return true;
}
