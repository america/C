#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define MY_ABORT(__COMMENT__) \
      fprintf (stderr, "\n" __FILE__ "(%d) " __COMMENT__ "\n", __LINE__); \
      exit (1);

#define MY_THREAD_ABORT(__COMMENT__) \
      fprintf (stderr, "\n" __FILE__ "(%d) " __COMMENT__ "\n", __LINE__); \
      pthread_exit(NULL);

#define INIT_VALUE_Y (12)
static int x,y;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond =  PTHREAD_COND_INITIALIZER;

void* condCheck(void *arg)
{
  int myerrno = 0;
  if ((myerrno = pthread_mutex_lock(&mut)) != 0)
  {
    fprintf(stderr, "condCheck mutロック失敗 %s\n", strerror(myerrno));
    exit(1);
  }
  // クリティカルセクション START
  fprintf(stdout, "condCheck x = %d / y = %d\n", x, y);
  // 条件が満たされるのを待つ
  if ((myerrno = pthread_cond_wait(&cond, &mut)) != 0)
  {
    fprintf(stderr, "condCheck cond_wait失敗 %s\n", strerror(myerrno));
    exit(1);
  }
  if (x > y)
  {
    fprintf(stdout, "### condCheck x > y !!\n");
  }
  else
  {
    fprintf(stderr, "ありえないルート x(%d) <= y(%d)\n", x, y);
  }
  // クリティカルセクション END
  if ((myerrno = pthread_mutex_unlock(&mut)) != 0)
  {
    fprintf(stderr, "condCheck mutアンロック失敗 %s\n", strerror(myerrno));
    exit(1);
  }
  pthread_exit(NULL);
}

void* condChange(void *arg)
{
  int myerrno = 0;
  int i = 0;
  sleep(5);
  for (i = 0; i < 10; i++)
  {
    if ((myerrno = pthread_mutex_lock(&mut)) != 0)
    {
      fprintf(stderr, "condChange mutロック失敗 %s\n", strerror(myerrno));
      exit(1);
    }
    // クリティカルセクション START
    x++;
    y--;
    fprintf(stdout, "condChange x = %d / y = %d\n", x, y);
    // 条件が満たされていれば通知
    if (x > y)
    {
      if((myerrno = pthread_cond_signal(&cond)) != 0)
      {
        fprintf(stderr, "condChange cond_signal失敗 %s\n", strerror(myerrno));
        exit(1);
      }
    }
    // クリティカルセクション END
    if ((myerrno = pthread_mutex_unlock(&mut)) != 0)
    {
      fprintf(stderr, "condChange mutアンロック失敗 %s\n", strerror(myerrno));
      exit(1);
    }
    sleep(1);
  }
  pthread_exit(NULL);
}

int main(void)
{
  x = 0;
  y = INIT_VALUE_Y;

  pthread_t threadCheck;
  pthread_t threadChange;
  if ((errno = pthread_create(&threadCheck, NULL, condCheck, NULL))
      != 0)
  {
    MY_ABORT("threadCheck作成失敗");
  }

  if ((errno = pthread_create(&threadChange, NULL, condChange, NULL))
      != 0)
  {
    MY_ABORT("threadCheck作成失敗");
  }

  void *threadReturn;
  if ((errno = pthread_join(threadChange, &threadReturn)) != 0)
  {
    MY_ABORT("threadChange join失敗");
  }

  if ((errno = pthread_join(threadCheck, &threadReturn)) != 0)
  {
    MY_ABORT("threadChange join失敗");
  }

  return 0;
}
