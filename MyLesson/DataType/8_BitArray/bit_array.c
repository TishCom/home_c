#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bit_array.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/


/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/


/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/*инициализация битового массива*/
bool initializeBitArray(BitArray *barr, uint32_t bits)
{
    if (barr == NULL || bits == 0)
        return false;

    uint32_t bytes =  (bits + 7) / 8;

    barr->data = (uint8_t*)malloc(bytes);
    if (barr->data == NULL)
        return false;

    for (uint32_t i = 0; i < bytes; i++)
        barr->data[i] = 0;

    barr->bits = bits;
    barr->bytes = bytes;

    return true;
}

/*определяет количество значащих битов в битовом массиве*/
uint32_t bitArrayGetBitCount(const BitArray *barr)
{
    if (barr == NULL)
        return 0;

    return barr->bits;
}

/*определяет количество установленный в 1 значащих битов в битовом массиве*/
uint32_t bitArrayGetSetCount(const BitArray *barr)
{
    if (barr == NULL)
        return 0;

    uint32_t number_set_bit = 0;

    for (uint32_t i = 0; i < barr->bytes; i++)
    {
        for (uint32_t bit = 0; bit < 8; bit++)
        {
            if (barr->data[i] & (1 << bit))
                number_set_bit++;
        }
    }
    
    return number_set_bit; 
}

/*определяет количество сброшенных в 0 значащих битов в битовом массиве*/
uint32_t bitArrayGetResetCount(const BitArray *barr)
{
    return bitArrayGetBitCount(barr) - bitArrayGetSetCount(barr); 
}

/*устанавливает значащий бит в битовом массиве в 1*/
bool setBitInArray(BitArray *barr, uint32_t number_bit)
{
    if (barr == NULL || barr->bits <= number_bit)
        return false;

    barr->data[number_bit / 8] |= 1 << number_bit % 8;

    return true;
}

/*сбрасывает значащий бит в битовом массиве в 0*/
bool resetBitInArray(BitArray *barr, uint32_t number_bit)
{
    if (barr == NULL || barr->bits <= number_bit)
        return false;

    barr->data[number_bit / 8] &= ~(1 << number_bit % 8);

    return true;
}

/*инвертирует значащий бит в битовом массиве*/
bool invertBitInArray(BitArray *barr, uint32_t number_bit)
{
    if (barr == NULL || barr->bits <= number_bit)
        return false;

    barr->data[number_bit / 8] ^= 1 << number_bit % 8;

    return true;
}

/*проверка бита в битовом масиве*/
bool checkBitInArray(const BitArray *barr, uint32_t number_bit, bool *bit_value)
{
    if (barr == NULL || barr->bits <= number_bit || bit_value == NULL)
        return false;

    *bit_value = (((barr->data[number_bit / 8] >> (number_bit % 8)) & 1) == 1);

    return true;
}

/*найти первый установленный бит*/
bool bitArrayFindFirstSet(const BitArray *barr, uint32_t *number_bit)
{
    if (barr == NULL || number_bit == NULL)
        return false;

    for (uint32_t byte = 0; byte < barr->bytes; byte++)
    {
        if (barr->data[byte] == 0)
            continue;
        
        for (uint32_t bit = 0; bit < 8; bit++)
        {
            if (byte * 8 + bit >= barr->bits)
                break;

            if ((barr->data[byte] & 1 << bit))
            {
                *number_bit = byte * 8 + bit;
                return true;
            }
        }
    }

    return false;
}

/*найти первый сброшенный бит*/
bool bitArrayFindFirstClear(const BitArray *barr, uint32_t *number_bit)
{
    if (barr == NULL || number_bit == NULL)
        return false;

    for (uint32_t byte = 0; byte < barr->bytes; byte++)
    {
        if (barr->data[byte] == 0xFF)
            continue;
        
        for (uint32_t bit = 0; bit < 8; bit++)
        {
            if (byte * 8 + bit >= barr->bits)
                break;

            if ((barr->data[byte] & 1 << bit) == 0)
            {
                *number_bit = byte * 8 + bit;
                return true;
            }
        }
    }

    return false;
}

/*проверка всех битов в битовом масиве на сброшенность в 0*/
bool bitArrayIsEmpty(const BitArray *barr, bool *is_empty)
{
    if (barr == NULL || is_empty == NULL)
        return false;

    *is_empty = true;

    for (uint32_t i = 0; i < barr->bytes; i++)
    {
        if (barr->data[i] != 0)
        {
            *is_empty = false;
            break;
        }
    }

    return true;
}

/*проверка всех битов в битовом масиве на установку в 1*/
bool bitArrayIsFull(const BitArray *barr, bool *is_full)
{
    if (barr == NULL || is_full == NULL)
        return false;

    *is_full = true;

    for (uint32_t i = 0; i < barr->bytes; i++)
    {
        if(i == barr->bytes - 1)
        {
            for (uint32_t y = 0; y < barr->bits - i * 8; y++)
            {
                if ((barr->data[i] & (1 << y)) == 0)
                {
                    *is_full = false;
                    break;
                }
            }
        }
        else if (barr->data[i] != 0xFF)
        {
            *is_full = false;
            break;
        }
    }

    return true;
}

/*установка всех значимых битов массива в 1*/
bool bitArraySetAll(BitArray *barr)
{
    if (barr == NULL)
        return false;

    for (uint32_t i = 0; i < barr->bytes - 1; i++)
        barr->data[i] = 0xFF;
    
    for (uint32_t i = (barr->bytes - 1) * 8; i < barr->bits; i++)
        setBitInArray(barr, i);

    return true;
}

/*сброс всех значимых битов массива в 0*/
bool bitArrayClearAll(BitArray *barr)
{
    if (barr == NULL)
        return false;

    for (uint32_t i = 0; i < barr->bytes; i++)
        barr->data[i] = 0;

    return true;
}

/*применение функции к каждому значащему биту в битовом массиве*/
bool traverseBitArray(BitArray *barr, 
                      void (*pfun)(BitArray *arr, uint32_t number_bit, bool bit_value))
{
    if (barr == NULL || pfun == NULL)
        return false;

    uint32_t bit_index = 0;
    bool bit_value = false;

    for (uint32_t byte = 0; byte < barr->bytes; byte++) 
    {
        for (uint32_t bit = 0; bit < 8; bit++) 
        {
            bit_index = byte * 8 + bit;
            if (bit_index >= barr->bits)
                break;
            
            bit_value = (barr->data[byte] & (1 << bit)) ? true : false;
            pfun(barr, bit_index, bit_value);
        }
    }

    return true;
}

/*освобождение выделенной памяти если она есть*/
void emptyTheBitArray(BitArray *barr)
{
    if (barr == NULL)
        return;

    free(barr->data);
    barr->data = NULL;
    barr->bits = 0;
    barr->bytes = 0;
}
 
/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/


/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/
