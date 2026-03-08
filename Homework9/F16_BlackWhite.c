/*
 * F16_BlackWhite.c
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

//Меньшая возможная буква в названии клетки
#define LIM_LETTER_MIN		'A'
//Большая возможная буква в названии клетки
#define LIM_LETTER_MAX		'H'
//Меньшая возможная цифра в названии клетки
#define LIM_NUMBER_MIN		1
//Большая возможная цифра в названии клетки
#define LIM_NUMBER_MAX		8
//Колличество клеток в в одной линии
#define NUMBER_CELL_IN_LINE	8

//Функция возвращает 1 если введенная клетка белая и ноль в противном случае
int blackOrWhite(void);
//Функция пропускает все символу в строке
void skipString(void);
//Функция проверяет является ли ввод корректным
int isCorrectInput(char letter, int number);

int main(int argc, char **argv)
{
	if (blackOrWhite())
		printf("WHITE\n");
	else
		printf("BLACK\n");
	
	return 0;
}

//Функция возвращает 1 если введенная клетка белая и ноль в противном случае
int blackOrWhite(void)
{
	char letter = 0;
	int number = 0;
	
	while((scanf("%c%d", &letter, &number) != 2) ||
			!isCorrectInput(letter, number))
	{
		skipString();
		printf("Enter correct volue.\n");
	}
	
	letter -= 'A';
	
	if (letter % 2 == 0)
		number++;
	
	return ((letter * NUMBER_CELL_IN_LINE + number) % 2);
}

//Функция пропускает все символу в строке
void skipString(void)
{
	while (getchar() != '\n')
		continue;
}

//Функция проверяет является ли ввод корректным
int isCorrectInput(char letter, int number)
{
	return ((letter >= LIM_LETTER_MIN && letter <= LIM_LETTER_MAX) &&
			(number >= LIM_NUMBER_MIN && number <= LIM_NUMBER_MAX));
}
