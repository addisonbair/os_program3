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

//Displays utime of pid

void Uswitch(int pid)
{
 DIR *fd_proc;
 FILE *f;
 struct dirent *dirp;
 char statfile[100], result[100], name[50], *str;
 int i = 0, count = 0;
 
 fd_proc = opendir("/proc/");
 
 sprintf(statfile, "cat /proc/%d/stat", pid);
 f = popen(statfile, "r");
 fgets(result,100,f);
 
 str = strtok(result," ");
 
 while (str != NULL)
  {
   if(count == 13) //12th item in file
   {
    printf("UTIME:\n%s\n",str);
   }
   str = strtok(NULL," ");
   count = count + 1;
  }
}
