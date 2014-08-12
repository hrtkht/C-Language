#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 20
#define MAX_DATA_STRING 100



char csvData[MAX_DATA][MAX_DATA_STRING];

typedef struct Addres
{
	char addres[100];
	char prefecture[100];
	char city[100];
	char area[100];
}S_addres;

void GetCsv(char *buf, S_addres *addres);

int main(void)
{
	FILE *f_csv, *f_out;
	int i, j;
	char addres[20];
	char buf[256];
	char *p_start;
	int addLen;
	int conFlag = 0;
	S_addres addresData;

	if ((f_csv = fopen("KEN_ALL.CSV", "r")) == NULL)
	{
		printf("‚Ó‚Ÿ‚¢‚é‚Ð‚ç‚¯‚Ë‚¥...\n");
		exit(2);
	}

	if ((f_out = fopen("ZŠ.txt", "w")) == NULL)
	{
		printf("‚ ‚¤‚Æ‚Õ‚Á‚Æ‚Ó‚Ÿ‚¢‚é‚Ð‚ç‚¯‚Ë‚¥‚ñ‚¾‚¯‚Ç...\n");
		exit(2);
	}

	do
	{
		rewind(f_csv);
		printf("—X•Ö”Ô†F");
		scanf("%s", &addres);
		addLen = strlen(addres);

		while (1)
		{
			p_start = fgets(buf, 256, f_csv);             // 1Úº°ÄÞ“Ç‚Þ
			if ( p_start == NULL )
				break;             // EOF

			GetCsv(buf, &addresData);                  // €–Ú‚ðŽæ‚èo‚·

			if ( memcmp(&addresData.addres,addres,addLen)!=0 )
				continue;                     // —X•Ö”Ô†‚ª‚¿‚ª‚¤

			printf("\nZŠ:%s%s%s\n",addresData.prefecture, addresData.city,addresData.area);
			fprintf(f_out, "—X•Ö”Ô†:%s\nZŠ:%s%s%s\n\n", addres, addresData.prefecture, addresData.city, addresData.area);
			//printf("%s", &csvData[9][0]);
			break;
		}
		printf("\n‘±s‚·‚é? Yes:1 No:0 ");

	} while (scanf("%d", &conFlag) && conFlag);
	fclose(f_csv);
	fclose(f_out);
	return 0;
}

void GetCsv(char *buf, S_addres *addres)
{
	char *p_start;
	char *p_end;
	int strLen;
	int i;

	p_start = buf;

	memset(addres->prefecture, '\0', MAX_DATA_STRING);
	memset(addres->city, '\0', MAX_DATA_STRING);
	memset(addres->area, '\0', MAX_DATA_STRING);
	for (i=0; i<9; i++)
	{
		if (*p_start == '\"')
			p_start++;

		p_end = strstr(p_start, ",");

		if (p_end == NULL)
			break;

		strLen = p_end - p_start;

		if (*(p_end - 1) == '\"')
			strLen--;

		if (strLen > 0)
		{
			switch (i)
			{
			case 2:
				memcpy(addres->addres, p_start, strLen);
				break;
			case 6:
				memcpy(addres->prefecture, p_start, strLen);
				break;
			case 7:
				memcpy(addres->city, p_start, strLen);
				break;
			case 8:
				memcpy(addres->area, p_start, strLen);
				break;
			default:
				break;
			}
		}
		p_start = p_end + 1;
	}

	//strcpy(&csvData[i][0], p_start);
}
