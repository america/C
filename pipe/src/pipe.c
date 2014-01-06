#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* 子の処理 */
void child(int *pipes);
/* 親の処理 */
void parent(int *pipes);

int main(void)
{
  int pid;
  /* パイプのファイルディスクリプタ
     要素 0 : 読み込み用
     要素 1 : 書き込み用
  */
  int pipes[2];

  /* pipe関数でパイプのファイルディスクリプタを取得 */
  errno = 0;
  if(pipe(pipes)){
    perror("pipe failed");
    exit(EXIT_FAILURE);
  }

  /* fork */
  errno = 0;
  pid = fork();
  switch(pid){
  case 0:
    /* 子プロセス */
    child(pipes);
    break;
  case -1:
    /* fork失敗 */
    perror("fork failed");
    exit(EXIT_FAILURE);
    break;
  default:
    /* 親プロセス */
    parent(pipes);
    break;
  }

  exit(EXIT_SUCCESS);
}

/* 子 */
void child(int *pipes){
  int data_size;
  char buffer[BUFSIZ + 1];

  /* パイプから読む */
  errno = 0;
  while((data_size = read(pipes[0],buffer,BUFSIZ))!=-1 || data_size > 0){
    printf("read : %s\t%d bytes\n",buffer,data_size);
  }
  if(data_size == -1){
    perror("read failed");
  }

}

/* 親 */
void parent(int *pipes){
  int data_size;
  char *msg = "hogefugafoo";

  /* パイプに書く */
  errno = 0;
  data_size = write(pipes[1],msg,strlen(msg));
  printf("write : %s\t%d bytes\n",msg,data_size);

  if(data_size == -1){
    perror("write failed");
  }


}
