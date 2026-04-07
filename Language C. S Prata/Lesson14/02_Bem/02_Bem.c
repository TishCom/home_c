#include <stdio.h>

struct name
{
    char first[20];
    char last[20];
};

struct bem
{
    int limbs;
    struct name title;
    char type[30];
};

void func(struct bem *b);

int main(int argc, char **argv)
{
    struct bem deb = {6, {"Berbnazel", "Gwolkapwolk"}, "Arcturan"};
    struct bem *pb = &deb;
    func(pb);

	return 0;
}

void func(struct bem *b)
{
    printf("%s %s - is %d %s.\n", b->title.first, b->title.last, b->limbs, b->type);
}