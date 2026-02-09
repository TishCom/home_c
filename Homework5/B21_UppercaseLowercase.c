/*
 * B21_UppercaseLowercase.c
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

//Проверка символа на то является это буквой старшего регистра или нет
#define IS_UPPERCASE_LETTER(letter)			((letter) >= 'A' && (letter) <= 'Z')
//Проверка символа на то является это буквой младшего регистра или нет
#define IS_LOWERCASE_LETTER(letter)			((letter) >= 'a' && (letter) <= 'z')
//Проверка символа на то является это буквой или нет
#define IS_LETTER(letter)					(IS_UPPERCASE_LETTER(letter) || IS_LOWERCASE_LETTER(letter))
//Переводит буквы английского алфавита из строчных в прописные
#define LOWERCASE_UPPERCASE(letter)			((letter) - ('a' - 'A'))
//Переводит буквы английского алфавита из прописных в строчные
#define UPPERCASE_LOWERCASE(letter)			((letter) + ('a' - 'A'))
//Переводит буквы английского алфавита из прописных в строчные и наоборот, остальные символы остаются неизменными
#define CHANGE_CASE(character)				(IS_LETTER(character) ? (IS_UPPERCASE_LETTER(character) ? UPPERCASE_LOWERCASE(character) : LOWERCASE_UPPERCASE(character)) : (character))

int main(int argc, char **argv)
{
	char char1 = 0;
	
	scanf("%c", &char1);
	
	while (char1 != '.')
	{
		if (IS_UPPERCASE_LETTER(char1))
			char1 = UPPERCASE_LOWERCASE(char1);

		printf("%c", char1);
		
		scanf("%c", &char1);
	}

	return 0;
}
