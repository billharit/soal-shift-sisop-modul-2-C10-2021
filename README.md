# soal-shift-sisop-modul-2-C10-2021

### KELOMPOK : C10

| **No** | **Nama** | **NRP** | 
| ------------- | ------------- | --------- |
| 1 | Dicksen Alfersius Novian  | 05111940000076 | 
| 2 | Vyra Fania Adelina  | 05111940000109 |
| 3 | Bill Harit Yafi  | 05111940000114 |


### Soal 1
> **[soal1.c](https://github.com/billharit/soal-shift-sisop-modul-2-C10-2021/blob/main/soal1/soal1.c)**

a. 

```
child2 = fork();

    if(child2 == 0){
     char *ex[] = {"mkdir", "modul2/Musyik", NULL};
     execv("/bin/mkdir", ex);
    }
```

```
if(child2 == 0){
     char *ex[] = {"mkdir", "modul2/Fylm", NULL};
     execv("/bin/mkdir", ex);
    }
```

```
if(child2 == 0){
     char *ex[] = {"mkdir", "modul2/Pyoto", NULL};
     execv("/bin/mkdir", ex);
    }
```

b. 


```
    child3 = fork();
     if(child3 == 0){
      sprintf(url, "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download");
      sprintf(file, "modul2/Musik_for_Stevany.zip");
      char *ar[] = {"wget", "--no-check-certificate", url, "-O", file, NULL};
      execv("/usr/bin/wget", ar);
     }
```

```
    if(child3 == 0){
      sprintf(url, "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download");
      sprintf(file, "modul2/Film_for_Stevany.zip");
      char *ar[] = {"wget", "--no-check-certificate", url, "-O", file, NULL};
      execv("/usr/bin/wget", ar);
     }
```

```
    if(child3 == 0){
      sprintf(url, "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download");
      sprintf(file, "modul2/Foto_for_Stevany.zip");
      char *ar[] = {"wget", "--no-check-certificate", url, "-O", file, NULL};
      execv("/usr/bin/wget", ar);
     }
```

c.

```
       chdir("modul2");
       char *zip[] = {"unzip", "-q", "Musik_for_Stevany.zip", NULL};
       execv("/usr/bin/unzip", zip);
```

```
       chdir("modul2");
       char *zip[] = {"unzip", "-q", "Film_for_Stevany.zip", NULL};
       execv("/usr/bin/unzip", zip);
```

```
       chdir("modul2");
       char *zip[] = {"unzip", "-q", "Foto_for_Stevany.zip", NULL};
       execv("/usr/bin/unzip", zip);
```

d.

```
child5 = fork();
if(child5 == 0){
        char *move[] = {"find", "modul2/MUSIK", "-mindepth", "1", 
       "-type", "f", "-exec", "/bin/mv", "-t", "modul2/Musyik", "{}", ";", (char *)NULL};
        execv("/usr/bin/find", move);
       }
```

```
 child5 = fork();
 if(child5 == 0){
        char *move[] = {"find", "modul2/FILM", "-mindepth", "1", 
                "-type", "f", "-exec", "/bin/mv", "-t", "modul2/Fylm", "{}", ";", (char *)NULL};
        execv("/usr/bin/find", move);
       }
```

```
child5 = fork();
       if(child5 == 0){
        char *move[] = {"find", "modul2/FOTO", "-mindepth", "1", 
                 "-type", "f", "-exec", "/bin/mv", "-t", "modul2/Pyoto", "{}",  ";", (char *)NULL};
        execv("/usr/bin/find", move);
```

e.

```
char *del[] = {"rm", "-rf", "modul2/MUSIK", "modul2/FOTO", "modul2/FILM", NULL};
     execv("/bin/rm", del);
```

f.

```
 chdir("modul2");
     char *zip[] = {"zip", "-r", "-m", "Lopyu_Stevany.zip", "Musyik", "Fylm", "Pyoto", NULL};
     execv("/usr/bin/zip", zip);  
```

### Soal 2
> **[soal2.c](https://github.com/billharit/soal-shift-sisop-modul-2-C10-2021/blob/main/soal2/soal2.c)**

Pada soal 2, diminta untuk membantu pengolahan data dalam suatu file .zip. Adapun keperluan sebagai berikut 
    
    A.  Diminta untuk unzip file 'pets.zip' kedalam folder "/home/[user]/modul2/petshop", lalu menghapus folder-folder yang tidak dibutuhkan.
Untuk melakukan ekstrak file zip, dilakukan perintah :
          
```c
  //EKSTRAK File .zip
        
  char *argv[]= {"unzip", "pets.zip", "-d", "/home/dicksen/modul2/petshop", NULL};
  execv("/bin/unzip",argv);
``` 
Untuk menghapus folder-folder yang tidak dibutuhkan, dilakukan perintah :
        
```c
// sleep the process for 1 second
        sleep(1);

        DIR *isi_petshop;
        struct dirent *isi;
        char path_petshop[] = "/home/dicksen/modul2/petshop";
        isi_petshop = opendir(path_petshop);
        char *nama_isi_petshop;
        //Menghapus Folder dan mencatat nama file gambar
        if(isi_petshop != NULL){
            while((isi = readdir(isi_petshop))){
                nama_isi_petshop = isi->d_name;
                //Jika jenis file adalah directory
                if(isi->d_type == 4){
                    
                    char hapus_direktori[200] = "/home/dicksen/modul2/petshop/";
                    strcat(hapus_direktori,nama_isi_petshop);
                    char *argumen_hapus[] = {"rm", "-r", hapus_direktori, NULL};
                    pid_t proses_hapus_direktori = fork();
                    if(proses_hapus_direktori == 0){
                        execv("/bin/rm",argumen_hapus);
                    }else{
                        //perror("maaf, penghapusan gagal :(\n");
                    }
                    wait(NULL);
                    
                }else{    
                    strcpy(nama_file[banyak_file_awal],nama_isi_petshop);
                    banyak_file_awal++;
                }
            }
            (void) closedir (isi_petshop);
```
Pada operasi diatas, selain menghapus folder didalam folder petshop, dilakukan katalog nama-nama file yang dimasukkan kedalam array 2D, serta menghitung banyaknya file gambar didalam folder petshop.
```c
    char nama_file[200][200]; //menyimpan nama dari setiap file gambar hewan
    int banyak_file_awal=0;
```

        
    B.  Mengategorikan foto peliharaan sesuai dengan jenis peliharaan.
    
Diminta untuk membuat folder sesuai jenis peliharaan, seperti "cat" akan masuk kedalam "petshop/cat" . Dilakukan perintah sebagai berikut:
    
```c
 //Membuat Folder Sesuai Jenis peliharaan
        int i;
        for(i = 0 ; i < banyak_file_awal ; i++){
            char *jenis_peliharaan; //menyimpan nama jenis peliharaan
            char temp[200]; 
            strcpy(temp,nama_file[i]);
            jenis_peliharaan = strtok(temp,";");
            char direktori_jenis_peliharaan[500] = "/home/dicksen/modul2/petshop/";
            strcat(direktori_jenis_peliharaan,jenis_peliharaan);
            pid_t proses_membuat_folder = fork();
            if(proses_membuat_folder == 0){
                char *argumen_membuat_folder[] = {"mkdir", "-p", direktori_jenis_peliharaan, NULL};
                execv("/bin/mkdir", argumen_membuat_folder);

            }
        }

```

Pada perintah diatas, dilakukan tokenizing pada array of char (nama file). Diambil jenis peliharaan untuk tiap file dalam folder petshop.
    
    C.  Memindahkan foto ke folder sesuai dengan jenis peliharaan, dengan memerhatikan nama file.
    
foto yang dipindahkan harus diganti namanya dari format [jenis peliharaan];[nama peliharaan];[umur peliharaan dalam tahun], menjadi [nama peliharaan]. Untuk melakukan hal tersebut, dilakukan perintah :

```c
//Memasukkan file gambar kedalam folder
        for(i = 0 ; i < banyak_file_awal ; i++){
            char *token_peliharaan; //menyimpan token file gambar
            char temp[200]; 
            strcpy(temp,nama_file[i]);
            if(strchr(temp,'_')==NULL){
                token_peliharaan = strtok(temp,";");
                char nama_folder_dan_peliharaan[200];
                int indeks_token = 0;
                //Mengambil token "jenis peliharaan" dan "nama peliharaan"
                while(token_peliharaan!=NULL){
                    if(indeks_token == 0){
                        strcpy(nama_folder_dan_peliharaan,token_peliharaan);
                        char slash = '/';
                        strncat(nama_folder_dan_peliharaan,&slash,1);
                    }
                    else if(indeks_token == 1){
                        strcat(nama_folder_dan_peliharaan,token_peliharaan);
                        strcat(nama_folder_dan_peliharaan,".jpg");
                    }
                    token_peliharaan = strtok(NULL,";");
                    indeks_token++;
                }
                char direktori_jenis_peliharaan[500] = "/home/dicksen/modul2/petshop/";
                char direktori_file_peliharaan[200] = "/home/dicksen/modul2/petshop/";
                strcat(direktori_jenis_peliharaan,nama_folder_dan_peliharaan);
                strcat(direktori_file_peliharaan,nama_file[i]);
                pid_t proses_memindahkan_gambar = fork();
                if(proses_memindahkan_gambar == 0){
                    char *argumen_memindahkan_gambar[] = {"cp", direktori_file_peliharaan, 
                                                        direktori_jenis_peliharaan, NULL};
                    execv("/bin/cp", argumen_memindahkan_gambar);
                }
            }
        }

```

Blok kode diatas digunakan untuk menyalin file gambar berisi 1 peliharaan kedalam folder sesuai dengan jenis peliharaan. Untuk kasus-kasus khusus, akan dibahas di sub-soal bagian D.
    
    D. Dikarenakan dalam satu file foto, bisa terdapat lebih dari 1 peliharaan, maka diminta untuk memindahkan masing-masing peliharaan kedalam folder sesuai jenis.
    
Pada bagian ini, diminta untuk mengindentifikasi peliharaan apa saja yang ada dalam 1 foto dan memindahkannya sesuai jenis peliharaan. Berikut blok kode yang digunakan :
    
```c
        //Memasukkan foto dengan lebih dari satu peliharaan kedalam folder
        for(i = 0 ; i < banyak_file_awal ; i++){
            char *token_peliharaan; //menyimpan token file gambar
            char temp[200]; 
            strcpy(temp,nama_file[i]);
            if(strchr(temp,'_')!=NULL){
                token_peliharaan = strtok(temp, "_");
                char multi_peliharaan[50][200];
                int indeks_multi_peliharaan=0;
                strcpy(multi_peliharaan[0],token_peliharaan);
                while(token_peliharaan!= NULL){
                    strcpy(multi_peliharaan[indeks_multi_peliharaan],token_peliharaan);
                    if(indeks_multi_peliharaan == 0){
                        strcat(multi_peliharaan[indeks_multi_peliharaan],".jpg");
                    }
                    token_peliharaan = strtok(NULL, "_");
                    indeks_multi_peliharaan++;
                    //puts(multi_peliharaan[indeks_multi_peliharaan-1]);
                }
                
                int j;
                //Melakukan looping untuk setiap peliharaan dalam 1 file gambar
                for(j=0; j<indeks_multi_peliharaan;j++){

                    strcpy(temp,multi_peliharaan[j]);
                    token_peliharaan = strtok(temp,";");
                    int indeks_token = 0;
                    char nama_folder_dan_peliharaan[200];
                    //Mengambil token "jenis peliharaan" dan "nama peliharaan"
                    while(token_peliharaan!=NULL){
                        if(indeks_token == 0){
                            strcpy(nama_folder_dan_peliharaan,token_peliharaan);
                            char slash = '/';
                            strncat(nama_folder_dan_peliharaan,&slash,1);
                        }
                        else if(indeks_token == 1){
                            strcat(nama_folder_dan_peliharaan,token_peliharaan);
                            strcat(nama_folder_dan_peliharaan,".jpg");
                        }
                        token_peliharaan = strtok(NULL,";");
                        indeks_token++;
                    }
                    char direktori_jenis_peliharaan[500] = "/home/dicksen/modul2/petshop/";
                    char direktori_file_peliharaan[200] = "/home/dicksen/modul2/petshop/";
                    strcat(direktori_jenis_peliharaan,nama_folder_dan_peliharaan);
                    strcat(direktori_file_peliharaan,nama_file[i]); //Mengacu pada file gambar awal
                    pid_t proses_memindahkan_gambar = fork();
                    if(proses_memindahkan_gambar == 0){
                        char *argumen_memindahkan_gambar[] = {"cp", direktori_file_peliharaan, 
                                                            direktori_jenis_peliharaan, NULL};
                        execv("/bin/cp", argumen_memindahkan_gambar);
                    }
                }
            }
        }
```
Pada potongan kode tersebut, pertama dilakukan looping untuk memisahkan peliharaan dalam 1 foto. Setelah didapat data peliharaan apa saja yang ada didalamnya, maka bisa disalin kedalam folder.
    
    E. Mengisi "keterangan.txt" di setiap folder yang berisi nama dan umur peliharaan.
    
Pada sub-soal ini, akan dibedakan menjadi 2 bagian yaitu memasukkan foto dengan 1 peliharaan didalamnya, dan dengan lebih dari 1 peliharaan didalamnya. Untuk kasus 1 peliharaan dalam 1 gambar :
    
```c
 //Memasukkan data kedalam keterangan.txt setiap folder jenis peliharaan
        for(i = 0 ; i < banyak_file_awal ; i++){
            char *token_peliharaan; //menyimpan token file gambar
            char temp[200]; 
            strcpy(temp,nama_file[i]);


            //Jika dalam gambar terdapat satu peliharaan
            if(strchr(temp,'_')==NULL){
                token_peliharaan = strtok(temp,";");
                char jenis_peliharaan[50];
                char nama_peliharaan[50];
                char umur_peliharaan[50];
                int indeks_token = 0;
                strcpy(jenis_peliharaan,token_peliharaan);
                while(token_peliharaan!=NULL){
                    if(indeks_token == 0){
                        strcpy(jenis_peliharaan,token_peliharaan);
                    }
                    else if(indeks_token == 1){
                        strcpy(nama_peliharaan,token_peliharaan);  
                    }
                    else if(indeks_token==2){
                        strcpy(umur_peliharaan,token_peliharaan);
                        strcpy(umur_peliharaan,strtok(umur_peliharaan,"."));
                    }
                    token_peliharaan = strtok(NULL,";");
                    indeks_token++;
                }
                char direktori_jenis_peliharaan[500] = "/home/dicksen/modul2/petshop/";
                strcat(direktori_jenis_peliharaan,jenis_peliharaan);
                char keterangan[] = "/keterangan.txt";
                strcat(direktori_jenis_peliharaan,keterangan);
                FILE *fptr = fopen(direktori_jenis_peliharaan,"a+");
                if(fptr != NULL){
                    fprintf(fptr, "nama : %s\numur : %s tahun\n\n", 
                            nama_peliharaan, umur_peliharaan);
                }else perror("gagal membuka file\n");
                fclose(fptr);
            }

```

Sedangkan untuk kasus lebih dari satu peliharaan :
    
```c
 //Jika dalam gambar ada lebih dari satu peliharaan
            else if(strchr(temp,'_')!=NULL){
                token_peliharaan = strtok(temp, "_");
                char multi_peliharaan[50][200];
                int indeks_multi_peliharaan=0;
                strcpy(multi_peliharaan[0],token_peliharaan);
                while(token_peliharaan!= NULL){
                    strcpy(multi_peliharaan[indeks_multi_peliharaan],token_peliharaan);
                    if(indeks_multi_peliharaan == 0){
                        strcat(multi_peliharaan[indeks_multi_peliharaan],".jpg");
                    }
                    token_peliharaan = strtok(NULL, "_");
                    indeks_multi_peliharaan++;
                }
                
                int j;
                //Melakukan looping untuk setiap peliharaan dalam 1 file gambar
                for(j=0; j<indeks_multi_peliharaan;j++){
                    
                    strcpy(temp,multi_peliharaan[j]);
                    token_peliharaan = strtok(temp,";");
                    char jenis_peliharaan[50];
                    char nama_peliharaan[50];
                    char umur_peliharaan[50];
                    int indeks_token = 0;
                    strcpy(jenis_peliharaan,token_peliharaan);
                    //Mengambil token "jenis peliharaan" , "nama peliharaan" , dan "umur peliharaan"
                    while(token_peliharaan!=NULL){
                        if(indeks_token == 0){
                            strcpy(jenis_peliharaan,token_peliharaan);
                        }
                        else if(indeks_token == 1){
                            strcpy(nama_peliharaan,token_peliharaan);
                        }
                        else if(indeks_token == 2){
                            strcpy(umur_peliharaan,token_peliharaan);
                            strcpy(umur_peliharaan,strtok(umur_peliharaan,"."));

                        }
                        token_peliharaan = strtok(NULL,";");
                        indeks_token++;
                    }
                    char direktori_jenis_peliharaan[500] = "/home/dicksen/modul2/petshop/";
                    strcat(direktori_jenis_peliharaan,jenis_peliharaan);
                    strcat(direktori_jenis_peliharaan,"/keterangan.txt");
                   FILE *fptr = fopen(direktori_jenis_peliharaan,"a+");
                    if(fptr != NULL){
                        fprintf(fptr, "nama : %s\numur : %s tahun\n\n", 
                                nama_peliharaan, umur_peliharaan);
                    }
                    fclose(fptr);
                }
            }
        }

```

Perlu di-ingat juga bahwa kita harus menghapus file gambar pada folder utama petshop karena di tiap folder sesuai jenis peliharaan sudah terdapat halo foto peliharaan. Berikut perintahnya :
    
 ```c
  //Menghapus gambar yang berada diluar folder sesuai jenis peliharaan
        isi_petshop = opendir(path_petshop);
        if(isi_petshop != NULL){
            while((isi = readdir(isi_petshop))){
                nama_isi_petshop = isi->d_name;
                //Jika jenis file bukan directory
                if(isi->d_type != 4){
                    char hapus_file[200] = "/home/dicksen/modul2/petshop/";
                    strcat(hapus_file,nama_isi_petshop);
                    char *argumen_hapus[] = {"rm", "-f", hapus_file, NULL};
                    pid_t proses_hapus_file = fork();
                    if(proses_hapus_file == 0){
                        execv("/bin/rm",argumen_hapus);
                    }else{
                        //perror("maaf, penghapusan gagal :(\n");
                    }
                    wait(NULL);
                    
                }else{    
                    strcpy(nama_file[banyak_file_awal],nama_isi_petshop);
                    banyak_file_awal++;
                }
            }
            (void) closedir (isi_petshop);
        }else perror ("Maaf, direktori tidak dapat dibuka\n");
 
 ```


**Kendala Nomor 2:**
Dalam pengerjaan nomor 2, terdapat beberapa kendala. Terkadang ada sintaks yang perlu perhatian lebih untuk digunakan. Penggunaan library kadang juga menjadi masalah karena perlu pencarian lebih untuk mengetahui library mana yang diperlukan. 


### Soal 3
> **[soal3.c](https://github.com/billharit/soal-shift-sisop-modul-2-C10-2021/blob/main/soal3/soal3.c)**

**3a. membuat program c interval 40 detik yang membuat direktori dengan format [YYYY-mm-dd_HH:ii:ss] sesuai timestamp**
```
  while(1)
    {
        char nama[60];
        buatfolder(nama);
        
        downloadgambar(nama);
        
        
        
        sleep(40);
    }
}
```
```
void buatfolder(char nama[])
{
    int status1;
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
    while(wait(&status1)>0);
}
```
<details>
  <summary>Gambar Soal3a</summary>
    
    ![1619338861305](https://user-images.githubusercontent.com/77628684/115986516-bd298300-a5da-11eb-932c-78753fdedc7a.jpg)
    
</details>

**Penjelasan** 
* pada program utama digunakan sleep(40) untuk menghentikan program dan melanjutkannya setelah 40 detik
* pada fungsi buatfolder kita akan mengappend salah satu cara mendapatkan timestamp dengan <time.h> kita akan menggunakan strftime untuk mendapatkan string nama folder
* `char *argv[] = {"mkdir", "-p", nama, NULL};
        execv("/bin/mkdir", argv);` berfungsi untuk mengeksesuksi mkdir (membuat folder) dengan timestamp sebagai nama
        
**3b. mendownload 10 gambar setiap 5 detik dengan nama timestamp dan ukuran (n%1000) + 50 & 3c. meminta membuat status.txt dengan caesar cipher shift 5 lalu menzip direktori beserta isinya dan meremove**
```
void downloadgambar(char nama[])
{
    pid_t child_id2, child_id3;
    int status,i;
    // chdir(nama);
    child_id2 = fork();
    FILE *fp;
    if(child_id2 < 0){
      exit(EXIT_FAILURE);
    }  
    if(child_id2 == 0){

      
      for(i=1;i<=10;i++){
        
      char buffer[50];
      char namafile[100];
      time_t now;
      struct tm* timeinfo;
      time (&now);
      timeinfo = localtime (&now);
      strftime(buffer,100,"%Y-%m-%d_%H:%M:%S", timeinfo);
      sprintf(namafile,"./%s/%s.jpg",nama, buffer);
      char link[50];
      // char folder[100];
      // sprintf(folder,"/%s", buffer);
      sprintf(link,"https://picsum.photos/%ld", (now%1000) + 50);
      // printf("%s\n%s", namafile, folder);
        child_id3 = fork();
        if(child_id3 < 0){
          exit(EXIT_FAILURE);
          }  
        if(child_id3 == 0) {
          char *argv[] = {"wget", "-qO", namafile,link, NULL};
          // char *argv[] = {"wget", "-qO", namafile,link,"&&", "mv", namafile, folder, NULL};
          execv("/bin/wget", argv);
        }
        sleep(5);
      }
    
    chdir(nama);
      char statusmsg[30] = "Download Success";
      // char statusfile;
      // sprintf(statusfile,"status.txt",nama);
      // sprintf(statusfile,"./%s/status.txt",nama);
        caesar(statusmsg);
        fp = fopen("status.txt", "w");
        fprintf(fp, statusmsg);
        fclose(fp);
    chdir("..");
    
    char *zipargv[] = {"zip", "-rm", nama,nama, NULL};
    execv("/bin/zip", zipargv);

    }
        
}

```
<details>
  <summary>Gambar 3b dan 3c</summary>
    
   ![1619338891775](https://user-images.githubusercontent.com/77628684/115986595-2610fb00-a5db-11eb-8ab6-3b31a0cf96ab.jpg)
   
   ![1619339169938](https://user-images.githubusercontent.com/77628684/115986601-2f9a6300-a5db-11eb-8ddd-949eb560e17a.jpg)
   
   ![1619338925824](https://user-images.githubusercontent.com/77628684/115986603-32955380-a5db-11eb-9dbc-ee26236f0593.jpg)

    
</details>

**Penjelasan** 
* 3b
* dilakukan iterasi i=0;i<10;i++ untuk mendapatkan 10 foto dan diakhiri sleep(5) untuk menginterval selama 5 detik
* `sprintf(namafile,"./%s/%s.jpg",nama, buffer);` membuat nama file
* `sprintf(link,"https://picsum.photos/%ld", (now%1000) + 50);` mendownload file dengan ketentuan
* `char *argv[] = {"wget", "-qO", namafile,link, NULL};` untuk dilakukan exec menggunakan wget dengan
* 3c
* setelah iterasi 3b selesai dilakukan chdir(nama) pada awal line baru untuk memasuki folder
* declare string status msg isi dengan tulisan "Download Success"
* masukkan kedalam fungsi caesar dengan shift 5 untuk merubah kata download Success
* `fp = fopen("status.txt", "w");
        fprintf(fp, statusmsg);
        fclose(fp);` untuk membuat file txt dan mengappend kata yang sudah di cipher
* chdir(..) untuk kembali ke folder utama dan sekarang kita menzip seluruh folder dan isinya
* `char *zipargv[] = {"zip", "-rm", nama,nama, NULL};` untuk menzip dan remove folder

**3d & 3e. membuat fungsi killer untuk membunuh program, pada 3e diminta untuk diberi comment tambahan**

```
void Killer()
{
 
  FILE* kill;
  kill = fopen("Killer.sh", "w");
  fprintf(kill, "#!/bin/bash\nif [ \"$1\" = \"-x\" ]\nthen\n\tkill %d\n \trm \"$0\"\nelse\n\tkillall -9 soal3\n\trm \"$0\"\nfi",getpid()); 
  fclose(kill);

}
```

<details>
    <summary>Gambar 3d dan 3e</summary>
    
![1619338952144](https://user-images.githubusercontent.com/77628684/115986891-b3a11a80-a5dc-11eb-82ea-fff78d72143e.jpg)

![1619338991445](https://user-images.githubusercontent.com/77628684/115986896-b7cd3800-a5dc-11eb-9bf8-3b6b2742d2db.jpg)

![1619339028996](https://user-images.githubusercontent.com/77628684/115986898-b8fe6500-a5dc-11eb-8c0b-7dae33ad7540.jpg)

</details>

**Penjelasan**
* `FILE* kill;
  kill = fopen("Killer.sh", "w");` untuk menbuat script dan mewrite didalamnya
* `fprintf(kill, "#!/bin/bash\nif [ \"$1\" = \"-x\" ]\nthen\n\tkill %d\n \trm \"$0\"\nelse\n\tkillall -9 soal3\n\trm \"$0\"\nfi",getpid()); ` akan menghasilkan isi text script sama seperti gambar diatas
* fclose(kill) menutup pengeditan file



