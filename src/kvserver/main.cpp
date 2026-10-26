#include <print>

#include "core/net.h"

int main() 
{
    auto listener = net::make_listener( 6380 );

    if ( !listener )
    {
        std::println( stderr, "failed to listen: {}", listener.error().message() );
        return 1;
    }

    return 0;
}