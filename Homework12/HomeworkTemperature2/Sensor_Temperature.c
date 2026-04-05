#include "Sensor_Temperature.h"

int returnIndexMonth(sensor_readings info[], uint8_t month)
{
    int index = 0;
    while (info[index].month < month)
        index++;
    
    return index;
}

void shiftLeftArr(sensor_readings arr[], int size)
{
	for (int i = 0; i < size; i++)
        arr[i] = arr[i + 1];

    arr[size] = (sensor_readings){.day = 0, .hour = 0, .minute = 0, .month = 0, .year = 0, .temperature = 0};
}

int compareDate(const void *pa, const void *pb)
{
    sensor_readings *a = (sensor_readings*)pa;
    sensor_readings *b = (sensor_readings*)pb;

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
    return ((sensor_readings*)pa)->temperature - ((sensor_readings*)pb)->temperature;
}

int dayInMonth(int size, sensor_readings info[], uint8_t month)
{
    int index = returnIndexMonth(info, month), day = 0;
    while (info[index + day].month == month && index + day < size)
        day++;
    
    return day;
}

float averageMonthlyTemperature(int size, sensor_readings info[], uint8_t month)
{
    if (month > DECEMBER || month < JANUARY)
        return ERROR;
    
    float sumTemperature = 0;
    int day = 0;
    for (int i = returnIndexMonth(info, month); info[i].month == month && i < size; i++)
    {
        sumTemperature += info[i].temperature;
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

int minimumMonthlyTemperature(int size, sensor_readings info[], uint8_t month)
{
    if (month > DECEMBER || month < JANUARY)
        return ERROR;

    int min = PRIMARY_MINIMUM;
    for (int i = returnIndexMonth(info, month); info[i].month == month && i < size; i++)
    {
        if (min > info[i].temperature)
            min = info[i].temperature;
    }
        
    return min;
}

int maximumMonthlyTemperature(int size, sensor_readings info[], uint8_t month)
{
    if (month > DECEMBER || month < JANUARY)
        return ERROR;

    int max = PRIMARY_MAXIMUM;
    for (int i = returnIndexMonth(info, month); info[i].month == month && i < size; i++)
    {
        if (max < info[i].temperature)
            max = info[i].temperature;
    }
        
    return max;
}

float averageYearTemperature(int size, sensor_readings info[])
{
    float sumTemperature = 0;
    for (int i = JANUARY; i <= DECEMBER; i++)
        sumTemperature += averageMonthlyTemperature(size, info, i);
    
    return sumTemperature / DECEMBER;
}

int minimumYearTemperature(int size, sensor_readings info[])
{
    int min = PRIMARY_MINIMUM, minMonth = 0;
    for (int i = JANUARY; i <= DECEMBER; i++)
    {
        minMonth = minimumMonthlyTemperature(size, info, i);
        if (min > minMonth)
            min = minMonth;
    }
    
    return min;
}

int maximumYearTemperature(int size, sensor_readings info[])
{
    int max = PRIMARY_MAXIMUM, maxMonth = 0;
    for (int i = JANUARY; i <= DECEMBER; i++)
    {
        maxMonth = maximumMonthlyTemperature(size, info, i);
        if (max < maxMonth)
            max = maxMonth;
    }
    
    return max;
}

int addingData(int size, int amountAvailableData, sensor_readings info[], sensor_readings data)
{
    if (amountAvailableData >= size)
        return ERROR;

    info[amountAvailableData].day = data.day;
    info[amountAvailableData].hour = data.hour;
    info[amountAvailableData].minute = data.minute;
    info[amountAvailableData].month = data.month;
    info[amountAvailableData].temperature = data.temperature;
    info[amountAvailableData].year = data.year;
    
    return ++amountAvailableData;
}

int deleteData(int size, int amountAvailableData, sensor_readings info[])
{
    amountAvailableData--;

    if (amountAvailableData >= size || amountAvailableData < 0)
        return ERROR;

    shiftLeftArr(info + amountAvailableData, size - amountAvailableData);
    
    return --size;
}

int fillArrSensor(int size, sensor_readings info[])
{
    int number = 0;
    addingData(size, number++, info, (sensor_readings) {.day = 1, .hour = 1, .minute = 23, .month = 1, .temperature = -20, .year = 2026});
    addingData(size, number++, info, (sensor_readings) {.day = 2, .hour = 2, .minute = 32, .month = 1, .temperature = -10, .year = 2026});
    addingData(size, number++, info, (sensor_readings) {.day = 3, .hour = 5, .minute = 33, .month = 1, .temperature = -12, .year = 2026});
    addingData(size, number++, info, (sensor_readings) {.day = 4, .hour = 8, .minute = 22, .month = 1, .temperature = -15, .year = 2026});
    addingData(size, number++, info, (sensor_readings) {.day = 5, .hour = 4, .minute = 56, .month = 1, .temperature = -18, .year = 2026});
    addingData(size, number++, info, (sensor_readings) {.day = 11, .hour = 12, .minute = 23, .month = 1, .temperature = -5, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 2, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 3, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 4, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 5, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 20, .hour = 12, .minute = 23, .month = 9, .temperature = 37, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 6, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 7, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 8, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 9, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 10, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 11, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 10, .hour = 12, .minute = 23, .month = 12, .temperature = 20, .year = 2026});
	addingData(size, number++, info, (sensor_readings) {.day = 15, .hour = 12, .minute = 23, .month = 6, .temperature = 2, .year = 2026});

    return number;
}

void printArrSensor(int amountAvailableData, sensor_readings info[])
{
    for (int i = 0; i < amountAvailableData; i++)
        printf("%4d - %2d - %2d - %2d - %2d - %3dC\n", info[i].year, info[i].month, info[i].day, info[i].hour, info[i].minute, info[i].temperature);
}

void sortDate(int size, sensor_readings info[])
{
    qsort(info, size, sizeof(sensor_readings), compareDate);
}

void sortTemperature(int size, sensor_readings info[])
{
    qsort(info, size, sizeof(sensor_readings), compareTemperature);
}