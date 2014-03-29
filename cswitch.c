#include "switches.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

//Displays command that started pid

void cswitch(int pid)
{
 FILE *f;
 char statfile[100], result[100], name[50];
 int x = 100;
 
 sprintf(statfile, "cat /proc/%d/cmdline", pid);
 f = popen(statfile, "r");
 fgets(result,100,f);
 printf("COMMAND:\n%s\n",result);

  
}
