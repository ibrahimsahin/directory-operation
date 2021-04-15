#include <stdio.h>              /* standard input/output routines.    */
#include <dirent.h>             /* readdir(), etc.                    */
#include <sys/stat.h>           /* stat(), etc.                       */
#include <string.h>             /* strstr(), etc.                     */
#include <unistd.h>             /* getcwd(), etc.                     */
#include<string.h>
#include<malloc.h>
#include <fcntl.h>
#include<time.h>
#include<sys/types.h>


#define MAX_DIR_PATH 2048

char *yol_yap(char *ek_yol,char* pattern)
{
	char * l=(char *) malloc(strlen(pattern)+strlen(ek_yol)+5);
	strcat(l,pattern);
	strcat(l,"/");
	strcat(l,ek_yol);
	return l;
}

int determine(char *aranacak,char *ek_yol)
{
	int i,j=0,control=1;
	int boy=strlen(ek_yol);
	int boy2=strlen(aranacak);
	if(strstr(ek_yol," ")==NULL && strstr(ek_yol,"ç")==NULL && strstr(ek_yol,"ş")==NULL && strstr(ek_yol,"ı")==NULL && strstr(ek_yol,"ğ")==NULL && strstr(ek_yol,"ö")==NULL && strstr(ek_yol,"ü")==NULL)
	{
		if(boy!=boy2)
			return 0;
	}
	for(i=0;i<boy2+1;i++)
	{
			if(aranacak[i]==63)
			{
				if( (ek_yol[j]==-59 && ek_yol[j+1]==-97) || (ek_yol[j]==-61 && ek_yol[j+1]==-89) || (ek_yol[j]==-60 && ek_yol[j+1]==-97) || (ek_yol[j]==-60 && ek_yol[j+1]==-79) || (ek_yol[j]==-61 && ek_yol[j+1]==-74) || (ek_yol[j]==-61 && ek_yol[j+1]==-68))
				{
					j++;
				}
				j++;
				continue;
			}

			if(aranacak[i]!=ek_yol[j])
			{
				control=0;
				break;
			}
			j++;
		}

	return control;
}

char *yol_duzelt(int ek_yol_boy,char * ek_yol, char *pattern)
{
	int pattern_boy=strlen(pattern);
	char * l=(char *) malloc(pattern_boy-ek_yol_boy);
	strncpy (l,pattern,pattern_boy-ek_yol_boy-1);
	char *k=yol_yap(ek_yol,l);
	return k;
}
void copy(char *ek_yol,char * pattern)
{
	char *l;
	char * pch=(char *) malloc(strlen(ek_yol));
	strcpy(pch,ek_yol);
	if(strstr(ek_yol," ")==NULL && strstr(ek_yol,"ç")==NULL && strstr(ek_yol,"ş")==NULL && strstr(ek_yol,"ı")==NULL && strstr(ek_yol,"ğ")==NULL && strstr(ek_yol,"ö")==NULL && strstr(ek_yol,"ü")==NULL)
		return;

	int ek_yol_boy=strlen(pch);
	while(strstr(pch," ")!=NULL || strstr(pch,"ç")!=NULL || strstr(pch,"ş")!=NULL || strstr(pch,"ı")!=NULL || strstr(pch,"ğ")==NULL || strstr(pch,"ö")!=NULL || strstr(pch,"ü")!=NULL)
	{

		int i=0,j=0;
		for(i=0;i<strlen(ek_yol)+1;i++)
		{
			if(ek_yol[i]==-59 && ek_yol[i+1]==-97)//ş karakteri
			{
				pch[j]=115;
				j++;
				i++;
				continue;
			}
			if(ek_yol[i]==-61 && ek_yol[i+1]==-89)//ç
			{
				pch[j]=99;
				j++;
				i++;
				continue;
			}
			if(ek_yol[i]==-60 && ek_yol[i+1]==-97)//ğ
			{
				pch[j]=103;
				j++;
				i++;
				continue;
			}
			if(ek_yol[i]==-60 && ek_yol[i+1]==-79)//ı
			{
				pch[j]=105;
				j++;
				i++;
				continue;
			}
			if(ek_yol[i]==-61 && ek_yol[i+1]==-74)//ö
			{
				pch[j]=111;
				j++;
				i++;
				continue;
			}
			if(ek_yol[i]==-61 && ek_yol[i+1]==-68)//ü
			{
				pch[j]=117;
				j++;
				i++;
				continue;
			}
			if(ek_yol[i]==32)
			{
				pch[j]=95;
				j++;
				continue;
			}

			pch[j]=ek_yol[i];
			j++;
		}
		l=yol_duzelt(ek_yol_boy,pch,pattern);
		break;
	}

	printf("%s\n",l);
	rename(pattern,l);
}

