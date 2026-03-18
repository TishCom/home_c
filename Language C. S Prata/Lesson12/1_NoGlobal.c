#include <stdio.h>

void critic(int *units);

int main(int argc, char **argv)
{
    int units;

    printf("How many pounds does a small barrel of butter weigh?\n");

    scanf("%d", &units);
    while (units != 56)
        critic(&units);

    printf("You knew that.\n");
	return 0;
}

void critic(int *units)
{
    printf("Try again.\n");

    scanf("%d", units);
}