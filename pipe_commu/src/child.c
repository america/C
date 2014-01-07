#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

static int signal_catched=0;

void sigcatch(int sig){
  signal_catched=1;
  /* シグナルハンドラをデフォルトに戻す */
  /*signal(sig,SIG_DFL);*/
}

int main(int argc,char *argv[]){
  int pipes[2];
  int readed;
  char read_buf[BUFSIZ + 1];
  char *boot_msg = "I'm booted";

  if(argc != 3){
    fprintf(stderr,"Invalid parameters\n");
    exit(EXIT_FAILURE);
  }

  /* 引数からパイプのファイルディスクリプタを取得 */
  pipes[0] = atoi(argv[1]);
  pipes[1] = atoi(argv[2]);

  /* パイプを介して親に起動を通知 */
  printf("%d\tchild booted\n",getpid());
  errno = 0;
  if(write(pipes[1],boot_msg,strlen(boot_msg)) < 0){
    perror("write failed");
  }
  printf("%d\tsended boot_msg\n",getpid());

  /* Delay */
  (void) signal(SIGINT, sigcatch);

  pause();  // シグナルを受け取るまで中止する
  if(signal_catched){
    printf("%d\tgot signal\n", getpid());
  }

  /* パイプを介して親からメッセージを受け取る */
  printf("%d\tchild read\n",getpid());
  errno = 0;
  memset(read_buf,'\0',sizeof(read_buf));
  readed = read(pipes[0],read_buf,BUFSIZ);
  if(readed <= 0){
    perror("read failed");
  }else{
    printf("%d\tgot message \"%s\"\n",getpid(),read_buf);
  }

  exit(EXIT_SUCCESS);

}
