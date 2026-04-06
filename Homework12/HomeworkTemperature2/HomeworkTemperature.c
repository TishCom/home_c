#include <stdio.h>
#include <unistd.h>
#include "Sensor_Temperature.h"

#define SIZE 200

void help(void);
void fileParam(void);
void monthParam(void);

int main(int argc, char **argv)
{
	sensor_readings info[SIZE] ={0};
	char rez=0;

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
	
	return 0;
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