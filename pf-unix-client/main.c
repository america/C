#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "pf-unix-client.h"

int main(void)
{
  int client_d; /* クライアントソケット */
  struct sockaddr_un *server_addr; /* サーバのアドレス */

  /* アドレスの初期化 */
  errno = 0;
  server_addr = malloc(sizeof(struct sockaddr_un));
  if(server_addr == NULL){
    MY_ABORT("malloc failure");
  }
  server_addr->sun_family = PF_UNIX;
  strcpy(server_addr->sun_path, FILE_SOCK);

  /* ソケットの作成 */
  errno = 0;
  if((client_d = socket(PF_UNIX, SOCK_STREAM, 0)) == -1){
    MY_ABORT("socket failure");
  }

  /* サーバに接続 */
  if(connect(client_d, (struct sockaddr *)server_addr, sizeof(*server_addr)) == -1){
    MY_ABORT("connect failure");
  }

  /* クライアント処理 */
  func(client_d);

  /* ソケットのclose */
  close(client_d);

  free(server_addr);

  exit(EXIT_SUCCESS);
}
