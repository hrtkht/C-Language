#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define FOLDER_PATH "e\\"

typedef struct ST_file
{
	char name[256];
	char newName[256];
	char path[256];
	char newPath[256];
	char extension[256];
	char kind[256];
	long fileSize;
	int rank;
}ST_file;

int setFileData(ST_file *st_fileData, struct dirent *dp);
void Rank(ST_file *st_fileData, int maxData);

int main(void)
{

	DIR *dir;
	struct dirent *dp;
	
	ST_file st_fileData[100];
	
	int i = 0;
	int maxData;
	
	
	dir = opendir(FOLDER_PATH);
	
	maxData = 0;
	for(dp=readdir(dir);dp!=NULL;dp=readdir(dir))
	{
		if (i >= 2)
		{
			setFileData(&st_fileData[i-2], dp);
			maxData = i - 1;
		}
		i++;
	}
	
	Rank(st_fileData, maxData);
	
	for (i=0; i<maxData; ++i)
	{
		char num[100];
		printf("%sの変更後の名前", st_fileData[i].name);
		scanf("%s", st_fileData[i].newName);
		
		/*
		sprintf(num, "%02d_", st_fileData[i].rank);
		strcpy(st_fileData[i].newPath, FOLDER_PATH);
		
		strcat(st_fileData[i].newPath, num);
		strcat(st_fileData[i].newPath, st_fileData[i].newName);
		strcat(st_fileData[i].newPath, ".");
		strcat(st_fileData[i].newPath, st_fileData[i].extension);
		*/
		
		sprintf(st_fileData[i].newPath, "%s%s_%03d_%s%s%s", 
			FOLDER_PATH,
			st_fileData[i].kind,
			st_fileData[i].rank,
			st_fileData[i].newName,
			".",
			st_fileData[i].extension);
		
		rename(st_fileData[i].path, st_fileData[i].newPath);
	}
	

	
	for (i=0; i<maxData; ++i)
	{
		printf("ファイルの名前  %s\n", st_fileData[i].name);
		printf("新しい名前      %s\n", st_fileData[i].newName);
		printf("ファイルのpath  %s\n", st_fileData[i].path);
		printf("新しいパス      %s\n", st_fileData[i].newPath);
		printf("拡張子          %s\n", st_fileData[i].extension);
		printf("サイズ（バイト）%dbyte\n", st_fileData[i].fileSize);
		printf("ランク          %d\n\n", st_fileData[i].rank);
	}
	
	closedir(dir);
	return 0;
}

int setFileData(ST_file *st_fileData, struct dirent *dp)
{
	FILE *fp;
	char *p;
	
	// ファイルの名前を入力
	strcpy(st_fileData->name, dp->d_name);
	
	// 拡張子を除く
	while ((p = strstr(st_fileData->name, strchr(dp->d_name, '.'))) != NULL)
	{
		*p = '\0';
	}
	
	// ファイルパスを入力
	strcpy(st_fileData->path, FOLDER_PATH);
	strcat(st_fileData->path, dp->d_name);
	
	// サイズを入力
	if ((fp = fopen(st_fileData->path, "rb")) == NULL)
	{
		printf("%s開けないわ", st_fileData->path);
		return -1;
	}
	fseek(fp, 0, SEEK_END);
	
	st_fileData->fileSize = ftell(fp);
	
	// 拡張子を入力
	strcpy(st_fileData->extension, (strchr(dp->d_name, '.') + 1));
	
	fclose(fp);
	
	// 種類を入力
	if (strstr(st_fileData->extension, "mp3") || 
		strstr(st_fileData->extension, "wav"))
	{
		strcpy(st_fileData->kind, "音楽");
	}
	else if (strstr(st_fileData->extension, "avi") || 
			strstr(st_fileData->extension, "mp4"))
	{
		strcpy(st_fileData->kind, "動画");
	}
	else if (strstr(st_fileData->extension, "jpg"))
	{
		strcpy(st_fileData->kind, "写真");
	}
	else
	{
		strcpy(st_fileData->kind, "その他");
	}
	return 0;
}

void Rank(ST_file *st_fileData, int maxData)
{
	int i, j;
	for (i=0; i<maxData; ++i)
	{
		st_fileData[i].rank = 1;
	}
	
	for (i=0; i<maxData; ++i)
	{
		for (j=0; j<maxData; ++j)
		{
			if (st_fileData[i].fileSize < st_fileData[j].fileSize)
			{
				st_fileData[i].rank++;

			}
		}	
	}
	
	for (i=0; i<maxData; ++i)
	{
		for (j=0; j<maxData; ++j)
		{
			if ((st_fileData[i].rank == st_fileData[j].rank) && (i != j))
			{
				st_fileData[j].rank++;
			}
		}
	}
}