#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 6

struct names
{
    char first[40];
    char last[40];
};

void showArray(const struct names arr[], int size);
int myComp(const void *p1, const void *p2);

int main(int argc, char **argv)
{
	struct names vals[NUM] = 
    {
        [0] = {.first = "Aren", .last = "Mercht"},
        [1] = {.first = "Kerg", .last = "Ldvfmv"},
        [2] = {.first = "Leryt", .last = "Mbssg"},
        [3] = {.first = "Herbf", .last = "Rvsdsh"},
        [4] = {.first = "Richard", .last = "Aranovsku"},
        [5] = {.first = "Bob", .last = "Nilson"}
    };
    
    puts("No sorted List:");
    showArray(vals, NUM);
    qsort(vals, NUM, sizeof(struct names), myComp);
    puts("\nSorted List:");
    showArray(vals, NUM);

	return 0;
}

void showArray(const struct names arr[], int size)
{
    int index;

    for (index = 0; index < size; index++)
    {
        printf("%s %s |", arr[index].first, arr[index].last);

        if (index % 6 == 2)
            putchar('\n');
    }
    
    if (index % 2 != 0)
        putchar('\n');
}

int myComp(const void *p1, const void *p2)
{
    const struct names *a1 = (const struct names*)p1;
    const struct names *a2 = (const struct names*)p2;
    int res = strcmp(a1->first, a2->first);

    if (res != 0)
        return res;
    else
        return strcmp(a1->last, a2->last);
}
