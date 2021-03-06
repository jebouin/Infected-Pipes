#include <iostream>
#include "ctime"
#include "cstdlib"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "IP.h"

int main()
{
    if(!sf::Shader::isAvailable()) {
        return EXIT_FAILURE;
    }
    srand((unsigned)time(NULL));
    IP *ip = new IP();
    delete ip;
    return 0;
}
