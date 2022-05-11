#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
  int child_to_parent[2], parent_to_child[2];
  char* child_buf = 0, *parent_buf = 0;
  char byte = 'a';
  pipe(child_to_parent);
  pipe(parent_to_child);
  
  int pid = fork();
  if(pid == -1){
    fprintf(2, "fork() failed");
    exit(1);
  }
  if(pid == 0){
    close(child_to_parent[0]);
    close(parent_to_child[1]);
    read(parent_to_child[0], child_buf, 1);
    fprintf(1, "<%d>: received ping\n", getpid());
    write(child_to_parent[1], child_buf, 1);
    close(child_to_parent[1]);
    close(parent_to_child[0]);
  }
  else{
    close(child_to_parent[1]);
    close(parent_to_child[0]);
    write(parent_to_child[1], &byte, 1);
    read(child_to_parent[0], parent_buf, 1);
    fprintf(1, "<%d>: received pong\n", getpid());
    close(child_to_parent[0]);
    close(parent_to_child[1]);
    wait(0);
  }
  exit(0);
}
