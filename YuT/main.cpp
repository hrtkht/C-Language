
// �|�W�V�����F�K�[�h(G)�@�t�H���[�h(F)�@�Z���^�[(C)



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE_NAME "shoes.txt"

#define MAX_SHOES		100

#define GUARD			0
#define FORWARD			1
#define CENTER			2

typedef struct ST_shoes
{
	char maker[100];
	char name[100];
	char positionData[100];
	int lightness;
	int grip;
	int fit;
	int design;
	int cushioning;
	int performance;
	int weight;
	int position[3];
}ST_shoes;

char *StrReplace( char *String, const char *From, const char *To );
char *StrShift( char *String, size_t nShift );
void printStar(int num);

int main(void)
{
	FILE *fp_input;
	ST_shoes st_shoes[MAX_SHOES];
	int i;
	int maxData;
	char makerData[100];
	int inputMaker;
	int inputPosition;
	int hitNum = 0;
	int select;


	if ((fp_input = fopen(INPUT_FILE_NAME, "r")) == NULL)
	{
		printf("�t�@�C���J���Ȃ��ăG���[�Ȃ񂾂�\n");
		exit(2);
	}

	i = 0;
	while (
		fscanf(fp_input, "%s %s %d %d %d %d %d %d %d",
		st_shoes[i].name,			st_shoes[i].positionData,
		&st_shoes[i].lightness,	&st_shoes[i].grip,			&st_shoes[i].fit,
		&st_shoes[i].design,	&st_shoes[i].cushioning,	&st_shoes[i].performance,
		&st_shoes[i].weight) != EOF)
	{
		st_shoes[i].position[GUARD] = 0;
		st_shoes[i].position[FORWARD] = 0;
		st_shoes[i].position[CENTER] = 0;
		maxData = ++i;
	}

	for (i=0; i<maxData; ++i)
	{

		if (strcmp(st_shoes[i].positionData, "0") == 0)
		{
			strcpy(makerData, st_shoes[i].name);
			strcpy(st_shoes[i].maker, "0");
		}
		else
		{
			char *tmpAddres;
			char shose_name[100];
			if ((tmpAddres = strstr(st_shoes[i].name, "�b")) != NULL)
			{
				strcpy(shose_name, st_shoes[i].name);

				strncpy(shose_name, st_shoes[i].name, strlen(st_shoes[i].name) - strlen(tmpAddres));
				shose_name[strlen(st_shoes[i].name) - strlen(tmpAddres)] = '\0';

				strcpy(st_shoes[i].maker, shose_name);
				strcpy(st_shoes[i].name, tmpAddres + 2);
			}
			else
			{
				strcpy(st_shoes[i].maker, makerData);
			}

			sscanf(st_shoes[i].positionData, "%d,%d,%d", &st_shoes[i].position[GUARD], &st_shoes[i].position[FORWARD], &st_shoes[i].position[CENTER]);
			//printf("%d%d%d\n", st_shoes[i].position[GUARD], st_shoes[i].position[FORWARD], st_shoes[i].position[CENTER]);

		}
	}

	printf("�~�����C�̃��[�J�[����͂���(asics��0 NIKE��1 ���̑���2 �C�ɂ��Ȃ���3)�F");
	scanf("%d", &inputMaker);

	//printf("�|�W�V�����̓��͂Ɉڂ�܂�\n");

	printf("�|�W�V������I������(�K�[�h��0 �t�H���[�h��1 �Z���^�[��2 �C�ɂ��Ȃ���3)�F");
	scanf("%d", &inputPosition);

	hitNum = 0;

	for (i=0; i<maxData; ++i)
	{
		switch (inputMaker)
		{
		case 0:
			select = (strstr("asics", st_shoes[i].maker) != NULL);
			break;
		case 1:
			select = (strstr("NIKE", st_shoes[i].maker) != NULL);
			break;
		case 2:
			select = (strstr("���̑�", st_shoes[i].maker) != NULL);
			break;
		case 3:
			select = 1;
			break;
		}

		switch (inputPosition)
		{
		case 0:
			select = (select && (st_shoes[i].position[GUARD] == 1));
			break;
		case 1:
			select = (select && (st_shoes[i].position[FORWARD] == 1));
			break;
		case 2:
			select = (select && (st_shoes[i].position[CENTER] == 1));
			break;
		case 3:
			select = (select && 1);
			break;
		}

		if (select)
		{
			printf("\n%s��%s\n", st_shoes[i].maker, st_shoes[i].name);

			printf("�|�W�V����%s\n:", st_shoes [i].positionData);

			printf("27cm������̏d��%dg\n", st_shoes[i].weight);

			printf("�y�ʐ�\t\t�F");
			printStar(st_shoes[i].lightness);

			printf("�O���b�v\t�F");
			printStar(st_shoes[i].grip);

			printf("�t�B�b�g��\t�F");
			printStar(st_shoes[i].fit);

			printf("�f�U�C��\t�F");
			printStar(st_shoes[i].design);

			printf("�N�b�V���j���O\t�F");
			printStar(st_shoes[i].cushioning);

			printf("�p�t�H�[�}���X\t�F");
			printStar(st_shoes[i].performance);

			printf("\n");

			hitNum++;
		}
	}
	/*
	printf("\n\n------���[�J�[����Ȃ����ǃ|�W�V���������Ă�悱��------\n\n");
	for (i=0; i<maxData; ++i)
	{
	if (strstr(shoesTable[inputMaker], st_shoes[i].kind) == NULL &&
	st_shoes[i].position[inputPosition] == 1)
	{

	printf("\n%s��%s\n", st_shoes[i].maker, st_shoes[i].name);

	printf("27cm������̏d��%dg\n", st_shoes[i].weight);

	printf("�y�ʐ�\t\t�F");
	printStar(st_shoes[i].lightness);

	printf("�O���b�v\t�F");
	printStar(st_shoes[i].grip);

	printf("�t�B�b�g��\t�F");
	printStar(st_shoes[i].fit);

	printf("�f�U�C��\t�F");
	printStar(st_shoes[i].design);

	printf("�N�b�V���j���O\t�F");
	printStar(st_shoes[i].cushioning);

	printf("�p�t�H�[�}���X\t�F");
	printStar(st_shoes[i].performance);

	printf("\n");

	hitNum++;
	}
	}

	printf("\n\n------�|�W�V��������Ȃ����ǃ��[�J�[�����Ă�悱��------\n\n");
	for (i=0; i<maxData; ++i)
	{
	if (strstr(shoesTable[inputMaker], st_shoes[i].kind) != NULL &&
	st_shoes[i].position[inputPosition] != 1)
	{

	printf("\n%s��%s\n", st_shoes[i].maker, st_shoes[i].name);

	printf("27cm������̏d��%dg\n", st_shoes[i].weight);

	printf("�y�ʐ�\t\t�F");
	printStar(st_shoes[i].lightness);

	printf("�O���b�v\t�F");
	printStar(st_shoes[i].grip);

	printf("�t�B�b�g��\t�F");
	printStar(st_shoes[i].fit);

	printf("�f�U�C��\t�F");
	printStar(st_shoes[i].design);

	printf("�N�b�V���j���O\t�F");
	printStar(st_shoes[i].cushioning);

	printf("�p�t�H�[�}���X\t�F");
	printStar(st_shoes[i].performance);

	printf("\n");

	hitNum++;
	}
	}
	*/

	if (!hitNum)
	{
		printf("�������ʂ�������\n");
	}
	/*
	for (i=0; i<maxData; ++i)
	{

	printf("%8s%35s %3d,%d,%d %3d %3d %3d %3d %3d %3d %3d\n",
	st_shoes[i].maker, st_shoes[i].name,	st_shoes[i].position[GUARD],
	st_shoes[i].position[FORWARD], st_shoes[i].position[CENTER],
	st_shoes[i].lightness,	st_shoes[i].grip,			st_shoes[i].fit,
	st_shoes[i].design,	st_shoes[i].cushioning,	st_shoes[i].performance,
	st_shoes[i].weight);

	}
	*/
	return 0;
}

char *StrReplace( char *String, const char *From, const char *To )
{
	int   nToLen;   // �u�����镶����̒���
	int   nFromLen; // �������镶����̒���
	int   nShift;
	char *start;    // �������J�n����ʒu
	char *stop;     // ������ String �̏I�[
	char *p;

	nToLen   = strlen( To );
	nFromLen = strlen( From );
	nShift   = nToLen - nFromLen;
	start    = String;
	stop     = String + strlen( String );

	// ������ String �̐擪���當���� From ������
	while( NULL != ( p = strstr( start, From ) ) )
	{
		// ������ To �����ʂł���悤�ɂ���
		start = StrShift( p + nFromLen, nShift );
		stop  = stop + nShift;

		// ������ To �𕡎�
		memmove( p, To, nToLen );
	}

	return String;
}//StrReplace

char *StrShift( char *String, size_t nShift )
{
	char *start = String;
	char *stop  = String + strlen( String );
	memmove( start + nShift, start, stop-start+1 );

	return String + nShift;
}//StrShift

void printStar(int num)
{
	int i;
	for (i=0; i<num; ++i)
	{
		printf("��");
	}
	for (i=0; i<5-num; ++i)
	{
		printf("��");
	}
	printf("\n");
}