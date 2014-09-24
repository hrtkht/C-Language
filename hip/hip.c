#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME	"gaNma.txt"

int main(void)
{
	FILE *fp;

	int i;
	char inWord[100];
	char fileWord[100];
	int inWordLen;
	int fileWordLen;

	if ((fp = fopen(FILE_NAME, "r")) == NULL)
	{
		printf("エラーだ死ね");
		exit(2);
	}
	printf("In:");
	scanf("%s", inWord);
	do
	{
		inWordLen = strlen(inWord);
		if (memcmp((inWord + inWordLen - 2), "ん", 2) == 0)
		{
			printf("「ん」とか最後に入れるなカス氏ね\n");
			getchar();
			getchar();
			break;
		}
		//printf("%s", inWord + inWordLen-2);
		rewind(fp);
		while (fscanf(fp, "%s", fileWord) != EOF)
		{
			fileWordLen = strlen(fileWord);
			if (memcmp((inWord + inWordLen - 2), fileWord, 2) == 0)
			{
				printf("Out%s\n", fileWord);
				break;
			}
		}
		printf("In:");
		scanf("%s", inWord);
		while (memcmp((fileWord + fileWordLen - 2), inWord, 2) != 0)
		{
			printf("再入力だカス死ね:");
			scanf("%s", inWord);
		}
		
	} while(1);
	fclose(fp);

	return 0;
}