#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
  int time;
  
  if(argc < 2){
    fprintf(2, "Usage: <sleep time>");
    exit(1);
  }
  
  time = atoi(argv[1]);
  if(time <= 0){
    fprintf(2, "Sleep: invalid sleep time");
    exit(1);
  }
  sleep(time);
  exit(0);
}

