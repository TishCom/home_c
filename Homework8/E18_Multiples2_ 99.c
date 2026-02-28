/*
 * E18_Multiples2_ 99.c
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

//Функция возвращает колличетво чисел из number которые кратны devider
int multiplesNumber(int number, int devider);
//Функция выводит в трминал колличетво чисел из number которые кратны (1-9)
void selectionCoincidenceArr(int number);

int main(int argc, char **argv)
{
	int number = 0;
	
	scanf("%d", &number);
	
	selectionCoincidenceArr(number);
	
	return 0;
}

//Функция выводит в трминал колличетво чисел из number которые кратны (1-9)
void selectionCoincidenceArr(int number)
{
	for (int i = 2; i <= 9; i++)
		printf("%d %d\n", i, multiplesNumber(number, i));
}

//Функция возвращает колличетво чисел из number которые кратны devider
int multiplesNumber(int number, int devider)
{
	int coincidence = 0;
	
	for (int i = 2; i <= number; i++)
	{
		if (i % devider == 0)
			coincidence++;
	}
	
	return coincidence;
}
