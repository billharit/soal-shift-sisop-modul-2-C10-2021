#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main() {
 pid_t  child1, child2, child3, child4, child5;
 int status;
 char url[300], file[50];

 child1 = fork();

 if(child1 < 0) {
  exit(EXIT_FAILURE);
 }

 if(child1 == 0){
  child2 = fork();

  if(child2 == 0){
   char *ex[] = {"mkdir", "sisop/Musyik", NULL};
   execv("/bin/mkdir", ex);
  }
  else {
   while((wait(&status)) > 0);
   child3 = fork();
   if(child3 == 0){
    sprintf(url, "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download");
    sprintf(file, "sisop/Musyik_for_Stevany.zip");
    char *ar[] = {"wget", url, "-O", file, NULL};
    execv("/bin/wget", ar);
   }
   else{
    while((wait(&status)) > 0);

    child4 = fork();

    if(child4 == 0){
     chdir("sisop");
     char *zip[] = {"unzip", "-q", "Musyik_for_Stevany.zip", NULL};
     execv("/bin/unzip", zip);
    }
    else{
     while((wait(&status)) > 0);

     child5 = fork();
     if(child5 == 0){
      char *move[] = {"find", "sisop/MUSIK", "-mindepth", "1", 
		   "-type", "f", "-exec", "/bin/mv", "-t", "sisop/Musyik", "{}", ";", (char *)NULL};
      execv("/bin/find", move);
     }
     else{
      child2 = fork();
     }
    }
   }
  }

  sleep(3);
  if(child2 == 0){
   char *ex[] = {"mkdir", "sisop/Fylm", NULL};
   execv("/bin/mkdir", ex);
  }
  else {
   while((wait(&status)) > 0);

   child3 = fork();

   if(child3 == 0){
    sprintf(url, "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download");
    sprintf(file, "sisop/Fylm_for_Stevany.zip");
    char *ar[] = {"wget", url, "-O", file, NULL};
    execv("/bin/wget", ar);
   }
   else{
    while((wait(&status)) > 0);

    child4 = fork();

    if(child4 == 0){
     chdir("sisop");
     char *zip[] = {"unzip", "-q", "Fylm_for_Stevany.zip", NULL};
     execv("/bin/unzip", zip);
    }
    else{
     while((wait(&status)) > 0);

     child5 = fork();
     if(child5 == 0){
      char *move[] = {"find", "sisop/FILM", "-mindepth", "1", 
                "-type", "f", "-exec", "/bin/mv", "-t", "sisop/Fylm", "{}", ";", (char *)NULL};
      execv("/bin/find", move);
     }
     else{
      child2 = fork();
     }
    }
   }
  }

  sleep(3);
  if(child2 == 0){
   char *ex[] = {"mkdir", "sisop/Pyoto", NULL};
   execv("/bin/mkdir", ex);
  }
  else{
   while((wait(&status)) > 0);

    child3 = fork();

    if(child3 == 0){
    sprintf(url, "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download");
    sprintf(file, "sisop/Pyoto_for_Stevany.zip");
    char *ar[] = {"wget", url, "-O", file, NULL};
    execv("/bin/wget", ar);
   }
   else {
    while((wait(&status)) > 0);

    child4 = fork();

    if(child4 == 0){
     chdir("sisop");
     char *zip[] = {"unzip", "-q", "Pyoto_for_Stevany.zip", NULL};
     execv("/bin/unzip", zip);
    }
    else{
     while((wait(&status)) > 0);

     child5 = fork();
     if(child5 == 0){
      char *move[] = {"find", "sisop/FOTO", "-mindepth", "1", 
                "-type", "f", "-exec", "/bin/mv", "-t", "sisop/Pyoto", "{}",  ";", (char *)NULL};
      execv("/bin/find", move);
     }
    }
   }
  }

  sleep(3);
  if(child1 == 0){
   child2 = fork();

   if(child2 == 0){
    char *del[] = {"rm", "-rf", "MUSIK", "FOTO", "FILM", NULL};
    execv("/bin/rm", del);
   }
   else{
    while((wait(&status)) > 0);

    chdir("sisop");
    char *zip[] = {"zip", "-r", "-m", "Lopyu_Stevany.zip", "Musyik", "Fylm", "Pyoto", NULL};
    execv("/bin/zip", zip);
   }
  }
 }
}
