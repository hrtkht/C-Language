#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE_NAME "test.txt"

typedef struct ST_spot
{
	char prefectura[100];
	char summer[100];
	char winter[100];

}ST_spot;

int setSpot(ST_spot *st_spot, FILE *fp_input);
void inputSpotData(char *in_prefectura, int *in_season);
int inputContinue(void);
void printSpot(ST_spot st_spot, char *in_prefectura, int in_season);

int main(void)
{
	FILE *fp_input;
	ST_spot st_spot[50];
	int i;
	int maxData;
	char in_prefectura[100];
	int in_season;

	if ((fp_input = fopen(INPUT_FILE_NAME, "r")) == NULL)
	{
		printf("�t�@�C���J���Ȃ��ăG���[�Ȃ񂾂�\n");
		exit(2);
	}

	maxData = setSpot(st_spot, fp_input);

	do
	{
		rewind(fp_input);	// �t�@�C����擪�ɖ߂�

		inputSpotData(in_prefectura, &in_season);

		for (i=0; i<=maxData; ++i)
		{
			printSpot(st_spot[i], in_prefectura, in_season);
		}
	} while (inputContinue());

	fclose(fp_input);

	return 0;
}

// �z��̍ő�v�f����Ԃ�
int setSpot(ST_spot *st_spot, FILE *fp_input)
{
	int i;
	for (i=0; (fscanf(fp_input, "%s%s%s", st_spot[i].prefectura, st_spot[i].summer, st_spot[i].winter) != EOF) && i<50; ++i)
		;
	return (i - 1);
}

// �������
void inputSpotData(char *in_prefectura, int *in_season)
{
	char buf[256];

	printf("������͂��Ă��������F");

	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%s", in_prefectura);

	do 
	{
		printf("�Ă��~��I�����Ă������� (0=�� 1=�~)�F");

		fgets(buf, sizeof(buf), stdin);
		sscanf(buf, "%d", in_season);

	} while ((*in_season) != 1 && (*in_season) != 0);
}

int inputContinue(void)
{
	char buf[256];
	int x;
	printf("���s���܂���(Yes=0�ȊO No=0)�F");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d", &x);

	return x;
}

void printSpot(ST_spot st_spot, char *in_prefectura, int in_season)
{

	if (strcmp(in_prefectura, st_spot.prefectura) == 0)
	{
		if (in_season == 0)
		{
			printf("%s\n", st_spot.summer);
		}
		else
		{
			printf("%s\n", st_spot.winter);
		}
	}
}