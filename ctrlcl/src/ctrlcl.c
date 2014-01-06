#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig){
    printf("OUCH! - I got signal %d\n", sig);
    (void) signal(SIGINT, SIG_DFL);
    // SIG_DFL で default のハンドラに戻す。
}

int   main(){
    (void) signal(SIGINT, ouch);
    // SIGINT のハンドラを ouch() に設定
    while(1) {
        printf("Hello World!\n");
        sleep(1);
    } 
}
