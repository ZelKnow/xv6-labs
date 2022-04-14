#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
childFunc(int p[2])
{
  int i, cur;
  int p2[2];
  close(p[1]);
  if (read(p[0], &i, 4) == 0) {
    close(p[0]);
    exit(0);
  }
  pipe(p2);
  fprintf(1, "prime %d\n", i);
  if (fork() == 0) {
    close(p[0]);
    childFunc(p2);
  } else {
    close(p2[0]);
    while (read(p[0], &cur, 4) != 0) {
      if (cur % i != 0) {
        write(p2[1], &cur, 4);
      }
    }
    close(p[0]);
    close(p2[1]);
    wait(0);
  }
  exit(0);
}

int
main(int argc, char *argv[])
{
  int i;
  int p[2];
  pipe(p);
  if (fork() == 0) {
    childFunc(p);
  } else {
    close(p[0]);
    for (i = 2; i < 35; i++){
      write(p[1], &i, 4);
    }
    close(p[1]);
    wait(0);
  }
  exit(0);
}
