#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static int alarm_fired = 0;

void ding(int sig){
    alarm_fired = 1;
}

int main(){
    int pid;

    printf("alarm application starting\n");

    if((pid = fork()) == 0) { //子プロセスの場合
        sleep(5);
        kill(getppid(), SIGALRM);
        //getppid()は現在のプロセスの親プロセスのPIDを得る
        //即ち親プロセスにSIGALARMを送る。
        exit(0);
    }

    printf("waiting for alarm to go off\n");
    (void) signal(SIGALRM, ding);

    pause();  //シグナルを受け取るまで中止する。
    if (alarm_fired) {
        printf("Ding!\n");
    }

    printf("done\n");
    exit(0);
}
