#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS  100

#define FILE_INPUT  "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson14\\7_File14\\book.txt"

struct book
{
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};

char* s_gets(char *st, int n);
void fopen1(FILE **pf, char *fileName, char *mode);
void shiftLeftArr(struct book arr[], int size);
int deleteData(int size, int deleteElement, struct book info[]);

int main(int argc, char **argv)
{
	struct book library[MAXBKS];
    int count = 0, index, filecount;
    int size = sizeof(struct book);
    FILE *pbooks;

    fopen1(&pbooks, FILE_INPUT, "r+b");
    rewind(pbooks);

    while (count < MAXBKS && fread(&library[count], size, 1, pbooks) == 1)
    {
        if (count == 0)
            puts("The current contents of the file book.txt:");
        printf("%s autor %s: $%.2f\n", library[count].title, library[count].author, library[count].value);
        count++;
    }

    count = deleteData(count, 2, library);

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

        fwrite(&library[filecount], size, count - filecount, pbooks);
    }
    else
        printf("No books at all? That's too bad.\n");
    
	return 0;
}

int deleteData(int size, int deleteElement, struct book info[])
{
    deleteElement--;

    if (deleteElement >= size || deleteElement < 0)
        return -1;

    shiftLeftArr(info + deleteElement, size - deleteElement);
    
    return --size;
}

void shiftLeftArr(struct book arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
        arr[i] = arr[i + 1];

    arr[size - 1] = (struct book){.author = "", .title = "", .value = 0};
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