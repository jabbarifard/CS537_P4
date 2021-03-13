#include "types.h"
#include "stat.h"
#include "pstat.h"
#include "user.h"

#include <stddef.h>


void
schedtest(int sliceA, char * sleepA, int sliceB, char * sleepB, int sleepParent)
{

    int pid2, pid3;

    if((pid2 = fork2(sliceA)) == 0){
        char *argv1[] = { "exec", sleepA, NULL };
        exec("loop", argv1);
    }
    
    if((pid3 = fork2(sliceB)) == 0){
        char *argv1[] = { "exec", sleepB, NULL };
        exec("loop", argv1);
    }

    // printf(1, "Slice A: %d\t Slice: %d\n", pid2, getslice(pid2));
    // printf(1, "Slice B: %d\t Slice: %d\n", pid3, getslice(pid3));
    sleep(sleepParent);

    struct pstat * test = malloc(sizeof(struct pstat));
    getpinfo(test);

    wait();
    wait();

    // printf(1,"DUMPING PSTAT\n"); 

    int i;
    
    // for (i = 0; i < NPROC; i++){
        
    //     if(test->inuse[i] == 1){
    //         printf(1,"%d\t PID: %d\t TS: %d\t CT: %d\t ScT: %d\t SlT: %d\t Sw: %d\t \n", 
    //         test->inuse[i], test->pid[i], 
    //         test->timeslice[i], test->compticks[i], 
    //         test->schedticks[i], test->sleepticks[i], test->switches[i]);
    //     }
    // }

    for (i = 0; i < NPROC; i++){
        
        if(test->pid[i] == pid2){
            printf(1, "%d ", test->compticks[i]);
        } 
        if(test->pid[i] == pid3){
            printf(1, "%d\n", test->compticks[i]);
        } 
        
    }
    


    free(test);

}

int main(int argc, char *argv[])
{

  if(argc != 6){
    exit();
  }

  schedtest(atoi(argv[1]),(argv[2]),atoi(argv[3]),(argv[4]),atoi(argv[5]));

  exit();
}
