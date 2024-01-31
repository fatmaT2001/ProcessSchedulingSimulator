#include "headers.h"
#include "process_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void clearResources(int);
void handeler(int);
int main(int argc, char **argv)
{
    signal(SIGINT, clearResources);
    signal(SIGCHLD,handeler);
    // TODO Initialization
    // 1. Read the input files.
    reading_file(argv[1]);
    // 2. Ask the user for the chosen scheduling algorithm and its parameters, if there are any.
    char type[20];
    printf("chose your alograthem enter 1 for SJF anf 2 for HP \n");
    scanf("%s",type);
    // 3. Initiate and create the scheduler and clock processes.
    printf("FROM PG TYP %s \n",type);
    starting_schulder(type);
    send_systeminfo();
    startclk();
    // 4. Use this function after creating the clock process to initialize clock
    initClk();
    // To get time use this

    int x = getClk();
    while(isEmptypg()!=true){

        struct process_info temp=peekpg();
        if (temp.process_arrivingT==getClk()){

            temp=poppg();

            send_proeces(temp);
            sleep(0.01);
            kill(schulerId,SIGUSR1);
        }
        else{
            sleep(1);
        }
        
    }
    pause();
    destroyClk(true);
}
void handeler(int sign){
    raise(SIGINT);
}
void clearResources(int signum)
{
    printf("destroing the Queue\n");
    msgctl(massId, IPC_RMID, (struct msqid_ds *) 0);
    msgctl(sysmass, IPC_RMID, (struct msqid_ds *) 0);

    //TODO Clears all resources in case of interruption
}
