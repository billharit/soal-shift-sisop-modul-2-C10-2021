#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

void Killer()
{
  pid_t child_id4;
  FILE* kill;
  kill = fopen("Killer.sh", "w");
  // fprintf(kill, "#!/bin/bash\nkill %d\nrm \"$0\"",getpid());
  fprintf(kill, "#!/bin/bash\nif [ $1 -eq \"-x\" ]\nthen\n\tkill %d\n \trm \"$0\"\nelse\n\tkillall -9 soal3\n\trm \"$0\"\nfi",getpid()); 
  fclose(kill);
  child_id4 = fork();
  if(child_id4 == 0 )
  {
    char *arg[]={"chmod","u+x","Killer.sh",NULL};
    execv("/bin/chmod", arg);
  }

}

void caesar(char message[])
{
  int key = 5;
  char ch;
	int i;

  for(i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			
			message[i] = ch;
		}
	}
}

void downloadgambar(char nama[])
{
    pid_t child_id2, child_id3;
    int status,i;
    child_id2 = fork();
    chdir(nama);
    FILE *fp;

    if(child_id2 == 0){

      
      for(i=1;i<=10;i++){
        
      char buffer[50];
      char namafile[100];
      time_t now;
      struct tm* timeinfo;
      time (&now);
      timeinfo = localtime (&now);
      strftime(buffer,100,"%Y-%m-%d_%H:%M:%S", timeinfo);
      sprintf(namafile,"%s.jpg", buffer);
      char link[50];
      sprintf(link,"https://picsum.photos/%ld", (now%1000) + 50);
        child_id3 = fork();
        if(child_id3 == 0) {
          char *argv[] = {"wget", "-qO", namafile,link, NULL};
          execv("/bin/wget", argv);
        }

        sleep(5);
      }

      char statusmsg[30] = "Download Success";
        caesar(statusmsg);
        fp = fopen("status.txt", "w");
        fprintf(fp, statusmsg);
        fclose(fp);

    chdir("..");

    char *zipargv[] = {"zip", "-rm", nama,nama, NULL};
    execv("/bin/zip", zipargv);

    }
        
}

void buatfolder(char nama[])
{
    time_t now;
    struct tm* timeinfo;
    time (&now);
    timeinfo = localtime (&now);
    // printf("[%d %d %d %d:%d:%d]",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    strftime(nama,60,"%Y-%m-%d_%H:%M:%S", timeinfo);

    pid_t child_id1;
    child_id1 = fork();
    if(child_id1 == 0){
        char *argv[] = {"mkdir", "-p", nama, NULL};
        execv("/bin/mkdir", argv);
    }
}

int main() {

   pid_t pid, sid;        // Variabel untuk menyimpan PID
   int status1,status2;
  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  Killer();

    while(1)
    {
        char nama[60];
        buatfolder(nama);
        while(wait(&status1)>0);
        downloadgambar(nama);
        while(wait(&status2)>0);
        
        
        sleep(40);
    }
}