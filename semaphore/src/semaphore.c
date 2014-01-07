#include <unistd.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define REPEAT_TIME 10

void sync_print(int semaphore,char symbol);
void del_semaphore(int semaphore);

int semaphore;

/* man semctlよりコピー */
union semun {
  int val;                  /* SETVAL の値 */
  struct semid_ds *buf;     /* IPC_STAT, IPC_SET 用のバッファ */
  unsigned short *array;    /* GETALL, SETALL 用の配列 */
  /* Linux 特有の部分: */
  struct seminfo *__buf;    /* IPC_INFO 用のバッファ */
};

int main(void)
{
  int pid,i;
  char symbol;
  time_t seed;
  time_t int_time;

  /* 乱数の種 */
  if((seed = time(NULL)) == -1){
    perror("time failure");
    exit(EXIT_FAILURE);
  }else{
    srand(seed);
  }

  /* セマフォの作成 */
#ifdef SYNC
  errno = 0;
  semaphore = semget((key_t)1111, 1, 0666|IPC_CREAT);
  if(semaphore == -1){
    perror("semget failure");
    exit(EXIT_FAILURE);
  }

  /* セマフォの初期化 */
  {
    union semun semunion;
    
    errno = 0;
    semunion.val = 1;
    if(semctl(semaphore, 0, SETVAL, semunion) == -1){
      perror("semctl(init) failure");
      exit(EXIT_FAILURE);
    }
  }
#else
  /* セマフォ気分 */
  semaphore = 1;
#endif

  errno = 0;
  pid = fork();
  switch(pid){
  case 0:
    /* 子 */
    symbol = 'c';
    for(i = 0; i < REPEAT_TIME; i++){
      sync_print(semaphore,symbol);
      int_time = rand() % 5;
      sleep(int_time);
    }
    break;
  case -1:
    perror("fork failure");
    exit(EXIT_FAILURE);
    break;
  default:
    /* 親 */
    symbol = 'p';
    for(i = 0; i < REPEAT_TIME; i++){
      sync_print(semaphore,symbol);
      int_time = rand() % 5;
      sleep(int_time);
    }
    wait();
    /* セマフォの削除 */
#ifdef SYNC
    del_semaphore(semaphore);
#endif
    break;
  }

  exit(EXIT_SUCCESS);
}

/* 親と子で同期をとって出力 */
void sync_print(int semaphore, char symbol)
{
  struct sembuf semb;
  semb.sem_num = 0;
  semb.sem_op = -1;
  semb.sem_flg = SEM_UNDO;

#ifdef SYNC
  /* セマフォの取得(ロック) */
  errno = 0;
  if(semop(semaphore, &semb, 1) == -1){
    perror("semop(wait) failure");
  }
#else
  /* セマフォ気分 */
  while(!semaphore){}
  semaphore = 0;
#endif

  /* クリティカルセクション */
  printf("%c",symbol);
  fflush(stdout);
  sleep(1);
  printf("%c ",symbol);
  fflush(stdout);

#ifdef SYNC
  /* セマフォの開放(アンロック) */
  semb.sem_op = 1;
  if(semop(semaphore, &semb, 1) == -1){
    perror("semop(signal) failure");
  }
#else
  /* セマフォ気分 */
  semaphore = 1;
#endif SYNC

}

/* セマフォの削除 */
void del_semaphore(int semaphore){
  union semun semunion;

  errno = 0;
  if(semctl(semaphore, 0, IPC_RMID, semunion) == -1){
    perror("semctl(del_semaphore) failure");
  }

}
