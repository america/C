#ifndef _PF_UNIX_SERVER_H
#define _PF_UNIX_SERVER_H

#include <stdlib.h>

#define MY_ABORT(__COMMENT__) \
    fprintf (stderr, "\n" __FILE__ "(%d) " __COMMENT__ "\n", __LINE__); \
    exit (EXIT_FAILURE);

/* ソケットファイル名 */
#define FILE_SOCK "server-socket"

/* ソケットファイルが残っていたら消す */
int check_sock_file(void);

/* サーバ処理 */
void func(int client_d);

#endif
