#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p1[2], p2[2];

  pipe(p1);
  pipe(p2);

  if (fork() == 0) {
    close(p2[0]);
    close(p1[1]);
    char buf[1];
    read(p1[0], buf, 1);
    int pid = getpid();
    fprintf(1, "%d: received ping\n", pid);
    write(p2[1], buf, 1);
    close(p1[0]);
    close(p2[1]);
  } else {
    close(p1[0]);
    close(p2[1]);
    char buf[1];
    buf[0] = 'H';
    write(p1[1], buf, 1);
    read(p2[0], buf, 1);
    int pid = getpid();
    fprintf(1, "%d: received pong\n", pid);
    close(p2[0]);
    close(p1[1]);
  }
  exit(0);
}
