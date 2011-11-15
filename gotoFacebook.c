/** gotoFacebook Program
 * Version 0.1a
 * Written by Nguyen Vu Hoang (Peter Nguyen)
 * Public: GPL
 **/

/**
 * 1. How to build gotoFacebook?
 * 	+For Windows:
 * 		Uses: Codeblocks, C-Free, Dev-C to build
 * 	+For Linux:
 * 		Uses: gcc gotoFacebook.c -o gotoFacebook
 * 2. Using gotoFacebook:
 * 	+For Windows:
 * 		Run Command Line as Administrator
 * 		Run gotoFacebook < list file include ip to hosts >
 * 	+For Linux:
 * 		The same
 * 		Run as root
 **/ 

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX_LINE_LEN 1000

static char link_host[MAX_LINE_LEN+1]="/etc/hosts"; // => For Linux
// For Windows: static char link_host[MAX]="C:\Windows\System32\driver\etc\hosts"

  /* int changes_host(char link_host_files);
   * return 0; Error
   * return 1; Success
   */

int changes_host(char link_host_files[MAX_LINE_LEN+1]){  
  char buf[MAX_LINE_LEN+1];
  FILE *file_from;
  FILE *file_to;
  file_from=fopen(link_host_files,"r");  
  if (!file_from){//loi mo file
    fprintf(stderr,"Cannot Open File %s",link_host_files);
    perror("");
    return 0;
  }
  
  file_to=fopen(link_host,"w+");
  if(!file_to){//loi mo file
    fprintf(stderr,"Cannot Open File %s",link_host);
    perror("");
    return 0;
  }
  //write file
  while(fgets(buf,MAX_LINE_LEN+1,file_from)){
    if(fputs(buf,file_to)==EOF){
      fprintf(stderr,"Error writting to target file");
      perror("");
      return 0;
    }
  }
  
  if(!feof(file_from)){//loi fgets()
    fprintf(stderr,"Error reading from source file: %s",file_from);
    perror("");
    return 0;
  }
  /* loi dong file */
  if(fclose(file_from)==EOF){
    fprintf(stderr,"Error when closing source file: %s",file_from);
    perror("");
  }
  if(fclose(file_to)==EOF){
    fprintf(stderr,"Error when closing source file: %s",file_to);
    perror("");
  }
  return 1;
}

/* Main progream */
int main(int argc, char *argv[]){
  int bool; //get True or False
  if (argc < 2 || !argv[1]){ 
    fprintf(stderr,"Usage: %s <source file host> ",argv[0]);
    exit(1);
  }
  bool=changes_host(argv[1]);
  if (bool)
    fprintf(stdout,"%s has been changed successfully. \n",argv[1]);
  else
    fprintf(stdout,"%s hasn't been changed.\n",argv[1]);
  return 0;
}