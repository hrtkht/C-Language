#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COUNTRY	0
#define CITY	1

// #define DEBUG

typedef struct ST_country
{
	char name[300];
	double standardTime;
	int cityNum;
}ST_country;

typedef struct ST_timelag
{
	int yearLag;
	int monLag;
	int dayLag;
	int hourLag;
	int minLag;
	double gmtLag;
}ST_timelag;

typedef struct ST_japantime
{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
}ST_japantime;

double match_country(ST_country *st_country, char *country, int maxCountry, int search);
double match_city(ST_country *st_country, int maxCountry, int maxCity);
void getTimeLag(ST_timelag *timeLag, ST_japantime jpTime, double standardTime);
int YesOrNo();

int main(void)
{
	FILE *f_country;
	ST_country st_country[100];
	char country[100] = {0};
	int i;
	int maxCountry = 0;
	double standardTime;
	ST_timelag timeLag;
	ST_japantime jpTime;

	time_t timer;
	struct tm *t_st;

	if ((f_country = fopen("COUNTRY.txt", "a+")) == NULL)
	{
		printf("ふぁいるえらー\n");
		exit(2);
	}

	i=0;
	while (fscanf(f_country, "%s%lf", &st_country[i].name, &st_country[i].standardTime) != EOF )
	{
		i++;
		st_country[i].cityNum = -1;
	}

	maxCountry = i;

	printf("どこの国：");
	scanf("%s", country);

	time(&timer);
	t_st = localtime(&timer);

#ifdef DEBUG
	jpTime.year	= 2011;
	jpTime.mon	= 3;
	jpTime.day	= 1;
	jpTime.hour	= 1;
	jpTime.min	= 29;
	jpTime.sec	= t_st->tm_sec;
#else 
	jpTime.year	= 1900 + t_st->tm_year;
	jpTime.mon	= t_st->tm_mon + 1;
	jpTime.day	= t_st->tm_mday;
	jpTime.hour	= t_st->tm_hour;
	jpTime.min	= t_st->tm_min;
	jpTime.sec	= t_st->tm_sec;
#endif

	standardTime = match_country(&st_country[0], country, maxCountry, COUNTRY);
	if (standardTime == -100)
	{
		standardTime = match_country(&st_country[0], country, maxCountry, CITY);
	}
	if (standardTime == 100)
	{
		printf("検索結果はありませんでした\n");
		printf("この国をリストに追加しますか？ Yes:1 No:0 ");
		if (YesOrNo())
		{
			double newCountryTimeLag;
			printf("検索したかったのは州や地域ですか？ Yes:1 No:0 ");
			if (YesOrNo())
			{
				char city[100];
				printf("州または地域の名前を入力してください：");
				scanf("%s", city);
				sprintf(country, "%s_%s", country, city);
			}
			else
			{
				;

			}
			printf("その国のGMT(グリニッジ標準時)を入力してください：");
			scanf("%lf", &newCountryTimeLag);
			fprintf(f_country, "%s %lf\n", country, newCountryTimeLag);
		}
	}
	else
	{
		getTimeLag(&timeLag, jpTime, standardTime);
		printf("向こうは%4d年%2d月%2d日%2d時%2d分\n", timeLag.yearLag, timeLag.monLag, timeLag.dayLag, timeLag.hourLag, timeLag.minLag);
	}

	fclose(f_country);
	return 0;
}

double match_country(ST_country *st_country, char *country, int maxCountry, int search)
{
	int i;
	int maxCity = 0;

	for (i=0; i<maxCountry; ++i)
	{
		if (strncmp(st_country[i].name, country, strlen(country)) == 0)
		{
			//if (*(st_country[i].name + strlen(country)) == '\0')
			if (strlen(country)[st_country[i].name] == '\0')
			{
				// HIT
				if (search == COUNTRY)
				{
					return st_country[i].standardTime;
				}
			}
			else if (*(st_country[i].name + strlen(country)) == '_')
			{

				if (search == CITY)
				{
					maxCity++;
					printf("%d:%s\n", maxCity, st_country[i].name + strlen(country) + 1);
					st_country[i].cityNum = maxCity;
				}
				else if (search == COUNTRY)
				{
					return -100;
				}

			}
			else
			{
				// インド→インドネシア的な
				//return 100;
			}
			//printf("%ca\n", *(st_country[i].name + strlen(country)));

		}
		else
		{
			// なんもひっかからない
			//return 100;
		}
	}
	if (search == CITY)
	{
		return match_city(&st_country[0], maxCountry, maxCity);
	}
	return 100;
}

