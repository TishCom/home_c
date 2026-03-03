/*
 * 9_Menu.c
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
#include <ctype.h>

void skipString(void);
char getFirstChar(void);
int getInt(void);
int acceptable(char ch);
char getFirstNoSpaceChar(void);
char skipSpace(void);

int main(int argc, char **argv)
{
	char opertion = 0;
	float number1 = 0, number2 = 0;
	
	printf("Enter operation a - q: \n");
	printf("a) addition		b) subtraction\n");
	printf("c) multiplication	d) division\n");
	printf("q) exit\n");
	
	while ((opertion = getFirstNoSpaceChar()) != 'q')
	{
		if (!acceptable(opertion))
		{
			printf("Enter correct operation.\n");
			continue;
		}
		
		printf("Enter first number: ");
		number1 = getInt();
		printf("Enter second number: ");
		number2 = getInt();
		
		while (opertion == 'd' && number2 == 0)
		{
			printf("Enter second number: ");
			number2 = getInt();
		}
		
		switch (opertion)
		{
			case 'a':
				printf("%.2f + %.2f = %.2f\n", number1, number2, number1 + number2);
				break;
			case 'b':
				printf("%.2f - %.2f = %.2f\n", number1, number2, number1 - number2);
				break;
			case 'c':
				printf("%.2f * %.2f = %.2f\n", number1, number2, number1 * number2);
				break;
			case 'd':
				printf("%.2f / %.2f = %.2f\n", number1, number2, number1 / number2);
		}
		
	}
	
	printf("Exit.\n");
	
	return 0;
}

int acceptable(char ch)
{
	return ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd';
}

char getFirstChar(void)
{
	int ch = getchar();
	
	skipString();
	
	return ch;
}

char getFirstNoSpaceChar(void)
{
	int ch = skipSpace();
	
	skipString();
	
	return ch;
}

char skipSpace(void)
{
	int ch = getchar();
	
	while (isspace(ch))
		ch = getchar();
	
	return ch;
}

int getInt(void)
{
	int number;
	
	while (scanf("%d", &number) != 1)
		skipString();
	
	return number;
}

void skipString(void)
{
	while (getchar() != '\n')
		continue;
}
