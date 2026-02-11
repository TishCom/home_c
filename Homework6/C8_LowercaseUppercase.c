/*
 * C8_LowercaseUppercase.c
 * 
 * Copyright 2026 Tisha <Tisha@DESKTOP-TSPB5RM>
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
#include <stdint.h>

//Функция переводит букву letter из нижнего регистра в верхний
char lowercaseUppercase(char letter);
//Функция переводит букву letter из верхнего регистра в нижний
char uppercaseLowercase(char letter);
//Функция меняет регистр буквы letter
char changeCaseLetter(char character);
//Функция переводит character(0 - 9) в число
uint32_t characterNumber(char character);
//Функция проверяет находится ли буква letter в верхнем регистре
uint32_t isUppercaseLetter(char letter);
//Функция проверяет находится ли буква letter в нижнем регистре
uint32_t isLowercaseLetter(char letter);
//Функция проверяет является ли letter буквой
uint32_t isLetter(char letter);
//Функция проверяет является ли character символом числа(0 - 9)
uint32_t isNumberCharacter(char character);
//Функция проверяет является ли character печатным символом
uint32_t isPrintableCharacter(char character);

int main(int argc, char **argv)
{
	char character = 0;
	
	scanf("%c", &character);
	
	while (character != '.')
	{
		character = lowercaseUppercase(character);
	
		printf("%c", character);
		
		scanf("%c", &character);
	}
	
	return 0;
}

//Функция переводит букву letter из нижнего регистра в верхний
char lowercaseUppercase(char letter)
{
	if (isLowercaseLetter(letter))
		return  letter - ('a' - 'A');
	else
		return  letter;
}

//Функция переводит букву letter из верхнего регистра в нижний
char uppercaseLowercase(char letter)
{
	if (isUppercaseLetter(letter))
		return  letter + ('a' - 'A');
	else
		return  letter;
}

//Функция меняет регистр буквы letter
char changeCaseLetter(char character)
{
	if (isLetter(character))
	{
		if (isLowercaseLetter(character))
			return  character - ('a' - 'A');
		else if (isUppercaseLetter(character))
			return  character + ('a' - 'A');
	}
	
	return  character;
}

//Функция переводит character(0 - 9) в число
uint32_t characterNumber(char character)
{
	if (isNumberCharacter(character))
		return  character - '0';
	else
		return  character;
}

//Функция проверяет находится ли буква letter в верхнем регистре
uint32_t isUppercaseLetter(char letter)
{
	if (letter >= 'A' && letter <= 'Z')
		return  1;
	else
		return  0;
}

//Функция проверяет находится ли буква letter в нижнем регистре
uint32_t isLowercaseLetter(char letter)
{
	if (letter >= 'a' && letter <= 'z')
		return  1;
	else
		return  0;
}

//Функция проверяет является ли letter буквой
uint32_t isLetter(char letter)
{
	if (isUppercaseLetter(letter) || isLowercaseLetter(letter))
		return  1;
	else
		return  0;
}

//Функция проверяет является ли character символом числа(0 - 9)
uint32_t isNumberCharacter(char character)
{
	if (character >= '0' && character <= '9')
		return  1;
	else
		return  0;
}

//Функция проверяет является ли character печатным символом
uint32_t isPrintableCharacter(char character)
{
	if ((character >= '!' && character <= '/') || 
		(character >= ':' && character <= '@') || 
		(character >= '[' && character <= '`') || 
		(character >= '{' && character <= '~'))
		return  1;
	else
		return  0;
}