double match_city(ST_country *st_country, int maxCountry, int maxCity)
{
	int i;
	int city;
	printf("\n何番の州??：");
	scanf("%d", &city);
	for (i=0; i<maxCountry; ++i)
	{
		if (st_country[i].cityNum == city)
		{
			return st_country[i].standardTime;
		}
		else if (i == maxCountry - 1)
		{
			return 100;
		}
	}
	return 100;
}

void getTimeLag(ST_timelag *timeLag, ST_japantime jpTime, double standardTime)
{
	timeLag->gmtLag = -(9 - standardTime);
		timeLag->yearLag = 0;
		timeLag->monLag = 0;
		timeLag->dayLag = 0;
		timeLag->hourLag = 0;
		timeLag->minLag = 0;
		//printf("\nグリニッジ標準時%.2f\n", standardTime);
		//printf("現地からの時差%.2f\n", timeLag->gmtLag);
		printf("　日本は%2d年%2d月%2d日%2d時%2d分\n",jpTime.year, jpTime.mon, jpTime.day, jpTime.hour, jpTime.min);

		timeLag->minLag = (int)(((double)timeLag->gmtLag - (int)timeLag->gmtLag) * 60 + jpTime.min);

		if (timeLag->minLag < 0)
		{
			timeLag->minLag = 60 + timeLag->minLag;
			timeLag->hourLag = -1;
		}
		else if (timeLag->minLag >= 60)
		{
			timeLag->minLag = timeLag->minLag - 60;
			timeLag->hourLag = +1;
		}

		timeLag->hourLag += (int)timeLag->gmtLag + jpTime.hour;

		if (timeLag->hourLag < 0)
		{
			timeLag->hourLag = 24 + timeLag->hourLag;
			timeLag->dayLag = -1;
		}
		else if (timeLag->hourLag >= 24)
		{
			timeLag->hourLag = timeLag->hourLag - 24;
			timeLag->dayLag = +1;
		}

		timeLag->dayLag += jpTime.day;
		switch(jpTime.mon)
		{

		case 5:
		case 7:	
		case 10:
		case 12:
			if (timeLag->dayLag <= 0)
			{
				timeLag->dayLag = 30;
				timeLag->monLag = -1;
			}
			else if (timeLag->dayLag > 31)
			{
				timeLag->dayLag = 1;
				timeLag->monLag = +1;
			}
			break;

		case 1:
		case 8:
			if (timeLag->dayLag <= 0)
			{
				timeLag->dayLag = 31;
				timeLag->monLag = -1;
			}
			else if (timeLag->dayLag > 31)
			{
				timeLag->dayLag = 1;
				timeLag->monLag = +1;
			}
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			if (timeLag->dayLag <= 0)
			{
				timeLag->dayLag = 31;
				timeLag->monLag = -1;
			}
			else if (timeLag->dayLag > 30)
			{
				timeLag->dayLag = 1;
				timeLag->monLag = +1;
			}
			break;

		case 2:
			if (timeLag->dayLag <= 0)
			{
				timeLag->dayLag = 31;
				timeLag->monLag = -1;
			}
			if (jpTime.year % 400 == 0 || (jpTime.year % 4 == 0 && jpTime.year % 100 != 0))
			{
				if (timeLag->dayLag > 29)
				{
					timeLag->dayLag = 1;
					timeLag->monLag = +1;
				}
				
			}
			else
			{
				if (timeLag->dayLag > 28)
				{
					timeLag->dayLag = 1;
					timeLag->monLag = +1;
				}
			}
			break;

		case 3:
			if (timeLag->dayLag <= 0)
			{
				if (jpTime.year % 400 == 0 || (jpTime.year % 4 == 0 && jpTime.year % 100 != 0))
				{
					timeLag->dayLag = 29;
				}
				else
				{
					timeLag->dayLag = 28;
				}
				timeLag->monLag = -1;
			}
			else if (timeLag->dayLag > 31)
			{
				timeLag->dayLag = 1;
				timeLag->monLag = +1;
			}

			break;
		}

		timeLag->monLag += jpTime.mon;
		if (timeLag->monLag <= 0)
		{
			timeLag->monLag = 12;
			timeLag->yearLag = -1;
		}
		else if (timeLag->monLag >= 13)
		{
			timeLag->monLag = 1;
			timeLag->yearLag = +1;
		}
		timeLag->yearLag += jpTime.year;
}

int YesOrNo()
{
	int x;
	scanf("%d", &x);
	return x;
}