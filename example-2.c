#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int childpid;
    int fib_sum = 0, file, temp, bekle, status, sz, seekp, fd[2], val = 0;

    pipe(fd);          //fd icin pipe olusturuldu  0-Oku, 1-Yaz
    childpid = fork(); //cocuk process olusturuldu
    if (childpid != 0) // parent ise
    {
        bekle = wait(&status); //child prosess icin bekle
        close(fd[1]);//pipe icin yazmayı kapa
        read(fd[0], &val, sizeof(val));
        file = open("orn.txt", O_WRONLY | O_CREAT, 0666);
        if (file < 0)
        {
            perror("r1");
            exit(1);
        }
        lseek(file, 0, SEEK_END); //DOSYANIN SONUNA GIT
        char dizi[10];
        sprintf(dizi, "%d", val);
        sz = write(file, dizi, strlen(dizi));
        close(file);

        close(fd[0]); // okumayı kapat
    }
    else // child ise
    {
        close(fd[0]);

        char buffer[100], kelime[100][100];
        int len = 0;
        len = read(STDIN_FILENO, buffer, 100);
        int i = 0, j = 0, k = 0, bKontrol = -1;
        for (i = 0; i < len - 1; i++) { //enter karakteride dahil oldugu icin -1
            if (buffer[i] == ' '){ //birden fazla bosluk olma durumu icin kontroller
                if ((i - 1 > 0 && buffer[i - 1] != ' ') && (i + 1 < len - 1 && buffer[i + 1] != ' '))
                    {
                        kelime[j][k] = '\0';
                        j++;
                        k = 0;
                    }
                else if ((i - 1 > 0 && buffer[i - 1] != ' ') && (i + 1 < len - 1 && buffer[i + 1] == ' '))
                    {
                        kelime[j][k] = '\0';
                        j++;
                        k = 0;
                    }
            }
            else//bosluk degil ise harfi ekle
            {
                kelime[j][k] = buffer[i];
                k++;
            }
        }

        char ayni[100][100];
        int aynisay = 0, ayniuz, aynisi = 0;

        for (i = 0; i < j + 1; i++) {
            for (int k = i + 1; k < j + 1; k++){
                if (!strcmp(kelime[i], kelime[k])){ //kelimeler birbiriyle karsilastirildi
                    aynisi = 0;
                    for (int n = 0; n < aynisay; n++) //eger ayni ise kelime dizinde var mi
                        {
                            if (!strcmp(kelime[i], ayni[n])){ aynisi = 1;}
                        }
                    if (aynisi == 0)
                    { //eger ayni kelime dizinde yoksa diziye at
                        strcpy(ayni[aynisay], kelime[i]);
                  
                        aynisay++;
                    }
                }
            }
        }
        fib_sum = aynisay;
        // degeri yazma tanimlayicisinda gonder:
        write(fd[1], &fib_sum, sizeof(fib_sum));
        close(fd[1]);
        return fib_sum;
    }
}
