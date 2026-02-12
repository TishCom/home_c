/*
 * C20_Parentheses.c
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

//Функция проверяет является ли символ character круглой скобуой
uint32_t isParentheses(char character);
//Функция проверяет является ли введенная строка с круглыми скобками корректной
uint32_t isCorrectUseParentheses(void);

int main(int argc, char **argv)
{
	if (isCorrectUseParentheses())
		printf("YES");
	else
		printf("NO");
	
	return 0;
}

//Функция проверяет является ли символ character круглой скобуой
uint32_t isParentheses(char character)
{
	if (character == ')' || character == '(')
		return  1;
	else
		return  0;
}

//Функция проверяет является ли введенная строка с круглыми скобками корректной
uint32_t isCorrectUseParentheses(void)
{
	char character = 0;
	int32_t sum = 0;
	
	scanf("%c", &character);
	
	while (sum >= 0 && character != '.')
	{
		if (character == '(')
			sum++;
		else if (character == ')')
			sum--;
			
		scanf("%c", &character);
	}
	
	return !sum;
}

