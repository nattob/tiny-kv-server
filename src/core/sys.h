#pragma once

#include <cerrno>
#include <expected>
#include <system_error>

namespace sys
{
    template <typename T>
    using Result = std::expected<T, std::error_code>;

    template <typename T>
    [[nodiscard]] Result<T> check( T value ) noexcept
    {
        if ( value == -1 )
        {
            return std::unexpected( std::error_code{errno, std::system_category()} );
        }
        return value;
    }
}
