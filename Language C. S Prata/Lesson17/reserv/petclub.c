#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

char menu(void);
void addpet(Tree *pt);
void droppet(Tree *pt);
void showpets(const Tree *pt);
void findpet(const Tree *pt);
void printitem(Item item);
void uppercase(char *str);
char *s_gets(char *st, int n);

int main(void)
{
    Tree pets;
    char choice;

    InitializeTree(&pets);
    while ((choice = menu()) != 'q')
    {
        switch (choice)
        {
            case 'a': addpet(&pets);
                      break;
            case 'l': showpets(&pets);
                      break;
            case 'f': findpet(&pets);
                      break;
            case 'n': printf("%d питомцев в клубе\n",
                              TreeItemCount(&pets));
                      break;
            case 'd': droppet(&pets);
                      break;
            default:  puts("Ошибка при выборе");
        }
    }
    DeleteAll(&pets);
    puts("До свидания.");

    return 0;
}

char menu(void)
{
    int ch;

    puts("Домашний клуб питомцев");
    puts("Введите букву, соответствующую выбранному варианту:");
    puts("a) добавление питомца          l) вывод списка питомцев");
    puts("n) количество питомцев         f) поиск питомца");
    puts("d) удаление питомца            q) выход");
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')   // пропуск остатка строки
            continue;
        ch = tolower(ch);
        if (strchr("alrfndq", ch) == NULL)
            puts("Пожалуйста, введите a, l, f, n, d или q:");
        else
            break;
    }
    if (ch == EOF)      // заставляем q завершить программу
        ch = 'q';

    return ch;
}

void addpet(Tree *pt)
{
    Item temp;

    if (TreeIsFull(pt))
        puts("В клубе больше нет мест!");
    else
    {
        puts("Введите имя питомца:");
        s_gets(temp.petname, SLEN);
        puts("Введите вид питомца:");
        s_gets(temp.petkind, SLEN);
        uppercase(temp.petname);
        uppercase(temp.petkind);
        AddItem(&temp, pt);
    }
}

void showpets(const Tree *pt)
{
    if (TreeIsEmpty(pt))
        puts("Записи отсутствуют.");
    else
        Traverse(pt, printitem);
}

void printitem(Item item)
{
    printf("Питомец: %-19s  Вид: %-19s\n", item.petname,
            item.petkind);
}

void findpet(const Tree *pt)
{
    Item temp;

    if (TreeIsEmpty(pt))
    {
        puts("Записи отсутствуют.");
        return;
    }

    puts("Введите имя питомца, которого хотите найти:");
    s_gets(temp.petname, SLEN);
    puts("Введите вид питомца:");
    s_gets(temp.petkind, SLEN);
    uppercase(temp.petname);
    uppercase(temp.petkind);
    printf("%s %s ", temp.petname, temp.petkind);
    if (InTree(&temp, pt))
        printf("является членом клуба.\n");
    else
        printf("не является членом клуба.\n");
}

void droppet(Tree *pt)
{
    Item temp;

    if (TreeIsEmpty(pt))
    {
        puts("Записи отсутствуют.");
        return;
    }

    puts("Введите имя питомца, которого хотите исключить:");
    s_gets(temp.petname, SLEN);
    puts("Введите вид питомца:");
    s_gets(temp.petkind, SLEN);
    uppercase(temp.petname);
    uppercase(temp.petkind);
    printf("%s %s ", temp.petname, temp.petkind);
    if (DeleteItem(&temp, pt))
        printf("исключен из клуба.\n");
    else
        printf("не является членом клуба.\n");
}

void uppercase(char *str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}