#include <stdio.h>
#include <unistd.h>
#include "Sensor_Temperature.h"

#define SIZE 200
#define INPUT_FILE "F:\\C_2026_MFTI\\Lesson13\\HomeworkTemperature3\\temperature_big.csv"
// #define INPUT_FILE "F:\\C_2026_MFTI\\Lesson13\\HomeworkTemperature3\\temperature_big1.txt"

void help(void);
void fileParam(void);
void monthParam(void);
void fopen1(FILE **pf, char *fileName, char *mode);
void fclose1(FILE *ptemp);
void scanDA(FILE *ptemp, dynamicArr *da);

int main(int argc, char **argv)
{
	dynamicArr info;
	FILE *ptemp;
	int rez = 0;

	initDynamicArr(&info);
	fopen1(&ptemp, INPUT_FILE, "r");
	scanDA(ptemp, &info);

    while ((rez = getopt(argc,argv,"hf:m:")) != -1)
    {
        switch (rez)
        {
            case 'h':
				help(); 
				break;
            case 'f':
				fileParam();
				break;
            case 'm':
				monthParam();
				break;
            case '?':
				printf("Error found!\n");
        }
    }

	for (int i = 0; info.sp > 0; i++)
	{
		printf("%d %d %d %d %d %d\n", info.item[i].year, info.item[i].month, info.item[i].day, info.item[i].hour, info.item[i].minute, info.item[i].temperature);
		popDynamicArr(&info);
	}
	
	fclose1(ptemp);
	deleteDynamicArr(&info);
	
	return 0;
}

void scanDA(FILE *ptemp, dynamicArr *da) 
{
	datatypeDA a;
	
	while (fscanf(ptemp, "%hd;%hhd;%hhd;%hhd;%hhd;%hhd", &a.year, &a.month, &a.day, &a.hour, &a.minute, &a.temperature) == 6)
		pushDynamicArr(da, a);
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "%s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

void fclose1(FILE *ptemp)
{
    if (fclose(ptemp) == EOF)
		printf("fail close\n");
	else
		printf("normal close\n");
}

void help(void)
{
	printf("Help.\n");
	printf("Description of the application functionality.\n");
	printf("Parameters:\n");
	printf("1)h - help\n");
	printf("2)f - file source\n");
	printf("3)m - month\n");
	printf("4)other - error\n");
}

void fileParam(void)
{
	printf("File - \"%s\".\n", optarg);
}

void monthParam(void)
{
	printf("Month - \"%s\".\n", optarg);
}