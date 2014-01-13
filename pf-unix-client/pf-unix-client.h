#ifndef _PF_UNIX_CLIENT_H
#define _PF_UNIX_CLIENT_H

#include <stdlib.h>

#define MY_ABORT(__COMMENT__) \
      fprintf (stderr, "\n" __FILE__ "(%d) " __COMMENT__ "\n", __LINE__); \
      exit (EXIT_FAILURE);

/* ソケットファイル名 */
#define FILE_SOCK "../pf-unix-server/server-socket"

/* クライアント処理 */
void func(int client_d);

#endif
