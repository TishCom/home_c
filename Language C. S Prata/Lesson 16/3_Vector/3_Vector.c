#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#define PI 3.14159265358979323846
#define RADIAN(A) ((PI * (A)) / 180)
#define DEGREES(A) ((180 * (A)) / PI)

typedef struct
{
    float r;
    float a;
}vectorFild;

typedef struct
{
    float x;
    float y;
}vectorAngle;

vectorAngle funcVector (vectorFild vector);

int main(int argc, char **argv)
{
    vectorFild a;
    vectorAngle b;

	printf("Hello world!\n");
    scanf("%f %f", &a.r, &a.a);
    b = funcVector(a);
    printf("r = %.2f, a = %.2f, x = %.2f, y = %.2f\n", a.r, a.a, b.x, b.y);

	return 0;
}

vectorAngle funcVector (vectorFild vector)
{
    vectorAngle ret;

    ret.x = vector.r * cos(RADIAN(vector.a));
    ret.y = vector.r * sin(RADIAN(vector.a));

    return ret;
}