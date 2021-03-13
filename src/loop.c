#include "types.h"
#include "stat.h"
#include "pstat.h"
#include "user.h"

void
loop(int sleepT)
{
  sleep(sleepT);

  int i = 0, j = 0;
  while (i < 800000000) {
    j += i * j + 1;
    i++;
  }
}

int main(int argc, char *argv[])
{

  if(argc != 2){
    exit();
  }

  // printf(1, "starting sleep\n");
  loop(atoi(argv[1]));
  // printf(1, "done sleep\n");

  exit();
}
