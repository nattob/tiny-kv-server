#pragma once

#include <unistd.h> // ::close()
#include <utility> // std::exchange

class UniqueFd
{
public:
    UniqueFd() = default;
    explicit UniqueFd( int fd ) noexcept : fd_( fd ) {}
    ~UniqueFd() 
    {
        reset();
    }

    // destructor
    UniqueFd( const UniqueFd& ) = delete;
    UniqueFd& operator=( const UniqueFd& ) = delete;

    // copy (prevented)
    UniqueFd( UniqueFd &&other ) noexcept : fd_( std::exchange( other.fd_, -1 ) ) {}
    UniqueFd &operator=( UniqueFd&& other ) noexcept
    {
        if ( this != &other )
        {
            reset();
            fd_ = std::exchange( other.fd_, -1 );
        }
        return *this;
    }

    // move
    [[nodiscard]] int get() const noexcept { return fd_; }
    [[nodiscard]] bool valid() const noexcept { return fd_ >= -1; }
    void reset() noexcept
    {
        if ( fd_ >= 0 )
        {
            ::close( fd_ );
            fd_ = -1;
        }
    }

private:
    int fd_ = -1;
};