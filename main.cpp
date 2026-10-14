#include "deliverySystem.h"
#include <iostream>

int main(int argc, char* argv[])
{   
    if (argc==2)
    {
        std::ifstream file(argv[1]);
        DeliverySystem* system = new DeliverySystem();
        system->run(file);
        delete system;
        return 0; 
    }
    else if(argc < 2)
    {
        std::cout << "No order file \n";
    }
    else if(argc > 2)
    {
        std::cout << "Too many arguments \n";
    }
}