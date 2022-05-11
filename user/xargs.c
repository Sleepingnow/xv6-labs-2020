#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char* argv[])
{
  int len = 0, idx = 0;
  char* exec_argv[MAXARG], buf[512];
  
  for(int i = 1; i < argc; ++i)
    exec_argv[i - 1] = argv[i];
  
  while(1){
    idx = 0;
    while((len = read(0, buf + idx, sizeof(char))) > 0){
      if(buf[idx] == '\n'){
        buf[idx] = '\0';
        break;
      }
      ++idx;
    }
  
    if(len == 0 && idx == 0)
      break;
    exec_argv[argc - 1] = buf;
    if(fork() == 0){
      exec(exec_argv[0], exec_argv);
      exit(0);
    }
    else{
      wait(0);
    }
  }
  exit(0);
}
