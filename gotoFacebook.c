/** gotoFacebook Program
 * Version 0.3a
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
static char backup_default[MAX_LINE_LEN+1]="127.0.0.1 localhost"; //=> change file this to be suitable for you
// For Windows: static char link_host[MAX]="C:\Windows\System32\driver\etc\hosts"

/*Change host file*/
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
    fprintf(stderr,"Cannot Open File %s\n",link_host);
    perror("");
    return 0;
  }
  //write file
  while(fgets(buf,MAX_LINE_LEN+1,file_from)){
    if(fputs(buf,file_to)==EOF){
      fprintf(stderr,"Error writting to target file\n");
      perror("");
      return 0;
    }
  }
  
  if(!feof(file_from)){//loi fgets()
    fprintf(stderr,"Error reading from source file: %s\n",file_from);
    perror("");
    return 0;
  }
  /* loi dong file */
  if(fclose(file_from)==EOF){
    fprintf(stderr,"Error when closing source file: %s\n",file_from);
    perror("");
  }
  if(fclose(file_to)==EOF){
    fprintf(stderr,"Error when closing source file: %s\n",file_to);
    perror("");
  }
  return 1;
}
/*Resore host file*/
int restore_host_file(){
  FILE *f_open;
  
  f_open=fopen(link_host,"w+");
  if (!f_open){
    fprintf(stderr,"Error Open file %s \n",link_host);
    perror("");
    return 0;
  }
  //Restore
  fprintf(f_open,backup_default);
  if (fclose(f_open)){
    fprintf(stderr,"Error close file %s \n",link_host);
    perror("");
  }
  return 1;  
} 

/* Main program */
int main(int argc, char *argv[]){
  int opt;//getopt()
  if (argc < 1){
    fprintf(stderr,"Usage:%s <option> <sources of file>\n",argv[0]);
    fprintf(stdout,"Option:\n");
    fprintf(stdout,"-U: update list file\n");
    fprintf(stdout,"-R: restore list file\n");
    fprintf(stdout,"-B: backup list file\n");
  }
  else{
    while ((opt=getopt(argc,argv,"u:r"))!=-1){
      switch(opt){
	case 'u':
	  if (changes_host(optarg))
	    fprintf(stdout,"%s has been changed successfully. \n",optarg);
	  else
	    fprintf(stdout,"%s hasn't been changed.\n",optarg);
	  break;
	case 'r':
	  if (restore_host_file())
	    fprintf(stdout,"File has been restored successfully. \n");
	  else
	    fprintf(stdout,"File hasn't been restored.\n");
	  break;      
	case '?':
	  fprintf(stdout,"Unknown option %s",optopt);
	  break;
      }
    }
  }
  return 0;
}