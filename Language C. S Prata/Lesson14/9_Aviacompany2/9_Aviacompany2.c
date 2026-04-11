#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_SIZE   40
#define SIZE        12
#define SIZE_FLIGHT 4

#define INOUT_FILE  "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson14\\9_Aviacompany2\\text.txt"

typedef struct passengerSeat
{
    int id;
    int booked;
    int bookingConfirmation;
    char name[NAME_SIZE];
}seat;

enum flight
{
    FLIGHT1 = 102,
    FLIGHT2 = 311,
    FLIGHT3 = 444,
    FLIGHT4 = 519,
};

void menu(int numberFlight);
void menu1(void);
char menuUp(void);
void initStruct(int string, int columns, seat passengers[string][columns]);
int numberAvailableSeat(int size, seat passengers[]);
void printAvailableSeat(int size, seat passengers[]);
void printBookedSeat(int size, seat passengers[]);
int isBookedSeat(int size, seat passengers[], int number);
int reserveSeat(int size, seat passengers[]);
int removeReserveSeat(int size, seat passengers[]);
void exitProg(void);
void fopen1(FILE **pf, char *fileName, char *mode);
void scipString(void);
int bookingSeat(int size, seat passengers[]);
int numberFlightID(int number);

int main(int argc, char **argv)
{
    seat passengers[SIZE_FLIGHT][SIZE]= {0};
    char ch = 0;
    int size = sizeof(struct passengerSeat);
    int numberFlight = 0;
    FILE *pfile;

    fopen1(&pfile, INOUT_FILE, "r+b");
    initStruct(SIZE_FLIGHT, SIZE, passengers);

    rewind(pfile);

    for (int i = 0; i < SIZE_FLIGHT; i++)
    {
        for (int y = 0; y < SIZE && fread(&passengers[i][y], size, 1, pfile) == 1; y++)
            continue;
    }
    
    while ((ch = menuUp()) != 'e')
    {
        switch (ch)
        {
            case 'a':
                numberFlight = 0;
                break;
            case 'b':
                numberFlight = 1;
                break;
            case 'c':
                numberFlight = 2;
                break;
            case 'd':
                numberFlight = 3;
        }

        menu(numberFlightID(numberFlight));
        while ((ch = getchar()) != 'g')
        {
            menu(numberFlightID(numberFlight));
            switch (ch)
            {
                case 'a':
                    printf("Available seats: %d\n", numberAvailableSeat(SIZE, passengers[numberFlight]));
                    break;
                case 'b':
                    printAvailableSeat(SIZE, passengers[numberFlight]);
                    break;
                case 'c':
                    printBookedSeat(SIZE, passengers[numberFlight]);
                    break;
                case 'd':
                    reserveSeat(SIZE, passengers[numberFlight]);
                    break;
                case 'e':
                    removeReserveSeat(SIZE, passengers[numberFlight]);
                    break;
                case 'f':
                    bookingSeat(SIZE, passengers[numberFlight]);
            }
        }
        scipString();
    }

    rewind(pfile);
    fwrite(passengers, size, SIZE_FLIGHT * SIZE, pfile);
    fclose(pfile);

	return 0;
}

int numberFlightID(int number)
{
    switch (number)
    {
        case 0:
            return FLIGHT1;
        case 1:
            return FLIGHT2;
        case 2:
            return FLIGHT3;
    }
    return FLIGHT4;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

void initStruct(int string, int columns, seat passengers[string][columns])
{
    for (int i = 0; i < string; i++)
    {
        for (int y = 0; y < columns; y++)
        {
            passengers[i][y].booked = 0;
            passengers[i][y].bookingConfirmation = 0;
            passengers[i][y].id = y + 1;
            strcpy(passengers[i][y].name, "");
        }
    }
}
void scipString(void)
{
    while (getchar() != '\n')
        continue;
}

char menuUp(void)
{
    char ch = 0;

    menu1();

    ch = getchar();
    scipString();
    while (strchr("abcde", ch) == NULL)
    {
        printf("Try again.\n");
        ch = getchar();
        scipString();
    }
    
    return ch;
}

void menu1(void)
{
    printf("TO SELECT A FUNCTION, ENTER ITS LETTER MARK:\n");
    printf("a) FLIGHT 1 - 102.\n");
    printf("b) FLIGHT 2 - 311.\n");
    printf("c) FLIGHT 3 - 444.\n");
    printf("d) FLIGHT 4 - 519.\n");
    printf("e) Exit the program.\n");
}

void menu(int numberFlight)
{
    printf("TO SELECT A FUNCTION, ENTER ITS LETTER MARK %d:\n", numberFlight);
    printf("a) Show the number of available seats.\n");
    printf("b) Show a list of available seats.\n");
    printf("c) Show the list of booked seats in ascending order.\n");
    printf("d) Reserve a seat for the passenger.\n");
    printf("e) Remove the armor from its position.\n");
    printf("f) Confirmation of the seat reservation.\n");
    printf("g) Exit the menuUp.\n");
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
        {
            printf("%d", passengers[i].id);
            if (passengers[i].bookingConfirmation == 1)
                printf("(confirmed) ");
            else    
                printf("(not confirmed) ");
        }
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

int bookingSeat(int size, seat passengers[])
{
    int number = 0;

    printBookedSeat(size, passengers);

    printf("Which one do you choose?");
    if (scanf("%d", &number) != 1 || !isBookedSeat(size, passengers, number - 1))
        return 0;
    
    number--;
    passengers[number].bookingConfirmation = 1;

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