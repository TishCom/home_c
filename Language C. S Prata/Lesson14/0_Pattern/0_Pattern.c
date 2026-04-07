#include <stdio.h>

struct Month
{
    char name[20];
    char abr[4];
    int day;
    int number;
};

int numberDay(struct Month arr[], int month);

int main(int argc, char **argv)
{
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

	printf("%s - %s - %d - %d.\n", arr[0].name, arr[0].abr, arr[0].day, arr[0].number);
    printf("%d\n", numberDay(arr, 3));

	return 0;
}

int numberDay(struct Month arr[], int month)
{
    int number = 0;
    for (int i = 0; arr[i].number < month; i++)
        number += arr[i].day;
        
    return number;
}