#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200

int main(int argc, char **argv)
{
    int words, sizeWord;
    char **ptr_str;
    char array[SIZE] = {0};

    printf("How many words do you want to enter? ");
    scanf("%d", &words);
    ptr_str = (char**) malloc(words * sizeof(char*));

    printf("Now enter %d words: \n", words);
    for (int i = 0; i < words; i++)
    {
        scanf("%s", array);
        sizeWord = strlen(array);
        ptr_str[i] = (char*) malloc(sizeWord + 1);

        for (int y = 0; y <= sizeWord; y++)
            ptr_str[i][y] = array[y];
    }

    for (int i = 0; i < words; i++)
        printf("%s\n", ptr_str[i]);

    for (int i = 0; i < words; i++)
       free(ptr_str[i]);

    free(ptr_str);
    
	return 0;
}