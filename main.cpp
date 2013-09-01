#include <iostream>
#include "ctime"
#include "cstdlib"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "IP.h"

using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    IP *ip = new IP();
    delete ip;
    return 0;
}
