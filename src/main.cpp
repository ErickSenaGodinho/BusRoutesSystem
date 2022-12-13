#include "system.cpp"

int main(int argc, char const *argv[])
{

    std::forward_list<Route> routes;
    bool fileLoaded = loadListFromFile(routes);
    if (!fileLoaded)
    {
        createFile();
    }
    unsigned int option;
    do
    {
        system("cls");
        menu();
        std::cin >> option;
        std::cin.ignore();

        switch (option)
        {
        case 1:
            searchBusRoute(routes);
            break;

        case 2:
            programMaintenance(routes);
            break;
        }
    } while (option != EXIT_OPTION);

    return 0;
}
