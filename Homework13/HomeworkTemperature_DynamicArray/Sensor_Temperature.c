#include "Sensor_Temperature.h"

int returnIndexMonth(datatypeDA *info, uint8_t month)
{
    int index = 0;
    while (info[index].month < month)
        index++;
    
    return index;
}

void shiftLeftArr(datatypeDA arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
        arr[i] = arr[i + 1];

    arr[size - 1] = (datatypeDA){.day = 0, .hour = 0, .minute = 0, .month = 0, .year = 0, .temperature = 0};
}

int compareDate(const void *pa, const void *pb)
{
    datatypeDA *a = (datatypeDA*)pa;
    datatypeDA *b = (datatypeDA*)pb;

    if (a->year != b->year)
        return a->year - b->year;
    else if (a->month != b->month)
        return a->month - b->month;
    else if (a->day != b->day)
        return a->day - b->day;
    else if (a->hour != b->hour)
        return a->hour - b->hour;
    else
        return a->minute - b->minute;
}

int compareTemperature(const void *pa, const void *pb)
{
    return ((datatypeDA*)pa)->temperature - ((datatypeDA*)pb)->temperature;
}

int dayInMonth(dynamicArr *da, uint8_t month)
{
    int index = returnIndexMonth(da->item, month), day = 0;
    while (da->item[index + day].month == month && index + day < da->sp)
        day++;
    
    return day;
}

float averageMonthlyTemperature(dynamicArr *da, uint8_t month)
{
    if (month > DECEMBER || month < JANUARY)
        return MY_ERROR;
    
    float sumTemperature = 0;
    int day = 0;
    for (int i = returnIndexMonth(da->item, month); da->item[i].month == month && i < da->sp; i++)
    {
        sumTemperature += da->item[i].temperature;
        day++;
    }

    // for (int i = 0; i < size; i++)
    // {
    //     if (info[i].month == month)
    //     {
    //         sumTemperature += info[i].temperature;
    //         day++;
    //     }
    // }
    
    return day == 0 ? 0 : sumTemperature / (float)day;
}

int minimumMonthlyTemperature(dynamicArr *da, uint8_t month)
{
    if (month > DECEMBER || month < JANUARY)
        return MY_ERROR;

    int min = PRIMARY_MINIMUM;
    for (int i = returnIndexMonth(da->item, month); da->item[i].month == month && i < da->sp; i++)
    {
        if (min > da->item[i].temperature)
            min = da->item[i].temperature;
    }
        
    return min;
}

int maximumMonthlyTemperature(dynamicArr *da, uint8_t month)
{
    if (month > DECEMBER || month < JANUARY)
        return MY_ERROR;

    int max = PRIMARY_MAXIMUM;
    for (int i = returnIndexMonth(da->item, month); da->item[i].month == month && i < da->sp; i++)
    {
        if (max < da->item[i].temperature)
            max = da->item[i].temperature;
    }
        
    return max;
}

float averageYearTemperature(dynamicArr *da)
{
    float sumTemperature = 0;
    for (uint8_t i = JANUARY; i <= DECEMBER; i++)
        sumTemperature += averageMonthlyTemperature(da, i);
    
    return sumTemperature / DECEMBER;
}

int minimumYearTemperature(dynamicArr *da)
{
    int min = PRIMARY_MINIMUM, minMonth = 0;
    for (uint8_t i = JANUARY; i <= DECEMBER; i++)
    {
        minMonth = minimumMonthlyTemperature(da, i);
        if (min > minMonth)
            min = minMonth;
    }
    
    return min;
}

int maximumYearTemperature(dynamicArr *da)
{
    int max = PRIMARY_MAXIMUM, maxMonth = 0;
    for (uint8_t i = JANUARY; i <= DECEMBER; i++)
    {
        maxMonth = maximumMonthlyTemperature(da, i);
        if (max < maxMonth)
            max = maxMonth;
    }
    
    return max;
}

int addingData(dynamicArr *da, datatypeDA data)
{
    pushDynamicArr(da, data);
    
    return da->sp;
}

int deleteData(int tergetDelete, dynamicArr *da)
{
    tergetDelete--;

    if (tergetDelete >= da->sp || tergetDelete < 0)
        return MY_ERROR;

    shiftLeftArr(da->item + tergetDelete, da->sp - tergetDelete);
    popDynamicArr(da);
    
    return da->sp;
}

int fillArrSensor(dynamicArr *da)
{
    pushDynamicArr(da, (datatypeDA) {.day = 1, .hour = 1, .minute = 23, .month = 1, .temperature = -20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 2, .hour = 2, .minute = 32, .month = 1, .temperature = -10, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 3, .hour = 5, .minute = 33, .month = 1, .temperature = -12, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 4, .hour = 8, .minute = 22, .month = 1, .temperature = -15, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 5, .hour = 4, .minute = 56, .month = 1, .temperature = -18, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 11, .hour = 12, .minute = 23, .month = 1, .temperature = -5, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 2, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 3, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 4, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 5, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 20, .hour = 12, .minute = 23, .month = 9, .temperature = 37, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 6, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 7, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 8, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 9, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 10, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 11, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 10, .hour = 12, .minute = 23, .month = 12, .temperature = 20, .year = 2026});
    pushDynamicArr(da, (datatypeDA) {.day = 15, .hour = 12, .minute = 23, .month = 6, .temperature = 2, .year = 2026});

    return da->sp;
}

void printArrSensor(dynamicArr *da)
{
    for (int i = 0; i < da->sp; i++)
        printf("%4d - %2d - %2d - %2d - %2d - %3dC\n", da->item[i].year, da->item[i].month, da->item[i].day, da->item[i].hour, da->item[i].minute, da->item[i].temperature);
}

void sortDate(dynamicArr *da)
{
    qsort(da->item, (size_t)da->sp, sizeof(datatypeDA), compareDate);
}

void sortTemperature(dynamicArr *da)
{
    qsort(da->item, (size_t)da->sp, sizeof(datatypeDA), compareTemperature);
}