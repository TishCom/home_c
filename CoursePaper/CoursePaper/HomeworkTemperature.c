#include <stdio.h>
#include <unistd.h>
#include "Sensor_Temperature.h"

#define SIZE 256
#define INPUT_FILE "F:\\C_2026_MFTI\\CoursePaper\\CoursePaper\\temperature_big.csv"

const char *NAME_MONTH[DECEMBER + 1] = 
{
    "", "JANUARY", "FEBRUARY", "MARCH", "APRIL",
    "MAY", "JUNE", "JULY", "AUGUST",
    "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
};

typedef struct
{
	bool isFill;
	char name[SIZE];
}myFile;

typedef struct
{
	uint16_t year;
	uint8_t month;
	uint32_t normalValue;
	uint32_t errValue;
	int8_t monthAvg;
	int8_t monthMax;
	int8_t monthMin;
}printData;

typedef struct
{
	uint32_t normalValue[DECEMBER];
	uint32_t errValue[DECEMBER];
}myData;

void help(void);
char* fileParam(void);
int monthParam(void);
void fopen1(FILE **pf, char *fileName, char *mode);
void fclose1(FILE *ptemp);
void scanDA(FILE *ptemp, dynamicArr *da, myData *data);
void printDA(myData *readData, dynamicArr *da, int numberMonth);
bool checkLimit(datatypeDA a);

int main(int argc, char **argv)
{
	dynamicArr info;
	FILE *ptemp;
	int rez = 0, numberMonth = 0;
	myFile fileName = {.isFill = false, .name = {0}};
	myData readData;
	
	if (argc == 1)
	{
		printf("Temp statistic application.\n");
		printf("The next time you launch the application, enter the -h key in the command line.\n");
		return 0;
	}
	
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
		return 0;

	initDynamicArr(&info);
	fopen1(&ptemp, fileName.name, "r");
	scanDA(ptemp, &info, &readData);

	printf(" # Year   Month     NuValue  ErValue  MonthAvg  MonthMax  MonthMin\n");

	for (int i = JANUARY; i <= DECEMBER; i++)
	{
		if (numberMonth == 0)
			printDA(&readData, &info, i);
		else if (numberMonth != 0)
		{
			printDA(&readData, &info, numberMonth);
			break;
		}
	}

	fclose(ptemp);
	deleteDynamicArr(&info);
	
	return 0;
}

void scanDA(FILE *ptemp, dynamicArr *da, myData *data) 
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
			pushDynamicArr(da, a);
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
	if (a.year > 2000 && a.year < 2100 && a.month > 0 && a.month < 13 && a.day > 0 && a.day < 32 
		&& a.hour < 24 && a.minute < 60 && a.temperature > -100 && a.temperature < 100)
		return true;
	
	return false;
}

void printDA(myData *readData, dynamicArr *da, int numberMonth)
{
	printData data;
	data.normalValue = readData->normalValue[numberMonth];
	data.errValue = readData->errValue[numberMonth];
	data.year = da->item[da->sp - 1].year;
	data.month = (uint8_t)numberMonth;
	data.monthAvg = (int8_t)averageMonthlyTemperature(da, (uint8_t)numberMonth);
	data.monthMax = (int8_t)maximumMonthlyTemperature(da, (uint8_t)numberMonth);
	data.monthMin = (int8_t)minimumMonthlyTemperature(da, (uint8_t)numberMonth);

	printf("%2d %4d %9s %7d %7d %8d %8d %10d\n", data.month - 1, data.year, NAME_MONTH[data.month], data.normalValue,
			data.errValue, data.monthAvg, data.monthMax, data.monthMin);
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
	printf("Month - \"%d\".\n", numberMonth);

	return numberMonth;
}