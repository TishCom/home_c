#include <stdio.h>
#include <string.h>

#define CSIZE 4
#define GSIZE 3

struct name
{
    char firstName[30];
    char lastName[30];
};

struct student
{
    struct name people;
    float grade[GSIZE];
    float average;
};

void input(int numberStudent, int sizeGrade, struct student arr[]);
void inputAll(int numberStudent, int sizeGrade, struct student arr[]);
float average(int sizeGrade, struct student a);
void averageAll(int numberStudent, int sizeGrade, struct student arr[]);
void printAll(int numberStudent, struct student arr[]);
void printAverageAll(int numberStudent, struct student arr[]);

int main(int argc, char **argv)
{
	struct student arr[CSIZE] = 
    {
        {.people.firstName = "Nick", .people.lastName = "Free"},
        {.people.firstName = "Nick1", .people.lastName = "Free1"},
        {.people.firstName = "Nick2", .people.lastName = "Free2"},
        {.people.firstName = "Nick3", .people.lastName = "Free3"}
    };

    inputAll(CSIZE, GSIZE, arr);
    averageAll(CSIZE, GSIZE, arr);
    printAll(CSIZE, arr);
    printAverageAll(CSIZE, arr);

	return 0;
}

void printAverageAll(int numberStudent, struct student arr[])
{
    float average[4] = {0};
    for (int  y = 0; y < numberStudent; y++)
    {
        average[0] += arr[y].grade[0];
        average[1] += arr[y].grade[1];
        average[2] += arr[y].grade[2];
        average[3] += arr[y].average;
    }

    for (int i = 0; i < 4; i++)
        average[i] /= 4;

    for (int i = 0; i < 4; i++)
        printf("%d)%.2f ", i + 1, average[i]);

    printf("\n");
}

void printAll(int numberStudent, struct student arr[])
{
    for (int  i = 0; i < numberStudent; i++)
        printf("%s %s: %.2f\n", arr[i].people.firstName, arr[i].people.lastName, arr[i].average);
}

void averageAll(int numberStudent, int sizeGrade, struct student arr[])
{
    for (int  i = 0; i < numberStudent; i++)
        arr[i].average = average(sizeGrade, arr[i]);
}

float average(int sizeGrade, struct student a)
{
    float sum = 0;
    for (int  i = 0; i < sizeGrade; i++)
        sum += a.grade[i];
    
    return sum / sizeGrade;
}

void inputAll(int numberStudent, int sizeGrade, struct student arr[])
{
    for (int  i = 0; i < numberStudent; i++)
        input(numberStudent, sizeGrade, arr);
}

void input(int numberStudent, int sizeGrade, struct student arr[])
{
    char name[30] = {0};

    printf("Name?\n");
    scanf("%s", name);

    for (int  i = 0; i < numberStudent; i++)
    {
        if (strcmp(arr[i].people.firstName, name) == 0)
        {
            printf("Grade?\n");
            for (int y = 0; y < sizeGrade; y++)
                scanf("%f", &arr[i].grade[y]);
            break;
        }
    }
}