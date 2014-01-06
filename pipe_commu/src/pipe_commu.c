#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


/* 親用 */
void parent(int pipes[2]);
/* 子用 */
void child(int pipes[2]);

int main(void)
{
  int pid;
  /* パイプ */
  int pipes[2];

  /* パイプの取得 */
  errno = 0;
  if(pipe(pipes)){
    perror("pipe failed");
  }

  /* fork */
  errno = 0;
  pid = fork();
  switch(pid){
  case 0:
    /* 子 */
    child(pipes);
    break;
  case -1:
    /* 失敗 */
    perror("fork failed");
    exit(EXIT_FAILURE);
    break;
  default:
    /* 親 */
    parent(pipes);
    break;
  }

  exit(EXIT_SUCCESS);

}

/* 親 */
void parent(int pipes[2]){
  char buffer[BUFSIZ + 1];
  int readed;
  int writed;
  char *parent_msg = "This is parent msg";

  /* 子のexec完了を確認 */
  printf("%d\tchecking child boot\n",getpid());
  memset(buffer,'\0',sizeof(buffer));
  errno = 0;
  readed = read(pipes[0],buffer,BUFSIZ);
  if(readed <= 0){
    perror("read failed");
  }else{
    printf("%d\tgot message \"%s\"\n",getpid(),buffer);
    printf("%d\tchecked child boot\n",getpid());
  }

  /* パイプに書き込む */
  printf("%d\twrite msg to child\n",getpid());
  errno = 0;
  writed = write(pipes[1],parent_msg,strlen(parent_msg));
  if(writed <= 0){
    perror("write failed");
  }

  /* 子が死ぬのを待つ */
  wait();
  exit(EXIT_SUCCESS);

}

/* 子 */
void child(int pipes[2]){
  char *params[4];

  params[0] = "child.o";
  params[1] = calloc(BUFSIZ + 1,sizeof(char));
  sprintf(params[1],"%d",pipes[0]);
  params[2] = calloc(BUFSIZ + 1,sizeof(char));
  sprintf(params[2],"%d",pipes[1]);
  params[3] = NULL;

  errno = 0;
  execv("./child.o",params);
  perror("exec failed");
  exit(EXIT_FAILURE);
}
