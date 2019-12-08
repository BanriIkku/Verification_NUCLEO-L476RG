#ifndef __PLATFORM_LOGGER_H_
#define __PLATFORM_LOGGER_H_

#include "mbed.h"

static void _Logger_output(const char* value);
static void _Logger_mutex_wait_function(void);
static void _Logger_mutex_release_function(void);

#endif // __PLATFORM_LOGGER_H_
