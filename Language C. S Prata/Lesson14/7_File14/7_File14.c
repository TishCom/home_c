#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS  100

#define FILE_INPUT  "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson14\\7_File14\\book.txt"

// #define DEBAG

struct book
{
    char title[MAXTITL];
    char author[MAXAUTL];
    int is_deleted;
    float value;
};

char* s_gets(char *st, int n);
void fopen1(FILE **pf, char *fileName, char *mode);
void shiftLeftArr(struct book arr[], int size);
int deleteData(int size, int deleteElement, struct book info[]);
int numberTitle(char *title, int size, struct book info[]);
void changeData(struct book *a);

int main(int argc, char **argv)
{
	struct book library[MAXBKS];
    int count = 0, index, filecount;
    int size = sizeof(struct book);
    int numberChange = 0;
    char nameChange[MAXTITL] = {0};
    FILE *pbooks;

    fopen1(&pbooks, FILE_INPUT, "r+b");
    rewind(pbooks);

    while (count < MAXBKS && fread(&library[count], size, 1, pbooks) == 1)
    {
        if (count == 0)
            puts("The current contents of the file book.txt:");
        if (library[count].is_deleted == 0)
        {
            printf("%s autor %s: $%.2f\n", library[count].title, library[count].author, library[count].value);
            count++;
        }
    }

    printf("Enter the book you want to delete.\n");
    printf("Press [Enter] at the beginning of a line to finish typing.\n");
    while (s_gets(nameChange, MAXTITL) != NULL && nameChange[0] != '\0')
    {
        numberChange = numberTitle(nameChange, count, library);
        count = deleteData(count, numberChange, library);
        fseek(pbooks, numberChange * size, SEEK_SET);
        fwrite(library + numberChange, size, count - numberChange + 1, pbooks);
        printf("Enter the book you want to delete.\n");
    }

    printf("Enter the book you want to change.\n");
    printf("Press [Enter] at the beginning of a line to finish typing.\n");
    while (s_gets(nameChange, MAXTITL) != NULL && nameChange[0] != '\0')
    {
        numberChange = numberTitle(nameChange, count, library);
        changeData(&library[numberChange]);
        fseek(pbooks, numberChange * size, SEEK_SET);
        fwrite(library + numberChange, size, 1, pbooks);
        printf("Enter the book you want to change.\n");
    }

    filecount = count;
    if (count == MAXBKS)
    {
        puts("The file book.txt is full.");
        exit(2);
    }

    printf("Enter the name of the book.\n");
    printf("Press [Enter] at the beginning of a line to finish typing.\n");
    while (count < MAXBKS && s_gets(library[count].title, MAXTITL) != NULL && library[count].title[0] != '\0')
    {
        library[count].is_deleted = 0;
        printf("Now enter the author's full name.\n");
        s_gets(library[count].author, MAXTITL);
        printf("Now enter the price.\n");
        scanf("%f", &library[count++].value);
        while (getchar() != '\n')
            continue;
        if (count < MAXBKS)
            printf("Enter the name of the book.\n");
    }
    
    if (count > 0)
    {
        printf("Catalog of your books:\n");

        for (int i = 0; i < count; i++)
            printf("%s - %s: %.2f\n", library[i].title, library[i].author, library[i].value);
        printf("\n");

        fseek(pbooks, filecount * size, SEEK_SET);
        fwrite(&library[filecount], size, count - filecount, pbooks);
    }
    else
        printf("No books at all? That's too bad.\n");

    fclose(pbooks);

	return 0;
}

int numberTitle(char *title, int size, struct book info[])
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(info[i].title, title) == 0)
            return i;
    }
    
    return -1;
}

int deleteData(int size, int deleteElement, struct book info[])
{
    if (deleteElement >= size || deleteElement < 0)
        return -1;

    shiftLeftArr(info + deleteElement, size - deleteElement);
    
    return --size;
}

void changeData(struct book *a)
{
    a->is_deleted = 0;
    printf("Enter the name of the book.\n");
    s_gets(a->title, MAXTITL) != NULL;
    printf("Now enter the author's full name.\n");
    s_gets(a->author, MAXTITL);
    printf("Now enter the price.\n");
    scanf("%f", &a->value);
    while (getchar() != '\n')
            continue;
}

void shiftLeftArr(struct book arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
        arr[i] = arr[i + 1];

    arr[size - 1] = (struct book){.author = "", .title = "", .value = 0, .is_deleted = 1};
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    
    return ret_val;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}