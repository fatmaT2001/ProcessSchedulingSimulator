#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/msg.h>
#define maxpg 100
struct process_info {
    int process_id;
    int process_runningT;
    int process_arrivingT;
    int process_prority;
};

int schulerId=0;
key_t masskey=10;
key_t massId=0;
struct process_info intArray[maxpg];
int front = 0;
int rear = -1;
int itemCount = 0;

struct process_info peekpg() {
   return intArray[front];
}

bool isEmptypg() {
   return itemCount == 0;
}



int sizepg() {
   return itemCount;
}  

void insertpg(struct process_info data) {

 
    

      intArray[++rear] = data;
      itemCount++;
   
}

struct process_info poppg() {
   struct process_info data = intArray[front++];
	itemCount--;
   return data;  
}
void displayprocessgen(){
   for (int i=front;i<rear+1;i++){
      printf("form process generator hola i am the process number %d and runnong time %d\n",intArray[i].process_id,intArray[i].process_runningT);
   }
}
void reading_file(char * filename){
    FILE *in_file;
    int temp=1;
    int listtemp[4];
    in_file = fopen(filename, "r");


    if (in_file == NULL){printf("Can't open file for reading.\n");}
    else
    {
        while((fscanf(in_file,"%d ", &listtemp[temp]))==1){
            if (temp%4==0){
                struct process_info process;
                process.process_id=listtemp[1];
                process.process_arrivingT=listtemp[2];
                process.process_runningT=listtemp[3];
                process.process_prority=listtemp[4];
                insertpg(process);
                temp=0;
            }
            temp+=1;

        } 
        fclose(in_file);
    }



}
struct system_info{
   int maxwait;

};
int totalruningtime(){
   int maxwait=0;
   for (int i=front;i<rear+1;i++){
      maxwait+=intArray[i].process_runningT;
   }
   return maxwait;
}
key_t sysmass=0;
void send_systeminfo(){
   struct system_info temp;
   temp.maxwait=totalruningtime();
   key_t masskeymax=11;
   sysmass=msgget(masskeymax, IPC_CREAT | 0666);
   int send_val = msgsnd(sysmass, &temp, sizeof(temp), !IPC_NOWAIT);

}
 void starting_schulder(char *type){

   schulerId=fork();
   while(schulerId==-1){
      schulerId=fork();
   }
   if(schulerId==0){
      execl("/home/os/Desktop/project/scheduler.out","scheduler.out",type,NULL);
        perror("Error in execv'ing to scheduler");
        exit(EXIT_FAILURE);

   }
   

}

void send_proeces(struct process_info process){
   massId=msgget(masskey, IPC_CREAT | 0666);
   int send_val = msgsnd(massId, &process, sizeof(process), !IPC_NOWAIT);

}
void startclk(){
   int clokpid=fork();
   while(clokpid==-1){
      clokpid=fork();
   }
   if (clokpid==0){
      char*argv[]={"clk.out",NULL};
      execv("clk.out",argv);
      perror("Error in execv'ing to clock");
      exit(EXIT_FAILURE);
   }

}
