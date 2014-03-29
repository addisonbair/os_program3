/*
Creator: Josh Beebe
CS4323 Program 1
References:
http://stackoverflow.com/questions/12005902/c-program-linux-get-command-line-output-to-a-variable-and-filter-data
http://techbasiclogic.blogspot.com/2010/04/linux-readdir-example-code-to-check.html
http://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
http://www.tutorialspoint.com/c_standard_library/c_function_strtok.htmps
*/

#include <stdlib.h>
#include <stdio.h>
#include "switches.h"
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <dirent.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char **argv)
{
 int x = 0, countp = 0, countU = 0, countc = 0;
 int pid[50], pid2 = 0, pexists = 0, isint = 0;
 int i = 0, y = 0;
 DIR *fd_proc;
 FILE *f;
 struct dirent *dirp;
 char statfile[100], result[100], name[50];
  
 //Option string leads with : for silent mode
 //This way I can control my own errors 
 //If no argument is found for p, then case ":" begins
 
 while((x = getopt(argc, argv, ":p:sUSvc")) != -1)
 {
  switch(x)
  {
   case 'p':
     isint = atoi(optarg);
     if(isint == 0) //Exit program if invalid arg or 0 for -p
     {
      printf("ERROR: Invalid -p argument\n");
      return 1;  
     }
     pexists = 1; //-p is found
     i = 1;
     break;
   case ':':
    if(optopt == 'p') //Exit program if no arg for -p
    {
     printf("ERROR: No argument specified for -p\n");
     return 1;
    }
  }
 }

 optind = 0; //Resetting getopt
 
 if(pexists == 0) //if no -p is present
 {
  
  fd_proc = opendir("/proc/");
  

  while((dirp = readdir(fd_proc)) != NULL)
  {
   pid2 = atoi(dirp->d_name);
 
   if (pid2 <= 0) //Ignore non-pids in directory
    continue;
   
   sprintf(statfile, "ls -l /proc/%s/stat", dirp->d_name);
   f = popen(statfile, "r");
   fgets(result,100,f);
   getlogin_r(name,50); //This gets the current user
 
   if(strstr(result, name))
   {
    pid[i] = pid2;
    i = i + 1; //Keep count of # of processes that current user owns
   }
  } 
 }
 //Loop until # of process is reached.  If -p is specified
 //then only forloop one time
 for(y = 0; y < i; y++)
 {
   //resetting value for next pid
   optind = 0;
   countU = 0;
   countc = 0;
   countp = 0;

   while((x = getopt(argc, argv, ":p:sUSvc"))!= -1)
   {
    switch(x) //Find out which options are input
    {
     case 'p':
       if(countp != 0)
        break;
       
       //Convert optarg to int
       pid[y] = atoi(optarg);
       
       if(pid[y] == 0)
       {
        printf("ERROR: Invalid -p argument\n");
        return 1;
       }

       pswitch(pid[y]);
       countp = countp + 1; //On all cases, make sure to flag -p to ensure it's first
       break;
     case 's':
      if(countp == 0)
      {
       pswitch(pid[y]);
       countp = countp + 1;
      }
       sswitch(pid[y]);
       break;
     case 'U':
       if(countp == 0)
       {
        pswitch(pid[y]);
        countp = countp + 1;
       }
       if(countU == 0)
       {
         Uswitch(pid[y]);
         countU = countU + 1;
       }
       break;
     case 'S':
       if(countp == 0)
       {
        pswitch(pid[y]);
        countp = countp + 1;
       }
       Sswitch(pid[y]);
       break;
     case 'v':
       if(countp == 0)
       {
        pswitch(pid[y]);
        countp = countp + 1;
       }
       vswitch(pid[y]);
       break;
     case 'c':
       if(countp == 0)
       {
        pswitch(pid[y]);
        countp = countp + 1;
       }
       if(countc == 0)
       {
        cswitch(pid[y]);
        countc = countc + 1;
       }
       break;
     //If no argument is found
     case ':':
       //If option is p
       if(optopt == 'p')
       {
        printf("ERROR: No argument specified for -p\n");
        return 1;
       }
       break;
    }
   }
   
    if(countp == 0)
    {
     pswitch(pid[y]);
     countp = countp + 1;
    }

    //Options that are output regardless
    if(countU == 0)
    {
      Uswitch(pid[y]);
      countU = countU + 1;
    }
    if(countc == 0)
    {
      cswitch(pid[y]);
      countc = countc + 1;
    }
 }
 printf("*************\n"); //End of output
} 
