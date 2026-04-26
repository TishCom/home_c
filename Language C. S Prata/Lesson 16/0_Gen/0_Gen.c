#include <stdio.h>
#include <string.h>

#define MYTYPE(X) _Generic((X),\
int:        "int",\
float:      "float",\
double:     "double",\
default:    "other"\
)

#define MYTYPEN(X) _Generic((X),\
_Bool:      "boolean",\
default:    "not boolean"\
)

int main(int argc, char **argv)
{
    int a;
    float b;
    double c;
    long d;
    _Bool f;
    double data1[100] = {1, 2, 3, 3, 4 ,5}, data2[300];

	printf("Hello world!\n");
    printf("%s\n", MYTYPE(a));
    printf("%s\n", MYTYPE(b));
    printf("%s\n", MYTYPE(c));
    printf("%s\n", MYTYPE(d));
    printf("%s\n", MYTYPE(a));
    printf("\n");
    printf("%s\n", MYTYPEN(c));
    printf("%s\n", MYTYPEN(f));
    printf("%s\n", MYTYPEN(a));
    printf("\n");

    for (int i = 0; i < 100; i++)
    {
        printf("%.2lf ", data1[i]);
    }
    printf("\n");
    for (int i = 0; i < 300; i++)
    {
        printf("%.2lf ", data2[i]);
    }
    printf("\n");
    memcpy(data1 , data2 + 200, 100 * sizeof(double));
    for (int i = 0; i < 100; i++)
    {
        printf("%.2lf ", data1[i]);
    }
    printf("\n");
    memcpy(data1 , data2, 100 * sizeof(double));
    for (int i = 0; i < 100; i++)
    {
        printf("%.2lf ", data1[i]);
    }
    printf("\n");
    

	return 0;
}