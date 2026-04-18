#include <stdio.h>
#include <unistd.h>
#include "Sensor_Temperature.h"

#define SIZE 256
#define INPUT_FILE "F:\\C_2026_MFTI\\CoursePaper\\CoursePaper\\temperature_big.csv"

typedef struct
{
	bool isFill;
	char name[SIZE];
}myFile;

void help(void);
char* fileParam(void);
int monthParam(void);
void fopen1(FILE **pf, char *fileName, char *mode);
void fclose1(FILE *ptemp);
void scanDA(FILE *ptemp, dynamicArr *da);
bool checkLimit(datatypeDA a);

int main(int argc, char **argv)
{
	dynamicArr info;
	FILE *ptemp;
	int rez = 0, numberMonth = 0;
	myFile fileName = {.isFill = false, .name = {0}};

	while ((rez = getopt(argc,argv,"hf:m:")) != -1)
    {
        switch (rez)
        {
            case 'h':
				help(); 
				break;
            case 'f':
				strcpy(fileName.name, fileParam());
				fileName.isFill = true;
				break;
            case 'm':
				numberMonth = monthParam();
				break;
            case '?':
				printf("Error found!\n");
        }
    }

	if (fileName.isFill == false)
		strcpy(fileName.name, INPUT_FILE);

	initDynamicArr(&info);
	fopen1(&ptemp, fileName.name, "r");
	scanDA(ptemp, &info);

	if (numberMonth == 0)
	{
		numberMonth = 1;

		printf("Average year temperature - %.2f\n", averageYearTemperature(&info));
		printf("Minimum year temperature - %d\n", minimumYearTemperature(&info));
		printf("Maximum year temperature - %d\n", maximumYearTemperature(&info));
	}
	
	printf("Average month(%d) temperature - %.2f\n", numberMonth, averageMonthlyTemperature(&info, (uint8_t)numberMonth));
	printf("Minimum month(%d) temperature - %d\n", numberMonth, minimumMonthlyTemperature(&info, (uint8_t)numberMonth));
	printf("Maximum month(%d) temperature - %d\n", numberMonth, maximumMonthlyTemperature(&info, (uint8_t)numberMonth));

	fclose(ptemp);
	deleteDynamicArr(&info);
	
	return 0;
}

void scanDA(FILE *ptemp, dynamicArr *da) 
{
	datatypeDA a;
	char buffer[SIZE];
    
    for (int numberString = 0, scan = 0; fgets(buffer, sizeof(buffer), ptemp) != NULL; numberString++)
    {
        scan = sscanf(buffer, "%hd;%hhd;%hhd;%hhd;%hhd;%hhd", &a.year, &a.month, &a.day, &a.hour, &a.minute, &a.temperature);
		
        if (scan == 6 && checkLimit(a))
            pushDynamicArr(da, a);
        else
            printf("Fail read string №%d - %s\n", numberString, buffer);
    }
}

bool checkLimit(datatypeDA a)
{
	if (a.year > 2000 && a.year < 2100 && a.month > 0 && a.month < 13 && a.day > 0 && a.day < 32 
		&& a.hour < 24 && a.minute < 60 && a.temperature > -100 && a.temperature < 100)
		return true;
	
	return false;
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

char* fileParam(void)
{
	char *fileName = optarg;
	printf("File - \"%s\".\n", fileName);

	return fileName;
}

int monthParam(void)
{
	int numberMonth = atoi(optarg);
	printf("Month - \"%d\".\n", numberMonth);

	return numberMonth;
}