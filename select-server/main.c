#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "main.h"

int main(int argc, char *argv[])
{
  int sock_fd;
  struct sockaddr_in server_addr;
  fd_set read_set;

  if(argc != 3){
    fprintf(stderr,"Usage: %s server_address server_port\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* サーバアドレスの初期化 */
  server_addr.sin_family = PF_INET;
  if(inet_aton(argv[1], &(server_addr).sin_addr) == 0){
    fprintf(stderr, "Invalid address \"%s\"\n",argv[1]);
    exit(EXIT_FAILURE);
  }
  server_addr.sin_port = htons(atoi(argv[2]));

  /* ソケットの作成 */
  errno = 0;
  if((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
    perror("socket failure");
    exit(EXIT_FAILURE);
  }

  /* bind */
  errno = 0;
  if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1){
    perror("bind failure");
    goto FINALIZE;
  }

  /* liseten */
  errno = 0;
  if(listen(sock_fd, 5) == -1){
    perror("listen failure");
    goto FINALIZE;
  }

  /* ファイルディスクリプタ集合の設定初期化 */
  FD_ZERO(&read_set);
  FD_SET(0, &read_set);
  FD_SET(sock_fd, &read_set);

  /* selectとaccept */
  while(1){
    int result;
    if((result = service(sock_fd, &server_addr, read_set)) == -1){
      goto FINALIZE;
    }else if(result == 1){
      break;
    }
  }

  close(sock_fd);

  exit(EXIT_SUCCESS);

 FINALIZE:
  close(sock_fd);
  exit(EXIT_FAILURE);

}
