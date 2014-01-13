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

int service(int sock_fd, struct sockaddr_in *server_addr, fd_set read_set)
{
  int connected_fd;
  char read_buf[BUFSIZ];
  int addr_len = sizeof(struct sockaddr_in);
  struct timeval timeout;

  /* タイムアウトの設定 */
  timeout.tv_sec = TIMEOUT;
  timeout.tv_usec = UTIMEOUT;

  errno = 0;
  if(select(FD_SETSIZE, &read_set, (fd_set *)NULL, (fd_set *)NULL, &timeout) == -1){
    perror("select failure");
    return -1;
  }

  /* ファイルディスクリプタの判別 */
  if(FD_ISSET(0, &read_set)){
    connected_fd = 0;
  }else if(FD_ISSET(sock_fd, &read_set)){
    errno = 0;
    if((connected_fd =
	accept(sock_fd, (struct sockaddr *)server_addr, &addr_len)) == -1){
      perror("accept failure");
      return -1;
    }
  }else{
    fprintf(stderr, "\nTIMEOUT\n");
    return 0;
  }

  /* 読み込み */
  memset(read_buf, '\0', BUFSIZ);
  errno = 0;
  if(read(connected_fd, read_buf, BUFSIZ) == -1){
    perror("read failure");
    return -1;
  }

  /* 書き出し */
  errno = 0;
  if(write(1, read_buf, BUFSIZ) == -1){
    perror("write failure");
    return -1;
  }

  /* 終了判定 */
  if(strcmp(read_buf, "exit") == 0 ||
     strcmp(read_buf, "exit\n") == 0){
    return 1;
  }

  return 0;
}
