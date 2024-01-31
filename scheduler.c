#include "headers.h"
#include "scheduler.h"
int main(int argc, char **argv)
{
    signal(SIGUSR1,handling);
    signal(SIGCHLD,child_handler);
    liatWaited = calloc(numberOfProcess, sizeof(int));

    initClk();
    altype=argv[1];
    scheduler_start_time=getClk();
    //TODO implement the scheduler :)
    //upon termination release the clock resources
    receving_maxworkingnumber();
    //receving_maxworkingnumber2();


    creaite();
    int num=maxWorkingSecond+5;
    while(num>getClk()){
      sleep(num-getClk());
    }
    scheduler_finish_time=getClk();
    finishfile();
    //displayfinished();
    destroyClk(true);
}
