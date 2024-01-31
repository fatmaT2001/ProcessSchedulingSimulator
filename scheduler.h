#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/msg.h>
#include <limits.h>
#include <math.h>
#define max 100
//----------------------- schuduler related variavles ---------
int handling_killedsignal_flage=0;
key_t masskey=10;
char  *altype;
int forkedprocessId;
int maxWorkingSecond=0;
int numberOfProcess=0;
float scheduler_start_time=0;
float scheduler_finish_time=0;
float *liatWaited =NULL;
//------------------------output variables --------------------
//int turnaroundTime=0;
float SWTAT=0;
float SWT=0;
float Average_weighted_turnaround_time=0;
float Average_waiting_time=0;
float Standard_deviation=0;
float runingTime=0;
float CPU_utilaziation=0;
float seQma=0;
//-------------------------------------------------------------
struct pcr {
    int process_id;
    int process_runningT;
    int process_arrivingT;
    int process_prority;
    int process_finishtime;
    int remain_time;
    int process_waitingtime;
    int startrunning;
    float turnaroundTime;
    float waitedTrunAroundTIme;
    char *process_state;
};
struct pcr curentRuningProcess={0,0,0,0,0,0,0,0,0,0,"initial"};
struct pcr SJFpcrQueue[100];
void equality_fun(struct pcr *p1,struct pcr *p2){
        p1->process_id=p2->process_id;

        p1->process_arrivingT=p2->process_arrivingT;
        p1->process_runningT=p2->process_runningT;
        p1->process_prority=p2->process_prority;
        p1->process_state=p2->process_state;
        p1->process_finishtime=p2->process_finishtime;
        p1->process_waitingtime=p2->process_waitingtime;
        p1->process_state=p2->process_state;
        p1->remain_time=p2->remain_time;
        p1->startrunning=p2->startrunning;
        p1->turnaroundTime=p2->turnaroundTime;
        p1->waitedTrunAroundTIme=p2->waitedTrunAroundTIme;

}
//----------------------------------------------prority queue for SJF----------------
int jsfsize = -1;
 
// Function to insert a new element
// into priority queue
void enqueue(struct pcr item)
{
    // Increase the size
    jsfsize++;
 
    // Insert the element
    equality_fun(&SJFpcrQueue[jsfsize],&item);
}
 
// Function to check the top element
int peek()
{
    int highestPriority = SJFpcrQueue[0].process_runningT;
    int ind = 0;
 
    // Check for the element with
    // highest priority
    for (int i = 0; i <= jsfsize; i++) {
 
        // If priority is same choose
        // the element with the
        // highest value
        
         if (highestPriority
                 >SJFpcrQueue[i].process_runningT) {
            highestPriority = SJFpcrQueue[i].process_runningT;
            ind = i;
        }
    }
        
    // Return position of the element
    return ind;
}
 
// Function to remove the element with
// the highest priority
void dequeue(struct pcr *item)
{
    // Find the position of the element
    // with highest priority
        int ind = peek();

        equality_fun(item,&SJFpcrQueue[ind]);

    // Shift the element one index before
    // from the position of the element
    // with highest priority is found
    for (int i = ind; i < jsfsize; i++) {
        equality_fun( &SJFpcrQueue[i] ,&SJFpcrQueue[i + 1]);
    }
 
    // Decrease the size of the
    // priority queue by one
    jsfsize--;
}

void display(){
        for (int i=0;i<jsfsize+1;i++){
                printf("from the sculer hola fatma i am data %d and runing number %d \n",SJFpcrQueue[i].process_id,SJFpcrQueue[i].process_runningT);
        }       
}
bool isEmpty(){
    return jsfsize==-1;
}
//---------------------------------------------------------------------------------
//-----------------------------------proroity queue for Hpf-----------------------
struct pcr HPpcrQueue[100];
 
// Pointer to the last index
int hpsize = -1;
 
// Function to insert a new element
// into priority queue
void enqueueHPqueue(struct pcr item)
{
    // Increase the size
    hpsize++;
 
    // Insert the element
    equality_fun(&HPpcrQueue[hpsize],&item);
}
 
// Function to check the top element
int peekHPqueue()
{
    int highestPriority = HPpcrQueue[0].process_prority;
    int ind = 0;
 
    // Check for the element with
    // highest priority
    for (int i = 0; i <= hpsize; i++) {
 
        // If priority is same choose
        // the element with the
        // highest value
        
         if (highestPriority
                 >HPpcrQueue[i].process_prority) {
            highestPriority = HPpcrQueue[i].process_prority;
            ind = i;
        }
    }
        
    // Return position of the element
    return ind;
}
 
// Function to remove the element with
// the highest priority
void dequeueHPqueue(struct pcr *item)
{
    // Find the position of the element
    // with highest priority
        int ind = peekHPqueue();

        equality_fun(item,&HPpcrQueue[ind]);

    // Shift the element one index before
    // from the position of the element
    // with highest priority is found
    for (int i = ind; i < hpsize; i++) {
        equality_fun( &HPpcrQueue[i] ,&HPpcrQueue[i + 1]);
    }
 
    // Decrease the size of the
    // priority queue by one
    hpsize--;
}

