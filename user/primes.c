#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void childProces(int fd){
  int number;
  read(fd, &number, sizeof(number));
  fprintf(1, "prime %d\n", number);

  int p[2];
  pipe(p);
  int tmp = 0;
  while(1){
    int n = read(fd, &tmp, sizeof(tmp));
    if (n <= 0){
      break;
    }
    if (tmp % number != 0){
      write(p[1], &tmp, sizeof(tmp));
    }
  }

  if (tmp == 0){
    close(p[0]);
    close(p[1]);
    close(fd);
    return;
  }

  int pid = fork();

  if (pid == 0){
    close(p[1]);
    close(fd);
    childProces(p[0]);
    close(p[0]);
  } else {
    close(p[0]);
    close(p[1]);
    close(fd);
    wait(0);
  }
}


int main(int argc, char *argv[]){
  int p[2];
  pipe(p);
  for(int i = 2; i <= 35; i++){
    write(p[1], &i, sizeof(i));
  }
  close(p[1]);
  childProces(p[0]);
  close(p[0]);
  exit(0);
}
