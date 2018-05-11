/*************************************************************************
	> File Name: shan.c
	> Author: zty
	> Mail: 1295303752@qq.com
	> Created Time: Tue 01 May 2018 12:31:05 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

int flag = 0;

void sig_int(int signum)
{
    if(flag == 1)
    fprintf(stderr,"[47;31mhello world[5m");
    fprintf(stderr,"[;[0m");
    fprintf(stderr,"[;[0m");
    printf("");
    exit(0);
}
int main(int argc, char *argv[])
{
    int i=0;
    struct sigaction sig_act;
    sig_act.sa_handler = sig_int;
    sigemptyset(&sig_act.sa_mask);
    sig_act.sa_flags = 0;

    if(sigaction(SIGINT,&sig_act,NULL)<0)
    {
        fprintf(stderr,"signal error");
        exit(1);
    }
    while(i++ < 10)
    {
        fprintf(stderr,"[;[s");
        fprintf(stderr,"47;31mhello world[5m");
        flag = 0;
        sleep(1);
        fprintf(stderr,"[;[u");
        fprintf(stderr,"[;[K");
        flag = 1;
        sleep(1);
    }
    fprintf(stderr,"47;31mhello world[5m");
    fprintf(stderr,"[;[0m");
    printf("");
    return 0;
}
