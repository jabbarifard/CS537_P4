#include "types.h"
#include "stat.h"
#include "pstat.h"
#include "user.h"

#include <stddef.h>


void
schedtest(int sliceA, char * sleepA, int sliceB, char * sleepB, int sleepParent)
{

    int pid = fork();
    int pid2, pid3;
    if(pid < 0){
        exit();
    } else if (pid == 0) {

        pid2 = fork2(sliceA);
        if(pid2 == 0) {
            char *argv1[] = { "exec", sleepA };
            exec("loop", argv1);
        } 

        wait();

        pid3 = fork2(sliceB);
        if(pid3 == 0) {
            char *argv1[] = { "exec", sleepB };
            exec("loop", argv1);
        } 

        wait();

    } else {        
        sleep(sleepParent);

        struct pstat * test = malloc(sizeof(struct pstat));
        getpinfo(test);

        printf(1,"DUMPING PSTAT\n"); 

   
        int i;
        for (i = 0; i < NPROC; i++){
            
            //if(test->inuse[i] == 0 || test->inuse[i] == 1){
            printf(1,"%d\t PID: %d\t TS: %d\t CT: %d\t ScT: %d\t SlT: %d\t Sw: %d\t \n", 
            test->inuse[i], test->pid[i], 
            test->timeslice[i], test->compticks[i], 
            test->schedticks[i], test->sleepticks[i], test->switches[i]);
            //}
        }

        free(test);
        wait();
        wait();

    }


}

int main(int argc, char *argv[])
{

  if(argc != 6){
    exit();
  }

  schedtest(atoi(argv[1]),(argv[2]),atoi(argv[3]),(argv[4]),atoi(argv[5]));


  exit();
}
