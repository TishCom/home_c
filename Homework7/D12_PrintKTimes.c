/*
 * D12_PrintKTimes.c
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

#define printK(number)	printKTimes(1, number) 

void printKTimes(uint32_t i, uint32_t n);
void recursionFor(uint32_t i, uint32_t n, uint32_t *y);

int main(int argc, char **argv)
{
	int32_t number = 0;
	
	scanf("%d", &number);
	
	printK(number); 
	
	return 0;
}

void printKTimes(uint32_t i, uint32_t n) 
{
	if (n <= 0)
		return;
	
	recursionFor(0, i, &n);
	
	printKTimes(i + 1, n);
}

void recursionFor(uint32_t i, uint32_t n, uint32_t *y)
{
	if (*y <= 0 || i >= n)
		return;
		
	printf("%d ", n);
	
	*y = *y - 1;
	
	recursionFor(i + 1, n, y);
}
