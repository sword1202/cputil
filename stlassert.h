#include <assert.h>

#undef _LIBCPP_ASSERT
#define _LIBCPP_ASSERT(condition, message) assert((condition) && message)