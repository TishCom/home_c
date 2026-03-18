#include <stdio.h>
#include "pe12-2a.h"

int main(int argc, char **argv)
{
	int mode = 0, previousMode = 0;
    float fuel = 0, distance = 0;

    printf("Enter: 0 is metric, 1 is imperial.\n");
    scanf("%d", &mode);

    while (mode >= 0)
    {
        set_mode(&mode, previousMode);
        get_info(&fuel,&distance);
        show_info(fuel, distance, mode);
        printf("Enter: 0 is metric, 1 is imperial.\n");
        printf("Enter -1 for exit.\n");
        previousMode = mode;
        scanf("%d", &mode);
    }
    
    printf("Exit.\n");
	return 0;
}