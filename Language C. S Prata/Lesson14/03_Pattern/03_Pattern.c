#include <stdio.h>

struct car
{
    char brand[30];
    int power;
    float ecology;
    int base;
    int year;
};

struct gas
{
    float distance;
    float gals;
    float mpg;
};

enum choices
{
    no      = 0,
    yes     = 1,
    maybe   = 2
};

typedef char* (*func1)(char*, char);
typedef double (*func2)(double, double);

struct gas func(struct gas a);
void funcPtr(struct gas *a);
char* funcPtr1(char *str, char ch);
char* funcPtr2(char *str, char ch);
double funcDoublePtr1(double a, double b);
double funcDoublePtr2(double a, double b);
double funcDoublePtr3(double a, double b);
double funcDoublePtr4(double a, double b);

int main(int argc, char **argv)
{
    func1 pf = funcPtr1;
    func2 arr[4] = {funcDoublePtr1, funcDoublePtr2, funcDoublePtr3, funcDoublePtr4};
    pf("fg", 'f');
    pf = funcPtr2;
    pf("Frenc", 'F');
	printf("Hello world! %d\n", maybe);

    printf("%.2f\n", arr[2](10.0, 2.5));
    printf("%.2f\n", (*(arr + 3))(10.0, 2.5));
	return 0;
}

struct gas func(struct gas a)
{
    a.mpg = a.gals / a.distance;

    return a;
}

void funcPtr(struct gas *a)
{
    a->mpg = a->gals / a->distance;
}

char* funcPtr1(char *str, char ch)
{
    printf("HI!!! - %s - %c\n", str, ch);
    return NULL;
}

char* funcPtr2(char *str, char ch)
{
    printf("HI Fine!!! - %s - %c\n", str, ch);
    return NULL;
}

double funcDoublePtr1(double a, double b)
{
    printf("HI Fine1!!! - %.2f - %.2f\n", a, b);
    return a + b;
}

double funcDoublePtr2(double a, double b)
{
    printf("HI Fine2!!! - %.2f - %.2f\n", a, b);
    return a + b;
}

double funcDoublePtr3(double a, double b)
{
    printf("HI Fine3!!! - %.2f - %.2f\n", a, b);
    return a + b;
}

double funcDoublePtr4(double a, double b)
{
    printf("HI Fine4!!! - %.2f - %.2f\n", a, b);
    return a + b;
}