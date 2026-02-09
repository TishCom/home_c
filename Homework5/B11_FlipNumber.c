/*
 * B10_FlipNumber.c
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

//Максималное возможное входное значение
#define MAX_NUMBER									5000000
//Минимальное возможное входное значение
#define MIN_NUMBER									0
//Входит ли введенное число в верхний предел
#define UPPER_LIMIT(number)							((number) <= MAX_NUMBER)
//Входит ли введенное число в нижний предел
#define LOWER_LIMIT(number)							((number) >= MIN_NUMBER)
//Входит ли введенное число в необходимые пределы
#define ENTER_LIMIT(number)							(UPPER_LIMIT(number) && LOWER_LIMIT(number))

//Основание системы счисления введенного числа
#define BASE_NUMBER									10
//Возвращяет цифру находящуюся в разряде digit числа number
#define RETURN_DIGIT_NUMBER(number, digit)			(((number) / (digit)) % BASE_NUMBER)
//Возвращяет десятичное число number сдвинутое вправо на digit разрядов
#define SHIFT_DIGIT_NUMBER_RIGHT(number, digit)		((number) / ((digit) * BASE_NUMBER))
//Возвращяет десятичное число number сдвинутое влево на digit разрядов
#define SHIFT_DIGIT_NUMBER_LEFT(number, digit)		((number) * ((digit) * BASE_NUMBER))

//Проверка числа на четность
#define IS_EVEN(number)								(!((number) % 2))

//Возвращяет максимальное из двух введенных чисел
#define MAX(operand1, operand2)						((operand1) >= (operand2) ? (operand1) : (operand2))
//Возвращяет минимальное из двух введенных чисел
#define MIN(operand1, operand2)						((operand1) <= (operand2) ? (operand1) : (operand2))

//Проверка символа на то является это буквой старшего регистра или нет
#define IS_UPPERCASE_LETTER(letter)					((letter) >= 'A' && (letter) <= 'Z')
//Проверка символа на то является это буквой младшего регистра или нет
#define IS_LOWERCASE_LETTER(letter)					((letter) >= 'a' && (letter) <= 'z')
//Проверка символа на то является это буквой или нет
#define IS_LETTER(letter)							(IS_UPPERCASE_LETTER(letter) || IS_LOWERCASE_LETTER(letter))
//Переводит буквы английского алфавита из строчных в прописные
#define LOWERCASE_UPPERCASE(letter)					((letter) - ('a' - 'A'))
//Переводит буквы английского алфавита из прописных в строчные
#define UPPERCASE_LOWERCASE(letter)					((letter) + ('a' - 'A'))
//Переводит буквы английского алфавита из прописных в строчные и наоборот, остальные символы остаются неизменными
#define CHANGE_CASE(character)						(IS_LETTER(character) ? (IS_UPPERCASE_LETTER(character) ? UPPERCASE_LOWERCASE(character) : LOWERCASE_UPPERCASE(character)) : (character))

//Разряды введенного числа
enum Place
{
	UNITS    = 1,
	TENS     = 10,
	HUNDREDS = 100
};

int main(int argc, char **argv)
{
	int32_t numberIN = 0, numberOUT = 0;
	
	scanf("%d", &numberIN);
	
	if (!(ENTER_LIMIT(numberIN)))
		return 1;
	
	while(numberIN > 9)
	{
		numberOUT += RETURN_DIGIT_NUMBER(numberIN, UNITS);
		numberOUT = SHIFT_DIGIT_NUMBER_LEFT(numberOUT, UNITS);
		numberIN = SHIFT_DIGIT_NUMBER_RIGHT(numberIN, UNITS);
	}
	
	numberOUT += RETURN_DIGIT_NUMBER(numberIN, UNITS);
	
	printf("%d", numberOUT);
	
	return 0;
}

