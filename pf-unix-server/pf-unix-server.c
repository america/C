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
 
/* サーバ処理 */
void func(int client_d)
{
  char buf[BUFSIZ];
  int read_num, i;

  read_num = 0;
  memset(buf, '\0', BUFSIZ);

  while((read_num = read(client_d, buf, BUFSIZ)) != 0){
    for(i = 0; i < read_num; i++){
      buf[i] = toupper(buf[i]);
    }
    errno = 0;
    if(write(client_d, buf,read_num) == -1){
      perror("write failure");
      exit(EXIT_FAILURE);
    }
  }
}

/* ソケットファイルが残っていたら消す */
int check_sock_file(void){
  struct stat file_stat;

  /* ソケットファイルと同名のファイルがあるか */
  errno = 0;
  if(stat(FILE_SOCK, &file_stat) == -1){
    if(errno == ENOENT){
      return 0;
    }else{
      perror("stat failure");
      return -1;
    }
  }

  /* 同名のファイルがソケットファイルである場合 */
  if(S_ISSOCK(file_stat.st_mode)){
    errno = 0;
    if(unlink(FILE_SOCK) == -1){
      perror("cannot unlink " FILE_SOCK);
      return 0;
    }
  }else{
    fprintf(stderr,"Not Socket File %s exists\n",FILE_SOCK);
    return -1;
  }

  return 0;
}
