#include <stdio.h>
#include <string.h>

typedef struct lens
{
    float foclen;
    float fstop;
    char brand[30];
}LENS;


int main(int argc, char **argv)
{
    LENS arr[10] = {[2].foclen = 500, [2].fstop = 250, [2].brand = "Remarkatar"};

    strncpy(arr[3].brand, "Remarkatar", strlen("Remarkatar") + 1);
    arr[3].foclen = 500;
    arr[3].fstop = 250;

	printf("%s - %.2f - %.2f\n", arr[2].brand, arr[2].foclen, arr[2].fstop);
    printf("%s - %.2f - %.2f\n", arr[3].brand, arr[3].foclen, arr[3].fstop);

	return 0;
}