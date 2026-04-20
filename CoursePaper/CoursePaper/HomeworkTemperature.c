#include <stdio.h>
#include <unistd.h>
#include "Sensor_Temperature.h"

#define SIZE 256

const char *NAME_MONTH[DECEMBER + 1] = 
{
    "", "JANUARY", "FEBRUARY", "MARCH", "APRIL",
    "MAY", "JUNE", "JULY", "AUGUST",
    "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
};

typedef struct
{
	uint32_t normalValue[DECEMBER + 1];
	uint32_t errValue[DECEMBER + 1];
}myData;

enum
{
	MIN_YEAR 	= 2000,
	MAX_YEAR 	= 2100,
	MIN_MONTH 	= 0,
	MAX_MONTH 	= 13,
	MIN_DAY 	= 0,
	MAX_DAY 	= 32,
	MAX_HOUR 	= 24,
	MAX_MINUTE 	= 60,
	MIN_TEMP 	= -100,
	MAX_TEMP 	= 100
};

void help(void);
char* fileParam(void);
int monthParam(void);
void fopen1(FILE **pf, char *fileName, char *mode);
void fclose1(FILE *ptemp);
void readFile(FILE *ptemp, dynamicArr *da, myData *data);
void myPrint(myData *readData, dynamicArr *da, int numberMonth);
bool checkLimit(datatypeDA a);
void formatPrint(myData *readData, dynamicArr *da, int numberMonth);
void readCommandLine(int argc, char **argv, char *fileName, int *numberMonth);

int main(int argc, char **argv)
{
	dynamicArr info;
	FILE *ptemp;
	int numberMonth = 0;
	char fileName[SIZE] = {0};
	myData readData;
	
	if (argc == 1)
	{
		printf("Temp statistic application.\n");
		printf("The next time you launch the application, enter the \"-h\" key in the command line.\n");
		return 0;
	}

	readCommandLine(argc, argv, fileName, &numberMonth);
	
	if (strlen(fileName) == 0)
		return 0;

	initDynamicArr(&info);
	fopen1(&ptemp, fileName, "r");

	readFile(ptemp, &info, &readData);
	formatPrint(&readData, &info, numberMonth);

	fclose(ptemp);
	deleteDynamicArr(&info);
	return 0;
}

void readCommandLine(int argc, char **argv, char *fileName, int *numberMonth)
{
	int rez = 0;

	while ((rez = getopt(argc,argv,"hf:m:")) != -1)
    {
        switch (rez)
        {
            case 'h':
				help(); 
				break;
            case 'f':
				strcpy(fileName, fileParam());
				break;
            case 'm':
				*numberMonth = monthParam();
				break;
            case '?':
				printf("Error found!\n");
        }
    }
}

void formatPrint(myData *readData, dynamicArr *da, int numberMonth)
{
	printf(" # Year   Month     NuValue  ErValue  MonthAvg  MonthMax  MonthMin\n");

	if (numberMonth != 0)
	{
		myPrint(readData, da, numberMonth);
		return;
	}

	for (int i = JANUARY; i <= DECEMBER; i++)
		myPrint(readData, da, i);
}

void readFile(FILE *ptemp, dynamicArr *da, myData *data) 
{
	datatypeDA a;
	char buffer[SIZE];
	int month = JANUARY;
	uint32_t normalData = 0, allData = 0;
    
    for (int numberString = 0, scan = 0; fgets(buffer, sizeof(buffer), ptemp) != NULL; numberString++)
    {
        scan = sscanf(buffer, "%hd;%hhd;%hhd;%hhd;%hhd;%hhd", &a.year, &a.month, &a.day, &a.hour, &a.minute, &a.temperature);

		if (a.month != month)
		{
			data->normalValue[month] = normalData;
			data->errValue[month] = allData - normalData;
			month = a.month;
			normalData = 0;
			allData = 0;
		}

		if (scan == 6 && checkLimit(a))
		{
			addingData(da, a);
			normalData++;
		}
		else
			printf("Fail read string №%d - %s\n", numberString, buffer);

		allData++;
    }

	data->normalValue[DECEMBER] = normalData;
	data->errValue[DECEMBER] = allData - normalData;
}

bool checkLimit(datatypeDA a)
{
	if (a.year > MIN_YEAR && a.year < MAX_YEAR && a.month > MIN_MONTH && a.month < MAX_MONTH && a.day > MIN_DAY
		&& a.day < MAX_DAY && a.hour < MAX_HOUR && a.minute < MAX_MINUTE && a.temperature > MIN_TEMP && a.temperature < MAX_TEMP)
		return true;
	
	return false;
}

void myPrint(myData *readData, dynamicArr *da, int numberMonth)
{
	printf("%2d %4d %9s %7d %7d %8d %8d %10d\n", numberMonth - 1, da->item[da->sp - 1].year, NAME_MONTH[numberMonth],
		readData->normalValue[numberMonth], readData->errValue[numberMonth], (int8_t)averageMonthlyTemperature(da, (uint8_t)numberMonth),
		maximumMonthlyTemperature(da, (uint8_t)numberMonth), minimumMonthlyTemperature(da, (uint8_t)numberMonth));
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open file - %s\n", fileName);
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
	printf("Temp statistic application.\n");
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

	if (numberMonth < 1)
		numberMonth = 1;
	else if (numberMonth > 12)
		numberMonth = 12;
	
	printf("Month - \"%d\".\n", numberMonth);

	return numberMonth;
}