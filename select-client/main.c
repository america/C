#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int sock_fd;
  struct sockaddr_in server_addr;

  if(argc != 4){
    fprintf(stderr,"Usage: %s server_address server_port msg\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* サーバ(接続先)アドレスの初期化 */
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

  errno = 0;
  if(connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
     == -1){
    perror("connect failure");
    goto FINALIZE;
  }

  errno = 0;  
  if(write(sock_fd, argv[3], strlen(argv[3])) == -1){
    perror("write failure");
    goto FINALIZE;
  }

  close(sock_fd);
  exit(EXIT_SUCCESS);

 FINALIZE:
  close(sock_fd);
  exit(EXIT_FAILURE);

}
