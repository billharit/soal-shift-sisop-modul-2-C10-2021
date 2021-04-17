#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>

int main()
{
    pid_t child1 = fork();
    char nama_file[200][200]; //menyimpan nama dari setiap file gambar hewan
    int banyak_file_awal=0;
    // Proses di-eksekusi kedua
    if (child1 == 0) {
        // sleep the process for 1 second
        sleep(1);
        printf("2nd CHILD\n");

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
        }else perror ("Maaf, direktori tidak dapat dibuka\n");
        
        sleep(1);
        
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

        sleep(1);

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

        sleep(1);

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

        sleep(1);

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

        sleep(1);

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
    }
  
    // Proses pertama yang di-eksekusi
    else {
        //EKSTRAK File .zip
        
        char *argv[]= {"unzip", "pets.zip", "-d", "/home/dicksen/modul2/petshop", NULL};
        execv("/bin/unzip",argv);
        
        
    }
  
    return 0;
}
