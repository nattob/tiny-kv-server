#include "core/net.h"

#include <netinet/in.h>
#include <sys/socket.h>

namespace net
{
    sys::Result<UniqueFd> make_listener( std::uint16_t port )
    {
        // create a tcp socket
        auto fd = sys::check( ::socket( AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0 ) );
        if ( !fd ) return std::unexpected( fd.error() );

        UniqueFd sock{ *fd };

        // set SO_REUSEADDR to avoid "Address already in use" error on restart
        int yes = 1;
        if ( auto r = sys::check( ::setsockopt( sock.get(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes ) ); !r )
        {
            return std::unexpected( r.error() );
        }

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons( port );
        addr.sin_addr.s_addr = htonl( INADDR_ANY );

        if ( auto r = sys::check( ::bind( sock.get(), reinterpret_cast<const sockaddr*>( &addr ), sizeof addr ) ); !r )
        {
            return std::unexpected( r.error() );
        }

        if ( auto r = sys::check( ::listen( sock.get(), SOMAXCONN ) ); !r )
        {
            return std::unexpected( r.error() );
        }

        return sock;
    }
}