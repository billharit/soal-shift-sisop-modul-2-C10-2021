# soal-shift-sisop-modul-2-C10-2021

### KELOMPOK : C10

| **No** | **Nama** | **NRP** | 
| ------------- | ------------- | --------- |
| 1 | Dicksen Alfersius Novian  | 05111940000076 | 
| 2 | Vyra Fania Adelina  | 05111940000109 |
| 3 | Bill Harit Yafi  | 05111940000114 |


### Soal 1
> **[soal1.c](https://github.com/billharit/soal-shift-sisop-modul-2-C10-2021/blob/main/soal1/soal1.c)**


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
