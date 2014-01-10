

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define MY_ABORT(__COMMENT__) \
      fprintf (stderr, "\n" __FILE__ "(%d) " __COMMENT__ "\n", __LINE__); \
      exit (1);

#define MY_THREAD_ABORT(__COMMENT__) \
      fprintf (stderr, "\n" __FILE__ "(%d) " __COMMENT__ "\n", __LINE__); \
      pthread_exit(NULL);

/*
 * スレッドパラメータ格納用
 */
typedef struct{
  int var1;
  int var2;
  int sum;
  int printFlag;
  pthread_mutex_t printLock;
} SHARED_THREAD_ARG;

/*
 * 表示スレッドイニシャル関数
 */
void *printThread(void *arg)
{
  SHARED_THREAD_ARG *my_thread_arg =(SHARED_THREAD_ARG*)arg;

  struct timespec sleepTime;
  sleepTime.tv_sec = 0;
  sleepTime.tv_nsec = 0.1 * 1000 * 1000;

  while(my_thread_arg->printFlag > 0){
#ifdef SYNC
    if (pthread_mutex_lock(&my_thread_arg->printLock) != 0){
      MY_THREAD_ABORT("faield to mutex lock");
    }
#endif
    printf("%d + %d = %d\n",
             my_thread_arg->var1,
             my_thread_arg->var2,
             my_thread_arg->sum);
#ifdef SYNC
    if (pthread_mutex_unlock(&my_thread_arg->printLock) != 0){
      MY_THREAD_ABORT("failed to mutex unlock");
    }
#else
#endif
    nanosleep(&sleepTime, NULL);
  }

  return 0;
}

/*
 * 計算スレッドイニシャル関数
 */
void *calcurateThread(void *arg)
{
  SHARED_THREAD_ARG *my_thread_arg =(SHARED_THREAD_ARG*)arg;

  struct timespec sleepTime;
  sleepTime.tv_sec = 0;
  sleepTime.tv_nsec = 0.5 * 1000 * 1000;

  int i = 0;

  for (i = 0; i < 3; i++){
#ifdef SYNC
    if (pthread_mutex_lock(&my_thread_arg->printLock) != 0){
      MY_THREAD_ABORT("failed to mutex lock");
    }
#endif
    nanosleep(&sleepTime, NULL);
    my_thread_arg->var1++;
    nanosleep(&sleepTime, NULL);
    my_thread_arg->var2++;
    nanosleep(&sleepTime, NULL);
    my_thread_arg->sum = my_thread_arg->var1
    + my_thread_arg->var2;
#ifdef SYNC
    if(pthread_mutex_unlock(&my_thread_arg->printLock) != 0){
      MY_THREAD_ABORT("failed to mutex lock");
    }
#endif
  }

  my_thread_arg->printFlag = 0;

  return 0;
}


int main(int argc,char *argv[])
{
  int status;
  void *thread_return;

  // スレッドa,b共有パラメータ
  SHARED_THREAD_ARG sharedArg = {0, 0, 0, 1, PTHREAD_MUTEX_INITIALIZER};

  pthread_t thread_a;
  // スレッドaを生成
  status=pthread_create(&thread_a, NULL, printThread, &sharedArg);
  if(status!=0){
    MY_ABORT("failed to create thread_a");
  }

  pthread_t thread_b;
  // スレッドbを生成
  status=pthread_create(&thread_b, NULL, calcurateThread, &sharedArg);
  if(status!=0){
    MY_ABORT("failed to create thread_b");
  }

  // スレッドaが終了するのを待つ.
  status = pthread_join(thread_a, &thread_return);
  if(status != 0){
    MY_ABORT("failed to join thread_a");
  }

  // スレッドbが終了するのを待つ.
  status = pthread_join(thread_b, &thread_return);
  if(status != 0){
    MY_ABORT("failed to join thread_b");
  }
  
  fprintf(stderr, "\n");

  return 0;
}
