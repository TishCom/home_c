/*
 * 14_TwoArrays.c
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

int main(int argc, char **argv)
{
	double numbers[8] = {0};
	double numbers1[8] = {0};
	
	for (int i = 0; i < 8; i++)
		scanf("%lf", &numbers[i]);
		
	numbers1[0] = numbers[0];
	
	for (int i = 1; i < 8; i++)
		numbers1[i] = numbers1[i - 1] + numbers[i];
		
	for (int i = 0; i < 8; i++)
		printf("%5.2lf ", numbers[i]);
		
	printf("\n");
		
	for (int i = 0; i < 8; i++)
		printf("%5.2lf ", numbers1[i]);
		
	return 0;
}

