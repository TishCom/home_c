#include <stdio.h>
#include "pe12-2a.h"

int main(int argc, char **argv)
{
	int mode = 7;

    printf("Enter: 0 is metric, 1 is imperial.\n");
    scanf("%d", &mode);

    while (mode >= 0)
    {
        set_mode(mode);
        get_info();
        show_info();
        printf("Enter: 0 is metric, 1 is imperial.\n");
        printf("Enter -1 for exit.\n");
        scanf("%d", &mode);
    }
    
    printf("Exit.\n");
	return 0;
}