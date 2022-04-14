#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i, j, k, beg;
  char in;
  char buf[512];
  k = 0;
  beg = 0;
  while (read(0, &in, 1) != 0)
  {
    char *newArgv[MAXARG] = {0};
    for (i = 1; i < argc; i++) {
      newArgv[i - 1] = argv[i];
    }
    j = argc - 1;
    while (1)
    {
      if (in == ' ' || in == '\n') {
        buf[k++] = 0;
        newArgv[j++] = &buf[beg];
        beg = k;
        if (in == '\n') {
          break;
        }
      }
      else
      {
        buf[k++] = in;
      }
      read(0, &in, 1);
    }
    if (fork() == 0) { 
      exec(argv[1], newArgv);
      exit(0);
    } else {
      wait(0);
    }
  }
  exit(0);
}
