#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Month
{
    char name[20];
    char abr[4];
    int day;
    int number;
};

struct Month arr[12] =
{
    {.name = "January",     .abr = "Jan", .day = 31, .number = 1},
    {.name = "February",    .abr = "Feb", .day = 28, .number = 2},
    {.name = "March",       .abr = "Mar", .day = 31, .number = 3},
    {.name = "April",       .abr = "Apr", .day = 30, .number = 4},
    {.name = "May",         .abr = "May", .day = 31, .number = 5},
    {.name = "June",        .abr = "Jun", .day = 30, .number = 6},
    {.name = "July",        .abr = "Jul", .day = 31, .number = 7},
    {.name = "August",      .abr = "Aug", .day = 31, .number = 8},
    {.name = "September",   .abr = "Sep", .day = 30, .number = 9},
    {.name = "October",     .abr = "Oct", .day = 31, .number = 10},
    {.name = "November",    .abr = "Nov", .day = 30, .number = 11},
    {.name = "December",    .abr = "Dec", .day = 31, .number = 12},
};

struct Date
{
    uint16_t year;
    char month[20];
    uint8_t day;
};

int transform(struct Date *d);
int numberDay(struct Date *d);

int main(int argc, char **argv)
{
    struct Date d = {0};
    
	printf("Enter the year of interest: ");
    scanf("%d", &d.year);

    printf("Enter the month of interest: ");
    scanf("%s", d.month);
    if (!isalpha(d.month[0]))
        transform(&d);
    
    printf("Enter the day of interest: ");
    scanf("%d", &d.day);

    printf("%d - %s - %d.\n", d.year, d.month, d.day);

    printf("Days - %d\n", numberDay(&d));

	return 0;
}

int numberDay(struct Date *d)
{
    for (int i = 0; i < 12; i++)
    {
       if (strcmp(arr[i].name, d->month) == 0)
            break;
       if (i == 11)
            return -1;
    }
    
    int number = 0;
    for (int i = 0; strcmp(arr[i].name, d->month) != 0; i++)
        number += arr[i].day;

    if (d->year % 4 == 0 && number >= arr[0].day + arr[1].day)
        number++;
        
    return number + d->day;
}

int transform(struct Date *d)
{
    int numMonth = atoi(d->month);

    if (numMonth > 12 || numMonth < 1)
        return -1;
    
    strcpy(d->month, arr[numMonth - 1].name);

    return 1;
}