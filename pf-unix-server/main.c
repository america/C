#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include "pf-unix-server.h"
 
int main(void)
{
  int server_d;                                  /* ソケットディスクリプタ(サーバ) */
  int client_d;                                  /* ソケットディスクリプタ(クライアント */
  struct sockaddr_un *server_addr;               /* ソケットのアドレス(サーバ) */
  struct sockaddr_un *client_addr;               /* ソケットのアドレス(クライアント) */
  socklen_t client_len = sizeof(*client_addr);   /* ソケットアドレスの長さ(クライアント) */

  if(check_sock_file() == -1){
    exit(EXIT_FAILURE);
  }

  /* アドレスの初期化 */
  errno = 0;
  server_addr = malloc(sizeof(struct sockaddr_un));
  if(server_addr == NULL){
    MY_ABORT("malloc failure");
  }
  server_addr->sun_family = PF_UNIX;
  strcpy(server_addr->sun_path,FILE_SOCK);

  errno = 0;
  client_addr = malloc(sizeof(struct sockaddr_un));
  if(client_addr == NULL){
    MY_ABORT("malloc failure");
  }

  /* ソケットの作成 */
  errno = 0;
  if((server_d = socket(PF_UNIX, SOCK_STREAM, 0)) == -1){
    perror("socket failure");
    check_sock_file();
    exit(EXIT_FAILURE);
  }

  /* ソケットのbind(ソケットに名前をつける) */
  errno = 0;
  if(bind(server_d, (struct sockaddr *)server_addr, sizeof(*server_addr)) == -1){
    perror("bind failure");
    close(server_d);
    check_sock_file();
    exit(EXIT_FAILURE);
  }

  /* listen */
  errno = 0;
  if(listen(server_d, 5) == -1){
    perror("listenn failure");
    close(server_d);
    check_sock_file();
    exit(EXIT_FAILURE);
  }

  /* accept */
  errno = 0;
  client_d = accept(server_d, (struct sockaddr *)client_addr, &client_len);
  if(client_d == -1){
    perror("accept failure");
    close(server_d);
    check_sock_file();
    exit(EXIT_FAILURE);
  }

  /* 処理 */
  func(client_d);

  /* ソケットのclose */
  close(client_d);
  close(server_d);

  if(check_sock_file() == -1){
    exit(EXIT_FAILURE);
  }

  free(server_addr);
  free(client_addr);

  exit(EXIT_SUCCESS);
}
