/*
 * F4_NumbersInString.c
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
#include <string.h>

//Размер массива
#define SIZE 	1000

/*
 * Функция вывдит на экран цифры в порядке возрастания, входящие в строку. 
 * Цифра пробел сколько раз данная цифра встречается в числе.
*/
void print_digit(char arr[]);
//Функция возвращает число равное колличеству вхождений цифр в строку arr
int numberDigitInString(char arr[], int size);

int main(int argc, char **argv)
{
	char stringNumber[SIZE] = {0};
	
	fgets(stringNumber, SIZE, stdin);
	*(strchr(stringNumber, '\n')) = '\0';
	
	print_digit(stringNumber);
	
	return 0;
}

/*
 * Функция вывдит на экран цифры в порядке возрастания, входящие в строку. 
 * Цифра пробел сколько раз данная цифра встречается в числе.
 * Вариант 2
*/
void print_digit(char arr[])
{
	int digit[10] = {0};
	
	for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] >= '0' && arr[i] <= '9')
			digit[arr[i] - '0']++;
	}
		
	for (int i = 0; i < 10; i++)
	{
		if (digit[i])
			printf("%d %d\n", i, digit[i]);
	}
}

//Функция возвращает число равное колличеству вхождений цифр в строку arr
int numberDigitInString(char arr[], int size)
{
	int number = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] >= '0' && arr[i] <= '9')
			number++;
	}
	
	return number;
}
