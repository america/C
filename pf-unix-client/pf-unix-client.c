#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "pf-unix-client.h"

/* クライアント処理 */
void func(int client_d){
  char *sendmsg = "people call him virtual fighter.";
  char rcvmsg[BUFSIZ];
  int written;
  int read_num;

  memset(rcvmsg, '\0', BUFSIZ);

  errno = 0;

  if((written = write(client_d, sendmsg, strlen(sendmsg))) != -1){
    fprintf(stdout,"sended msg:\t%s\n",sendmsg);
    errno = 0;
    if((read_num = read(client_d, rcvmsg, BUFSIZ)) != -1){
      fprintf(stdout,"received msg:\t%s\n",rcvmsg);
    }else{
      perror("read failure");
    }
  }else{
    perror("write failure");
  }

}
