#include <iostream>
#include "ctime"
#include "cstdlib"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "IP.h"

using namespace std;

int main()
{
    if(!sf::Shader::isAvailable()) {
        return EXIT_FAILURE;
    }
    srand((unsigned)time(NULL));
    IP *ip = new IP();
    delete ip;
    ip = 0;
    return 0;
}
