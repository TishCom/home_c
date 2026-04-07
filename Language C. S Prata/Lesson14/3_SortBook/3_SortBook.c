#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS  100

struct book
{
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};

char* s_gets(char *st, int n);
int sortAlf(const void *pa, const void *pb);
int sortPrice(const void *pa, const void *pb);

int main(int argc, char **argv)
{
	struct book library[MAXBKS];
    int count = 0;

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

        qsort(library, count, sizeof(struct book), sortAlf);
        for (int i = 0; i < count; i++)
            printf("%s - %s: %.2f\n", library[i].title, library[i].author, library[i].value);
        printf("\n");

        qsort(library, count, sizeof(struct book), sortPrice);
        for (int i = 0; i < count; i++)
            printf("%s - %s: %.2f\n", library[i].title, library[i].author, library[i].value);
        printf("\n"); 
    }
    else
        printf("No books at all? That's too bad.\n");
    
	return 0;
}

int sortAlf(const void *pa, const void *pb)
{
    return strcmp(((struct book*)pa)->title, ((struct book*)pb)->title);
}

int sortPrice(const void *pa, const void *pb)
{
    return ((struct book*)pa)->value - ((struct book*)pb)->value;
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