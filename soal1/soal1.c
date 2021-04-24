#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

int main() {
 pid_t pid, sid;
 pid_t  child1, child2, child3, child4, child5;
 int status;
 char url[300], file[50];
 int hour, min, sec, day, month;
 
 pid = fork();

 if(pid < 0){
  exit(EXIT_FAILURE);
 }
 
 if(pid > 0){
  exit(EXIT_SUCCESS);
 }
   
 umask(0);
 
 sid=setsid();
  
 if(sid<0){
  exit(EXIT_FAILURE);
 }

 
 close(STDIN_FILENO);
 close(STDOUT_FILENO);
 close(STDERR_FILENO);

 while(1){
 
  time_t now = time(NULL);
  struct tm *local = localtime(&now);
 
  hour = local->tm_hour;
  min = local->tm_min;
  sec = local->tm_sec;
 
  day = local->tm_mday;
  month = local->tm_mon+1;
  
  if(month==4 && day==9 && hour==16 && min==22 && sec==0){
   
    child2 = fork();

    if(child2 == 0){
     char *ex[] = {"mkdir", "modul2/Musyik", NULL};
     execv("/bin/mkdir", ex);
    }
    else {
     while((wait(&status)) > 0);
     child3 = fork();
     if(child3 == 0){
      sprintf(url, "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download");
      sprintf(file, "modul2/Musik_for_Stevany.zip");
      char *ar[] = {"wget", "--no-check-certificate", url, "-O", file, NULL};
      execv("/usr/bin/wget", ar);
     }
     else{
      while((wait(&status)) > 0);

      child4 = fork();

      if(child4 == 0){
       chdir("modul2");
       char *zip[] = {"unzip", "-q", "Musik_for_Stevany.zip", NULL};
       execv("/usr/bin/unzip", zip);
      }
      else{
       while((wait(&status)) > 0);

       child5 = fork();
       if(child5 == 0){
        char *move[] = {"find", "modul2/MUSIK", "-mindepth", "1", 
       "-type", "f", "-exec", "/bin/mv", "-t", "modul2/Musyik", "{}", ";", (char *)NULL};
        execv("/usr/bin/find", move);
       }
       else{
        while((wait(&status)) > 0);
        
        child2 = fork();
       }
      }
     }
    }

    sleep(3);
    if(child2 == 0){
     char *ex[] = {"mkdir", "modul2/Fylm", NULL};
     execv("/bin/mkdir", ex);
    }
    else {
     while((wait(&status)) > 0);

     child3 = fork(); 

     if(child3 == 0){
      sprintf(url, "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download");
      sprintf(file, "modul2/Film_for_Stevany.zip");
      char *ar[] = {"wget", "--no-check-certificate", url, "-O", file, NULL};
      execv("/usr/bin/wget", ar);
     }
     else{
      while((wait(&status)) > 0);

      child4 = fork();
 
      if(child4 == 0){
       chdir("modul2");
       char *zip[] = {"unzip", "-q", "Film_for_Stevany.zip", NULL};
       execv("/usr/bin/unzip", zip);
      }
      else{
       while((wait(&status)) > 0);

       child5 = fork();
       if(child5 == 0){
        char *move[] = {"find", "modul2/FILM", "-mindepth", "1", 
                "-type", "f", "-exec", "/bin/mv", "-t", "modul2/Fylm", "{}", ";", (char *)NULL};
        execv("/usr/bin/find", move);
       }
       else{
        while((wait(&status)) > 0);
        
        child2 = fork();
       }
      }
     }
    }

    sleep(3);
    if(child2 == 0){
     char *ex[] = {"mkdir", "modul2/Pyoto", NULL};
     execv("/bin/mkdir", ex);
    }
    else{
     while((wait(&status)) > 0);

      child3 = fork();

      if(child3 == 0){
      sprintf(url, "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download");
      sprintf(file, "modul2/Foto_for_Stevany.zip");
      char *ar[] = {"wget", "--no-check-certificate", url, "-O", file, NULL};
      execv("/usr/bin/wget", ar);
     }
     else {
      while((wait(&status)) > 0);

      child4 = fork();

      if(child4 == 0){
       chdir("modul2");
       char *zip[] = {"unzip", "-q", "Foto_for_Stevany.zip", NULL};
       execv("/usr/bin/unzip", zip);
      }
      else{
       while((wait(&status)) > 0);

       child5 = fork();
       if(child5 == 0){
        char *move[] = {"find", "modul2/FOTO", "-mindepth", "1", 
                 "-type", "f", "-exec", "/bin/mv", "-t", "modul2/Pyoto", "{}",  ";", (char *)NULL};
        execv("/usr/bin/find", move);
       }
      }
     }
    }
  }

  else if(month==4 && day==9 && hour==22 && min==22 && sec==0){
   
    child2 = fork();

    if(child2 == 0){
     char *del[] = {"rm", "-rf", "modul2/MUSIK", "modul2/FOTO", "modul2/FILM", NULL};
     execv("/bin/rm", del);
    }
    else{
     while((wait(&status)) > 0);

     chdir("modul2");
     char *zip[] = {"zip", "-r", "-m", "Lopyu_Stevany.zip", "Musyik", "Fylm", "Pyoto", NULL};
     execv("/usr/bin/zip", zip);  
    }
   }
  sleep(1);
 }
}
