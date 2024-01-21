#pragma once

// https://raw.githubusercontent.com/bombela/backward-cpp/master/backward.hpp

#if STACK_TRACE_ENABLED == 1

#if STACK_TRACE_MINIMAL == 1
#undef BACKWARD_HAS_DW
#define BACKWARD_HAS_DW 0
#undef BACKWARD_HAS_DWARF
#define BACKWARD_HAS_DWARF 0
#undef BACKWARD_HAS_BFD
#define BACKWARD_HAS_BFD 0
#endif

#include "backward.hpp"

namespace backward
{
static SignalHandling sh;

} // namespace backward
#endif
