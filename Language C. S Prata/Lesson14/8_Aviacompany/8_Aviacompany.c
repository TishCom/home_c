#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_SIZE   40
#define SIZE        12

#define INOUT_FILE  "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson14\\8_Aviacompany\\text.txt"

typedef struct passengerSeat
{
    int id;
    int booked;
    char name[NAME_SIZE];
}seat;

void menu(void);
void initStruct(int size, seat passengers[]);
int numberAvailableSeat(int size, seat passengers[]);
void printAvailableSeat(int size, seat passengers[]);
void printBookedSeat(int size, seat passengers[]);
int isBookedSeat(int size, seat passengers[], int number);
int reserveSeat(int size, seat passengers[]);
int removeReserveSeat(int size, seat passengers[]);
void exitProg(void);
void fopen1(FILE **pf, char *fileName, char *mode);

int main(int argc, char **argv)
{
    seat passengers[SIZE]= {0};
    char ch = 0;
    int size = sizeof(struct passengerSeat);
    FILE *pfile;

    fopen1(&pfile, INOUT_FILE, "r+b");
    initStruct(SIZE, passengers);

    rewind(pfile);

    for (int i = 0; i < SIZE && fread(&passengers[i], size, 1, pfile) == 1; i++)
        continue;

    menu();
    while ((ch = getchar()) != 'f')
    {
        menu();
        switch (ch)
        {
            case 'a':
                printf("Available seats: %d\n", numberAvailableSeat(SIZE, passengers));
                break;
            case 'b':
                printAvailableSeat(SIZE, passengers);
                break;
            case 'c':
                printBookedSeat(SIZE, passengers);
                break;
            case 'd':
                reserveSeat(SIZE, passengers);
                break;
            case 'e':
                removeReserveSeat(SIZE, passengers);
        }
    }

    rewind(pfile);
    fwrite(passengers, size, SIZE, pfile);
    fclose(pfile);

	return 0;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

void initStruct(int size, seat passengers[])
{
    for (int i = 0; i < size; i++)
    {
        passengers[i].booked = 0;
        passengers[i].id = i + 1;
        strcpy(passengers[i].name, "");
    }
}

void menu(void)
{
    printf("TO SELECT A FUNCTION, ENTER ITS LETTER MARK:\n");
    printf("a) Show the number of available seats.\n");
    printf("b) Show a list of available seats.\n");
    printf("c) Show the list of booked seats in ascending order.\n");
    printf("d) Reserve a seat for the passenger.\n");
    printf("e) Remove the armor from its position.\n");
    printf("f) Exit the program.\n");
}

int numberAvailableSeat(int size, seat passengers[])
{
    int number = 0;
    for (int i = 0; i < size; i++)
    {
        if (passengers[i].booked == 0)
            number++;
    }
    
    return number;
}

void printAvailableSeat(int size, seat passengers[])
{
    printf("There are available seats: ");
    for (int i = 0; i < size; i++)
    {
        if (passengers[i].booked == 0)
            printf("%d ", passengers[i].id);
    }
    printf(".\n");
}

void printBookedSeat(int size, seat passengers[])
{
    printf("There are booked seats: ");
    for (int i = 0; i < size; i++)
    {
        if (passengers[i].booked == 1)
            printf("%d ", passengers[i].id);
    }
    printf(".\n");
}

int isBookedSeat(int size, seat passengers[], int number)
{
    if (number < 0 || number > size - 1)
        return -1;
    
    return passengers[number].booked;
}

int reserveSeat(int size, seat passengers[])
{
    int number = 0;

    printAvailableSeat(size, passengers);

    printf("Which one do you choose?");
    if (scanf("%d", &number) != 1 || isBookedSeat(size, passengers, number - 1))
        return 0;
    
    number--;
    printf("Tell me your name: ");
    scanf("%s", passengers[number].name);
    passengers[number].booked = 1;

    return number;
}

int removeReserveSeat(int size, seat passengers[])
{
    int number = 0;

    printf("Which place did you book?");
    if (scanf("%d", &number) != 1 || !isBookedSeat(size, passengers, number - 1))
        return 0;
        
    number--;
    strcpy(passengers[number].name, "");
    passengers[number].booked = 0;

    return number;
}

void exitProg(void)
{
    exit(1);
}