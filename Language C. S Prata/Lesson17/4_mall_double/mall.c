#include <stdio.h>
#include <stdlib.h>   // для rand() и srand()
#include <time.h>     // для time()
#include "queue.h"    // изменить определение Item
#define MIN_PER_HR 60.0

bool newcustomer(double x);     // появился ли новый клиент?
Item customertime(long when);   // установка параметров клиента

int main(void)
{
    Queue line, line1;
    Item temp;                          // данные нового клиента
    int hours;                          // количество часов моделирования
    int perhour;                        // среднее количество клиентов в час
    long cycle, cyclelimit;             // счетчик цикла, лимит счетчика
    long turnaways = 0;                 // количество отказов (очередь заполнена)
    long customers = 0, customers1 = 0; // количество присоединившихся к очереди
    long served = 0, served1 = 0;       // количество обслуженных клиентов
    long sum_line = 0, sum_line1 = 0;   // общая длина очереди
    int wait_time = 0, wait_time1 = 0;  // время до освобождения Sigmund
    double min_per_cust;                // среднее время между прибытиями клиентов
    long line_wait = 0, line_wait1 = 0; // общее время ожидания в очереди
    
    InitializeQueue(&line);
    InitializeQueue(&line1);
    srand((unsigned int) time(0));      // случайная инициализация rand()
    puts("Case Study: Sigmund Lander's Advice Booth");
    puts("Enter the number of simulation hours:");
    scanf("%d", &hours);
    cyclelimit = MIN_PER_HR * hours;
    puts("Enter the average number of customers per hour:");
    scanf("%d", &perhour);
    min_per_cust = MIN_PER_HR / perhour;
    
    for (cycle = 0; cycle < cyclelimit; cycle++)
    {
        if (newcustomer(min_per_cust))
        {
            if (QueueIsFull(&line) && QueueIsFull(&line1))
                turnaways++;
            else
            {
                temp = customertime(cycle);
                if (QueueItemCount(&line) > QueueItemCount(&line1))
                {
                    customers1++;
                    EnQueue(temp, &line1);
                }
                else
                {
                    customers++;
                    EnQueue(temp, &line);
                }
            }
        }
        if (wait_time <= 0 && !QueueIsEmpty(&line))
        {
            DeQueue(&temp, &line);
            wait_time = temp.processtime;
            line_wait += cycle - temp.arrive;
            served++;
        }
        if (wait_time1 <= 0 && !QueueIsEmpty(&line1))
        {
            DeQueue(&temp, &line1);
            wait_time1 = temp.processtime;
            line_wait1 += cycle - temp.arrive;
            served1++;
        }
        if (wait_time > 0)
            wait_time--;
        if (wait_time1 > 0)
            wait_time1--;
        sum_line += QueueItemCount(&line);
        sum_line1 += QueueItemCount(&line1);
    }
    
    if (customers > 0)
    {
        printf("               turnaways: %ld\n", turnaways);
        printf("customers accepted for 1: %ld\n", customers);
        printf("  customers served for 1: %ld\n", served);
        printf("average queue size for 1: %.2f\n", (double) sum_line / cyclelimit);
        printf(" average wait time: %.2f minutes for 1\n", (double) line_wait / served);
    }
    else
        puts("No customers for 1!");
    if (customers1 > 0)
    {
        printf("customers accepted for 2: %ld\n", customers1);
        printf("  customers served for 2: %ld\n", served1);
        printf("average queue size for 2: %.2f\n", (double) sum_line1 / cyclelimit);
        printf(" average wait time: %.2f minutes for 2\n", (double) line_wait1 / served1);
    }
    else
        puts("No customers for 2!");

    EmptyTheQueue(&line);
    EmptyTheQueue(&line1);
    puts("Bye!");
    
    return 0;
}

// x = среднее время (в минутах) между прибытиями клиентов
// функция возвращает true, если в эту минуту появился клиент
bool newcustomer(double x)
{
    if (rand() * x / RAND_MAX < 1)
        return true;
    else
        return false;
}

// when - время прибытия клиента
// функция возвращает структуру Item со временем прибытия when
// и временем обслуживания, случайно выбранным в диапазоне 1-3
Item customertime(long when)
{
    Item cust;
    
    cust.processtime = rand() % 3 + 1;
    cust.arrive = when;
    
    return cust;
}