int update(char *ek_yol,char* pattern)
{
	int control = open(pattern, O_RDWR);
	if(control==-1)
	{
			DIR* dir;
			dir=opendir(pattern);
			struct dirent* entry;
			while ( (entry = readdir(dir)) != NULL)
			{
				if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
					continue;
				char * l=yol_yap(entry->d_name,pattern);
				update(entry->d_name,l);
			}
		return 1;
	}
	else
	{
		copy(ek_yol,pattern);
	}
	close(control);
	return 0;
}

int delete(char *ek_yol,char* pattern,char *aranacak){

	int aynimi=determine(aranacak,ek_yol);
	int control = open(pattern, O_RDWR);
	if(control==-1)
	{
		if(aynimi==1)
		{
			printf("%s\n", pattern);
			DIR* dir;
			dir=opendir(pattern);
			struct dirent* entry;
			while ( (entry = readdir(dir)) != NULL)
			{
				if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
					continue;
				char * l=yol_yap(entry->d_name,pattern);
				delete(entry->d_name,l,entry->d_name);
			}
		}

		return 1;
	}
	else
	{
		if(aynimi==1)
		{
				printf("%s\n", pattern);
				unlink(pattern);
		}
	}

	close(control);
	return 0;
}


int search(char *ek_yol,char* pattern,char *aranacak)
{

	int aynimi=determine(aranacak,ek_yol);

	int control = open(pattern, O_RDWR);
	if(control==-1)
	{
		if(aynimi==1)
			printf("%s\n", pattern);
		return 1;
	}
	else
	{
		if(aynimi==1)
			printf("%s\n", pattern);
	}

	close(control);
	return 0;
}

int list(char *ek_yol,char* pattern)
{
	int k=0;
	int control= open(pattern, O_RDWR);
	if(control==-1)
	{
		printf("< %s>\n", ek_yol);
		return 1;
	}
	else
		printf("---%s\n", ek_yol);

	close(control);
	return k;
}

void menu(char *komut,char * pattern,char *aranacak)
{
	DIR* dir;
	dir=opendir(pattern);
	struct dirent* entry;
	while ( (entry = readdir(dir)) != NULL)
	{
		if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
			continue;
		char * l=yol_yap(entry->d_name,pattern);
		if(strcmp(komut,"-u")==0)
		{
			int k=update(entry->d_name,l);
			if(k==1)
			{
				menu(komut,l,NULL);
				copy(entry->d_name,l);
			}
		}
		else if(strcmp(komut,"-l")==0)
		{
			int k=list(entry->d_name,l);
			if(k==1)
				menu(komut,l,NULL);
		}
		else if(strcmp(komut,"-s")==0)
		{
			int k=search(entry->d_name,l,aranacak);
			if(k==1)
				menu(komut,l,aranacak);
		}
		else if(strcmp(komut,"-d")==0)
		{
			int k=delete(entry->d_name,l,aranacak);
			if(k==1)
			{
				menu(komut,l,aranacak);
				rmdir(l);
			}
		}
	}
}
void arrange(char **argc)
{
	if(strcmp(argc[1],"-u")==0)
		menu(argc[1],argc[2],NULL);
	else if(strcmp(argc[1],"-l")==0)
		menu(argc[1],argc[2],NULL);
	else if(strcmp(argc[1],"-s")==0)
		menu(argc[1],argc[3],argc[2]);
	else if(strcmp(argc[1],"-d")==0)
		menu(argc[1],argc[3],argc[2]);
}
int main(int arg,char **argc)
{
    arrange(argc);
    return 0;
}

