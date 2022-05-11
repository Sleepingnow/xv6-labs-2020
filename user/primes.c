#include "kernel/types.h"
#include "user/user.h"

void process(int left_to_right[])
{
  int prime, curNum;
  int new_left_to_right[2];
  
  pipe(new_left_to_right);
  
  if(read(left_to_right[0], &prime, sizeof(int)) <= 0)
    return;
  fprintf(1, "prime %d\n", prime);
  
  if(fork() == 0){
    close(new_left_to_right[1]);
    process(new_left_to_right);
    close(new_left_to_right[0]);
  }
  else{
    close(new_left_to_right[0]);
    while(read(left_to_right[0], &curNum, sizeof(int)) > 0){
      if(curNum % prime != 0){
        write(new_left_to_right[1], &curNum, sizeof(int));
      }
    }
    close(new_left_to_right[1]);
    wait(0);
  }
  close(left_to_right[0]);
  close(left_to_right[1]);
}

int main(int argc, char* argv[])
{
  int left_to_right[2], i;
  pipe(left_to_right);
  
  if(fork() == 0){
    close(left_to_right[1]);
    process(left_to_right);
    close(left_to_right[0]);
  }
  else{
    close(left_to_right[0]);
    for(i = 2; i <= 35; ++i){
      write(left_to_right[1], &i, sizeof(int));   
    }
    close(left_to_right[1]);
    wait(0);
  }
  exit(0);
}
