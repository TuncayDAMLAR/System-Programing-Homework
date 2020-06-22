#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	struct stat buf;
	int exists;
	DIR *d;
	struct dirent *de;

	d = opendir(argv[1]);
	if (d == NULL){
		fprintf(stderr, "Dosya Acilamadi \n");
		exit(1);
	}
	for (de = readdir(d); de != NULL; de = readdir(d))//dizini null olana kadar oku
	{
		exists = stat(de->d_name, &buf);
		if ((buf.st_mode & S_IRUSR) && (buf.st_mode & S_IWUSR) && !(buf.st_mode & S_IXUSR) 
		&& !(buf.st_mode & S_IRGRP) && !(buf.st_mode & S_IWGRP) && !(buf.st_mode & S_IXGRP) 
		&& !(buf.st_mode & S_IROTH) && !(buf.st_mode & S_IWOTH) && !(buf.st_mode & S_IXOTH))
		{
			if (de->d_type != DT_DIR || !strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){
				continue;//eger klasör degilse pas gec
			}
			else{
				printf("Dosya Adi = %s ", de->d_name);
				printf("Dosya Yetkisi: \t");
				printf("drw-------");
				printf(" Kullanici Okuma/Yazma izinli");
				printf("\n\n");
			}
		}
	}
	closedir(d);
}

