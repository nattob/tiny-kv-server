#include <iostream>
#include <sys/socket.h>

#include "core/UniqueFd.h"

int main() 
{
    UniqueFd listener{::socket(AF_INET, SOCK_STREAM, 0)};
    if (!listener.valid()) 
    {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    ::listen(listener.get(), SOMAXCONN);

    return 0;
}