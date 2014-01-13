#ifndef _PF_INET_SERVER_H
#define _PF_INET_SERVER_H

#include <stdlib.h>

#define MY_ABORT(__COMMENT__) \
    fprintf (stderr, "\n" __FILE__ "(%d) " __COMMENT__ "\n", __LINE__); \
    exit (EXIT_FAILURE);

#endif
