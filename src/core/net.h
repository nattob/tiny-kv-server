#pragma once

#include <cstdint>

#include "core/sys.h"
#include "core/UniqueFd.h"

namespace net
{
    [[nodiscard]] sys::Result<UniqueFd> make_listener( std::uint16_t port ) noexcept;
}