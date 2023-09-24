#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]){
  char buf[8];
  int p[2];
  pipe(p);

  int pid = fork();
  if (pid > 0){
    wait(0);
    read(p[0], buf, 4);
    fprintf(1, "%d: received pong\n", getpid());
  } else if (pid == 0){
    write(p[1], "ping", 4);
    fprintf(1, "%d: received ping\n", getpid());
  } else {
    exit(-1);
  }
  exit(0);
}