void displayHPqueue(){
        for (int i=0;i<hpsize+1;i++){
                printf("from the sculer hola fatma i am data %d and runing number %d \n",HPpcrQueue[i].process_id,HPpcrQueue[i].process_runningT);
        }       
}
bool isEmptyHPqueue(){
    return hpsize==-1;
}
//--------------------------------------------------------------------------------
//--------------------------------------output functions --------------------------

FILE *fptr;
void creaite(){
    fptr=fopen("process.txt","w");
    if(fptr == NULL)
   {
      printf("Error!");   
                   
   }
   else{
    fprintf(fptr, "#At time x process y state arr w total z remain y wait k\n");
   }
   fclose(fptr);
}
void writing_file_process(struct pcr * temp){
    fptr=fopen("process.txt","a");
    if (!strcmp(temp->process_state, "started")||!strcmp(temp->process_state, "stopped")){
            fprintf(fptr,"at time = %d  process with id =%d   %s  at time %d  and waited for %d \n",getClk(),temp->process_id,temp->process_state,getClk(),temp->process_waitingtime);
            }
    else if (!strcmp(temp->process_state, "finished"))
    
        fprintf(fptr,"at time = %d  process with id =%d   %s  at time %d  and waited for %d and the TA time %.2f and the WTA %.2f \n",getClk(),temp->process_id,temp->process_state,getClk(),temp->process_waitingtime,temp->turnaroundTime,temp->waitedTrunAroundTIme);

    
    fclose(fptr);

} 


//////////////////////////////////////////////////////////////////////////////////
//------------------------proceses handling functions ---------------------------
// this fucntion start the chosen process by forking and execv it is file and passing it is ranining time and update it is data 
// input: the input is a char flaq to decide which queue it is going to use depeneding on the user chosen schulder
void startprocess(char flag){
        if (flag =='s')dequeue(&curentRuningProcess);
        else dequeueHPqueue(&curentRuningProcess);
        curentRuningProcess.process_waitingtime=getClk()-curentRuningProcess.process_arrivingT;
        curentRuningProcess.startrunning=getClk();
        curentRuningProcess.process_state="started";
        writing_file_process(&curentRuningProcess);
        forkedprocessId=fork();
        while(forkedprocessId==-1){
            forkedprocessId=fork();
        }
        if (forkedprocessId==0){
            char result[50];
            int num = curentRuningProcess.process_runningT;
            sprintf(result, "%d", num);
            char*argv[]={"process.out",result,NULL};
            execv("process.out",argv);
            printf("error in crwating process \n");
        }
}
// this fucntion used when the schulder decide that there is a more sutaible process then the current runing so it will stop it 
// stoping the process needs multiple steps starting saving it is current data ,adding it agin to the queue, sending a kill siganl to it and ignoring it is child handlier as it is not finished yet  
void stopprocess(){
    //first save the data of the current process into templete process;
    struct pcr temp;
    temp.process_id=curentRuningProcess.process_id;
    temp.process_prority=curentRuningProcess.process_prority;
    temp.process_runningT=curentRuningProcess.process_runningT-(getClk()-curentRuningProcess.startrunning);
    temp.process_finishtime=curentRuningProcess.process_finishtime;
    temp.process_state=curentRuningProcess.process_state;
    temp.process_waitingtime=curentRuningProcess.process_waitingtime;
    temp.process_arrivingT=curentRuningProcess.process_arrivingT;
    temp.turnaroundTime=curentRuningProcess.turnaroundTime;
    temp.waitedTrunAroundTIme=curentRuningProcess.waitedTrunAroundTIme;
    temp.startrunning=curentRuningProcess.startrunning;

    enqueueHPqueue(temp);
    //second out putit in the file 
    temp.process_state="stopped";
    writing_file_process(&temp);
    curentRuningProcess.process_id=0;
    //then killing the process
    handling_killedsignal_flage=1;
    kill(forkedprocessId,SIGKILL);
}
//----------------------------------------------------------------------------------------
//--------------------------------- schulder algorthems ----------------------------------
// first the SJF algorathem it is the most eay one all it do is checking when reciving a signal if there is a curent process or not and if not it will start 
//new one by calling the sart process function
void SJFAlgorathem(){
       if (curentRuningProcess.process_id==0){
        if(isEmpty()!=true){
        startprocess('s');}
}}
//-------------------PHPF algorithms--------------------
// the schond algorithm is Preemptive Highest Priority First  when calling this alogrithem it will have samiler locgic to the SJF except when a new process with better 
// prority then the current runing one arrive so this algorthem stop the current process by challing the process stop fucntion and then run the better prority one 
// so samply it check if there is  not any runing processes and the queue is not empty and it will be the normal case else it will be the highest prority arrving one   
void HPalgorathem(){
// first case checking if there is no running process
    if (curentRuningProcess.process_id==0 && isEmptyHPqueue()!=true){
        handling_killedsignal_flage=0;
        startprocess('h');
    }
    else{
        if (curentRuningProcess.process_prority>HPpcrQueue[peekHPqueue()].process_prority){
            stopprocess();
        }
    }

}
//------------------------------------------------------------------------------------------
//----------------------------- signal handling function -----------------------------------
// first the child handler when a process funish it is runing time it will send a signal to the schudler then he will be resposible for calculating it is data 
// and start a new one 
void child_handler(int signal){
        struct pcr temp;

    if (handling_killedsignal_flage ==1){
        runingTime+=getClk()-curentRuningProcess.startrunning;
         temp.turnaroundTime=getClk()-curentRuningProcess.process_arrivingT;
        if(curentRuningProcess.process_runningT!=0) {temp.waitedTrunAroundTIme=temp.turnaroundTime/curentRuningProcess.process_runningT;
            SWTAT+=temp.waitedTrunAroundTIme;
        }

        HPalgorathem();
        return;
    }
    
    temp.process_id=curentRuningProcess.process_id;
    temp.process_arrivingT=curentRuningProcess.process_arrivingT;
    temp.process_runningT=curentRuningProcess.process_runningT;
    temp.startrunning=curentRuningProcess.startrunning;
    temp.process_finishtime=getClk();

    temp.process_waitingtime=curentRuningProcess.process_waitingtime;
    temp.process_state="finished";

    temp.turnaroundTime=getClk()-curentRuningProcess.process_arrivingT;
    if (curentRuningProcess.process_runningT!=0) {temp.waitedTrunAroundTIme=temp.turnaroundTime/curentRuningProcess.process_runningT;
    SWT+=temp.process_waitingtime;}
        printf("for the procee %d the runing time is %d \n",temp.process_id,temp.process_runningT);

    printf("swt for procsee %d is %f \n",temp.process_id,SWT);
    runingTime+=getClk()-curentRuningProcess.startrunning;
    liatWaited[curentRuningProcess.process_id-1]=temp.waitedTrunAroundTIme;
    SWTAT+=temp.waitedTrunAroundTIme;
    writing_file_process(&temp);
    curentRuningProcess.process_id=0;
    if (!strcmp(altype, "SJF")) SJFAlgorathem();
    else HPalgorathem();
}

