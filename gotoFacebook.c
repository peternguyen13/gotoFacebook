/** **************** **/
/** gotoFacebook.c **/


/** gotoFacebook Program
 * Version 0.4a
 * Written by Nguyen Vu Hoang (Peter Nguyen)
 * Public: GPL
 **/

/** check system **/
#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
  static char link_host[255]="C:\Windows\System32\driver\etc\hosts";  // for windows
#else
  static char link_host[255]="/etc/hosts"; // for Linux
#endif
/** end check system **/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX_LINE_LEN 1000

/*Change host file*/
int changes_host(char link_list[MAX_LINE_LEN+1]){  
  char buf[MAX_LINE_LEN+1];
  FILE *file_from;
  FILE *file_to;
  file_from=fopen(link_list,"r");  
  if (!file_from){//loi mo file
    fprintf(stderr,"Cannot Open File %s",link_list);
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
      fprintf(stderr,"Error writting file\n");
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
int restore_host_file(char link_to_restore[MAX_LINE_LEN]){
  char buf[MAX_LINE_LEN+1];
  FILE *file_from;
  FILE *file_to;
  
  file_from=fopen(link_to_restore,"r");
  if (!file_from){
    fprintf(stderr,"Error Open file %s \n",link_host);
    perror("");
    return 0;
  }
  
  file_to=fopen(link_host,"w+");
  if (!file_to){
    fprintf(stderr,"Error Open file %s \n",link_host);
    perror("");
    return 0;
  }
  //chep file
  while(fgets(buf,MAX_LINE_LEN+1,file_from)){
    if(fputs(buf,file_to)==EOF){
      fprintf(stderr,"Error writting file\n");
      perror("");
      return 0;
    }
  }
  
  if(!feof(file_from)){
    fprintf(stderr,"Error reading sources file\n");
    perror("");
    return 0;
  }
  
  if (fclose(file_from)){
    fprintf(stderr,"Error close file %s \n",link_to_restore);
    perror("");
  }
  
  if (fclose(file_to)){
    fprintf(stderr,"Error close file %s \n",link_host);
    perror("");
  }
  return 1;  
}


int backup_host_file(char link_to_backup[MAX_LINE_LEN+1]){
  char buf[MAX_LINE_LEN+1];
  FILE *file_from;
  FILE *file_to;
  
  file_from=fopen(link_host,"r");
  if (!file_from){
    fprintf(stderr,"Error Open file %s \n",link_host);
    perror("");
    return 0;
  }
  
  file_to=fopen(link_to_backup,"w+");
  if (!file_to){
    fprintf(stderr,"Error Open file %s \n",link_to_backup);
    perror("");
    return 0;
  }
  //chep file
  while(fgets(buf,MAX_LINE_LEN+1,file_from)){
    if(fputs(buf,file_to)==EOF){
      fprintf(stderr,"Error writting file\n");
      perror("");
      return 0;
    }
  } 
  
  if(!feof(file_from)){
    fprintf(stderr,"Error reading sources file\n");
    perror("");
    return 0;
  }
  
  if (fclose(file_from)){
    fprintf(stderr,"Error close file %s \n",link_to_backup);
    perror("");
  }
  
  if (fclose(file_to)){
    fprintf(stderr,"Error close file %s \n",link_host);
    perror("");
  }
  return 1;  
} 

/* Main program */
int main(int argc, char *argv[]){
  int opt;//getopt()
  if (argc < 2){
    fprintf(stderr,"Usage:%s <option> <sources of file>\n",argv[0]);
    fprintf(stdout,"Use commant %s -H to help",argv[0]);
  }
  else{
    while ((opt=getopt(argc,argv,"U:B:R:H"))!=-1){
      switch(opt){
	case 'U':
	  if (changes_host(optarg))
	    fprintf(stdout,"%s has been changed successfully. \n",optarg);
	  else
	    fprintf(stdout,"%s hasn't been changed.\n",optarg);
	  break;
	case 'R':
	  if (restore_host_file(optarg))
	    fprintf(stdout,"File has been restored successfully. \n");
	  else
	    fprintf(stdout,"File hasn't been restored.\n");
	  break;
	case 'B':
	  if (backup_host_file(optarg))
	    fprintf(stdout,"File has been backup successfully. \n");
	  else
	    fprintf(stdout,"File hasn't been backup.\n");
	  break;
	case 'H':
	  fprintf(stdout,"Option:\n");
	  fprintf(stdout,"-U: update list file\n");
	  fprintf(stdout,"-R: restore list file\n");
	  fprintf(stdout,"-B: backup list file\n");
	  break;
	case '?':
	  fprintf(stdout,"Unknown option %s",optopt);
	  break;
      }
    }
  }
  return 0;
}