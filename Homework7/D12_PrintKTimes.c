/*
 * D12_PrintKTimes.c
 * 
 * Copyright 2026 tisha <tisha@DESKTOP-H2QK95F>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <inttypes.h>

//Обертка функции printKTimes
#define printK(number)		printKTimes(1, number) 
//Возвращяет следующее число
#define NEXT_NUMBER(number)	((number) + 1)

/*
 * Функция распечатывает последовательность из n чисел,
 * в которой каждое натуральное число k встречается ровно k раз
 */
void printKTimes(uint32_t i, uint32_t n);
//Вспомогательная функция для функции printKTimes
void recursionFor(uint32_t i, uint32_t n, uint32_t *y);

int main(int argc, char **argv)
{
	int32_t number = 0;
	
	scanf("%d", &number);
	
	printK(number); 
	
	return 0;
}

void printKTimes(uint32_t auxiliaryNumber, uint32_t numberUser) 
{
	if (numberUser <= 0)
		return;
	
	recursionFor(0, auxiliaryNumber, &numberUser);
	
	printKTimes(NEXT_NUMBER(auxiliaryNumber), numberUser);
}

void recursionFor(uint32_t auxiliaryNumber2, uint32_t auxiliaryNumber1, uint32_t *numberUser)
{
	if (*numberUser <= 0 || auxiliaryNumber2 >= auxiliaryNumber1)
		return;
		
	printf("%d ", auxiliaryNumber1);
	
	(*numberUser)--;
	
	recursionFor(NEXT_NUMBER(auxiliaryNumber2), auxiliaryNumber1, numberUser);
}
