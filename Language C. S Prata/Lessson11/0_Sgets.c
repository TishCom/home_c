/*
 * 0_Sgets.c
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

char* sgets(char *str, int size);
void skipString(void);
char* fgets1(char *str, int size);

int main(int argc, char **argv)
{
	char arr[40];
	char arr1[60];
	
	sgets(arr, 40);
	
	printf("%s\n", arr);
	fputs(arr, stdout);
	putchar('\n');
	puts(arr + 2);
	fputs(arr, stdout);
	putchar('\n');
	sprintf(arr1, "%s %s: %d.\n", arr, "Hello", 32);
	puts(arr1);
	
	fgets1(arr, 40);
	puts(arr);
	fgets1(arr, 40);
	puts(arr);
	
	return 0;
}

/* Аналог функции fgets, но она считывает столько сколько
 *надо(второй параметр), а если что то осталось то это просто
 *отбрасывает и плюс удаляет '\n' из конечной строки.
*/
char* sgets(char *str, int size)
{
	char *retVal;
	int i = 0;
	
	retVal = fgets(str, size, stdin);
	
	if (retVal)
	{
		while (str[i] != '\n' && str[i] != '\0')
			i++;
			
		if (str[i] == '\n')
			str[i] = '\0';
		else
			skipString();
	}
	
	return retVal;
}

//Обычны fgets просто убирает '\n'
char* fgets1(char *str, int size)
{
	char *retVal, *find;
	
	retVal = fgets(str, size, stdin);
	
	if (retVal)
	{
		find = strchr(str, '\n');
		
		if (find)
			*find = '\0';
	}
	
	return retVal;
}

void skipString(void)
{
	while (getchar() != '\n')
		continue;
}