//----------------------------
// the peocess generator signal handeler this funcyion handle the new arriving process signal form the process generator 
// by first reading it from the massage queue then adding it to the right data structure according to the runing algorthim
void handling(int signal){
    struct pcr p;
    key_t massId=msgget(masskey, IPC_CREAT | 0666);
    int masgvalue=msgrcv(massId, &p, sizeof(p), 0, !IPC_NOWAIT);
    p.process_finishtime=0;
    p.process_state="arriveded";
    p.process_waitingtime=0;
    numberOfProcess++;
    if (!strcmp(altype, "SJF")) {
            enqueue(p);
            SJFAlgorathem();}
    else{ 
        enqueueHPqueue(p);
        HPalgorathem();
        }
}
//////////////////////////////////////////////////////////////////////////////////////////////
void startclk(){
   int clokpid=fork();
   while(clokpid==-1){
      clokpid=fork();
   }
   if (clokpid==0){
      char*argv[]={"clk.out",NULL};
      execv("clk.out",argv);
   }

}
struct system_info{
   int maxwait;

};
void receving_maxworkingnumber(){
    struct system_info temp1;
    key_t masskeymax=11;
    key_t sysmass1=msgget(masskeymax, IPC_CREAT | 0666);
    int masgvalue=msgrcv(sysmass1, &temp1, sizeof(temp1),0,!IPC_NOWAIT);
    maxWorkingSecond=temp1.maxwait;
}
void calcStatistic(){
    Average_waiting_time=SWT/numberOfProcess;
    Average_weighted_turnaround_time=SWTAT/numberOfProcess;
    float semqmsq=0;
    for (int i=0;i<numberOfProcess;i++){

        float num =(liatWaited[i]-Average_weighted_turnaround_time)*(liatWaited[i]-Average_weighted_turnaround_time);
        semqmsq+=num;
    }
    seQma=sqrtf((float)semqmsq/numberOfProcess);

}

void finishfile(){
    FILE *fptrf;
    calcStatistic();
    fptrf=fopen("processFINIAL.txt","w");
    CPU_utilaziation=100*(runingTime/(scheduler_finish_time-scheduler_start_time));
    fprintf(fptrf,"CPU utilatiazion = %.2f \n",CPU_utilaziation);
    fprintf(fptrf,"average turnaround time = %.2f \n",Average_waiting_time);
    fprintf(fptrf,"average waited turn arround time %.2f \n",Average_weighted_turnaround_time);
    fprintf(fptrf,"the Standererd WTA is %.2f \n ",seQma);
    fclose(fptrf);

}