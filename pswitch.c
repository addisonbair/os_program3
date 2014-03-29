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

//Displays process information regarding pid

void pswitch(int pid)
{
 
 FILE *f;
 char statfile[100], result[100];
   
 sprintf(statfile, "ls -l /proc/%d/stat", pid);
 f = popen(statfile, "r");
 fgets(result,100,f);
 
 printf("*************\n");
 printf("PROCESS INFO:\n%s",result);
}
