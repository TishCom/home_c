/*
 * 11_MenuOutput.c
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
#include <string.h>

#define STRING 	10
#define COLUMNS 40

void output(int size, const char arr[]);
void inputArr(int string, int columns, char arr[string][columns], char *arr1[columns]);
void sortASCIIArr(int string, char *arr[]);
void sortLengthArr(int string, char *arr[]);
void sortLengthFirstWordArr(int string, char *arr[]);
void swap(char **i, char **y);
int numberCharacterInWord(char arr[]);

int main(int argc, char **argv)
{
	char str[STRING][COLUMNS] = {0};
	char *str1[COLUMNS] = {0};
	
	inputArr(STRING, COLUMNS, str, str1);
	
	printf("Enter chois\n");
	switch (getchar())
	{
		case 'a':
			printf("Normal\n");
			break;
		case 'b':
			printf("Sort ASCII\n");
			sortASCIIArr(STRING, str1);
			break;
		case 'c':
			printf("Sort Length\n");
			sortLengthArr(STRING, str1);
			break;
		case 'd':
			printf("Sort Length First Word\n");
			sortLengthFirstWordArr(STRING, str1);
			break;
		case 'e':
			printf("Exit\n");
			return 0;
	}
		
	for (int i = 0; i < STRING; i++)
		output(COLUMNS, str1[i]);
		
	return 0;
}

void inputArr(int string, int columns, char arr[string][columns], char *arr1[columns])
{
	for (int i = 0; i < string; i++)
	{
		for (int y = 0, ch = getchar(); y < columns && ch != '\n'; y++)
		{
			arr[i][y] = ch;
			
			ch = getchar();
			if (ch == EOF)
				return;
		}
		arr1[i] = arr[i];
	}	
}

void sortASCIIArr(int string, char *arr[])
{
	for (int i = 0; i < string; i++)
	{
		for (int y = i + 1; y < string; y++)
		{
			if (strcmp(arr[i], arr[y]) > 0)
				swap(&arr[i], &arr[y]);
		}
	}		
}

void sortLengthArr(int string, char *arr[])
{
	for (int i = 0; i < string; i++)
	{
		for (int y = i + 1; y < string; y++)
		{
			if (strlen(arr[i]) < strlen(arr[y]))
				swap(&arr[i], &arr[y]);
		}
	}	
}

void sortLengthFirstWordArr(int string, char *arr[])
{
	for (int i = 0; i < string; i++)
	{
		for (int y = i + 1; y < string; y++)
		{
			if (numberCharacterInWord(arr[i]) < numberCharacterInWord(arr[y]))
				swap(&arr[i], &arr[y]);
		}
	}	
}

int numberCharacterInWord(char *arr)
{
	int number = 0;
		
	while (isspace(*arr))
		arr++;
		
	while (!isspace(*arr) && *arr)
	{
		number++;
		arr++;
	}
		
	return number;
}

void output(int size, const char arr[])
{
	for (int i = 0; i < size; i++)
		putchar(arr[i]);
		
	putchar('\n');
}

void swap(char **i, char **y)
{
	char *temp = *i;
	*i = *y;
	*y = temp;
}
