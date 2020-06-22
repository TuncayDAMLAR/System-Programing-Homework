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
    char cumle[100], sesliHarfler[100];
    int len = 0, child,bekle,status, sbayrak = 0,say=0;
    char sesliHarf[10] = {'a', 'e', 'i', 'u', 'o', 'A', 'E', 'I', 'U', 'O'};
    len = read(STDIN_FILENO, cumle, 100);//standart cikistan veri okundu
    child = fork();
    if (child != 0){ // parent
	    for (int i = 0; i < len; i++){//kelimenin harflerini gez
		    for (int j = 0; j < 10; j++){//Sesli harfleri gezin
		        if (cumle[i] == sesliHarf[j])//harflerde sesli harf var mi
		        {
		            sbayrak = 1;
		        }
		    }
		    if(sbayrak == 0) //sesli harf bayragı 0 sa ekrana yaz
		    {
		        printf("%c", cumle[i]);	        
		    }
		    sbayrak = 0;
		}
    }
    else//chil ise
    {
		bekle = wait(&status);//sesliharf dizisi degiskenlerine aynı anda erismemeleri icin
		for (int i = 0; i < len; i++){
	        for (int j = 0; j < 10; j++){
	            if (cumle[i] == sesliHarf[j])
	            {
			    sesliHarfler[say]=cumle[i];
			    say++;
	            }
	        }
	    }
	    len = write(5, sesliHarfler, say);//5 nolu dosya tanimlayıcısına yazdır.
			return 0;
    }
}
