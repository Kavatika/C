#define _POSIX_SOURCE
#include "errorhandler.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void error_handler()
{
 int errno_internal = errno;
 char * err = strerror(errno_internal);
 write(2, err, strlen(err));
 write(2, "\n", 1);
 exit(errno_internal);
}
