#include <stdio.h>
#include <inttypes.h>

struct Name
{
    char firstName[30];
    char patronymic[30];
    char lastName[30];
};

struct People
{
    uint32_t number;
    struct Name name;
};

void printStruct(struct People *a);
void printStruct1(struct People a);

int main(int argc, char **argv)
{
	struct People arr[5] = 
    {
        {.number = 123456789, .name.firstName = "Hefed", .name.lastName = "Jefnj", .name.patronymic = "Kschd"},
        {.number = 123456789, .name.firstName = "Hefed", .name.lastName = "nhjyj"},
        {.number = 123456789, .name.firstName = "Hefed", .name.lastName = "awsfesa", .name.patronymic = "Kschd"},
        {.number = 123456789, .name.firstName = "Hefed", .name.lastName = "Jefnj", .name.patronymic = "vbnbv"},
        {.number = 123456789, .name.firstName = "etwr", .name.lastName = "Jefnj"},
    };

    for (int i = 0; i < 5; i++)
        printStruct1(arr[i]);

	return 0;
}

void printStruct(struct People *a)
{
    char ch = 0;
    if (a->name.patronymic[0] == '\0')
        ch = '\0';
    else 
        ch = '.';
        
    printf("%s, %s %c%c -- %d\n", a->name.lastName, a->name.firstName, a->name.patronymic[0], ch, a->number);
}

void printStruct1(struct People a)
{
    char ch = 0;
    if (a.name.patronymic[0] == '\0')
        ch = '\0';
    else 
        ch = '.';
        
    printf("%s, %s %c%c -- %d\n", a.name.lastName, a.name.firstName, a.name.patronymic[0], ch, a.number);
}